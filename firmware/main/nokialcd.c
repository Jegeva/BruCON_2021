#include "nokialcd.h"
#include "img_brucon.h"
#include "img_map.h"
#include "img_westvleteren.h"
#include "font_opensans_10.h"
#include "brucon_nvs.h"
#include "sensor.h"
#include <freertos/task.h>
#include "bootloader_random.h"
extern TickType_t  last_click;

spi_device_handle_t spi;
uint8_t driver;

uint16_t frame[ROW_LENGTH * COL_HEIGHT];

void do_spi_init();




static inline int min(int a, int b) { return (a < b ? a : b); }
static inline int max(int a, int b) { return (a > b ? a : b); }


#define CMD(x)  (x)
#define DATA(x) (0x100 | (x))

typedef struct {
    int bit;             /* next available bit position, MSB to LSB */
    int pos;             /* current position in buffer[] */
    int total_bits;      /* total bits currently in the buffer */
    int max_bits;        /* maximum number of bits in the buffer */
    uint32_t buffer[];
} bit_buffer_t;

static inline void bit_buffer_clear(bit_buffer_t *bb)
{
    bb->bit = 0;
    bb->pos = 0;
    bb->total_bits = 0;
    bb->buffer[0] = 0;   /* Only the first element of the buffer needs to be cleared, the 'next'
                          * element will be cleared when the buffer is getting used */
}

static inline bit_buffer_t *bit_buffer_alloc(int bits)
{
    bit_buffer_t *bb = heap_caps_malloc(sizeof(bit_buffer_t) + ((bits + 31) & ~31) / 8, MALLOC_CAP_DMA);
    if (bb)
        bit_buffer_clear(bb);
    return bb;
}

static inline void bit_buffer_add(bit_buffer_t *bb, int bits, uint32_t data)
{
    int available = 32 - bb->bit;  /* the available bits in buffer[pos] */

    if (bits == 0)
        return;

    if (available >= bits)         /* test if it fits in one step */
        bb->buffer[bb->pos] |= __builtin_bswap32(data << (available - bits));
    else {                         /* crossing the 32-bit boundary */
        bb->buffer[bb->pos] |= __builtin_bswap32(data >> (bits - available));
        bb->buffer[bb->pos + 1] = __builtin_bswap32(data << (32 - (bits - available)));
    }

    bb->total_bits += bits;
    bb->bit += bits;
    bb->pos += bb->bit / 32;
    bb->bit %= 32;

    if (bb->bit == 0)              /* an element was filled without overflow, make sure that */
        bb->buffer[bb->pos] = 0;   /* the next element is cleared */
}

void lcd_send_bit_buffer(spi_device_handle_t spi, bit_buffer_t *bb)
{
    esp_err_t ret;
    spi_transaction_t t = {
        .length = bb->total_bits,
        .tx_buffer = bb->buffer,
    };
    //spi_device_polling_end(spi,portMAX_DELAY);
    ret = spi_device_transmit(spi, &t);
    assert(ret == ESP_OK);
}


#define get_nibble(x, n)     (((x) >> (n * 4)) & 0x0f)
#define nibble(x, n)         (((x) & 0x0f) << (n * 4))
#define set_nibble(a, x, n)  (((a) & ~(0x0f << (n * 4)) & 0xffff) | nibble((x), (n)))

static pixel_t pixel_blend(pixel_t a, pixel_t b, unsigned int blend)
{
    unsigned int aa = get_nibble(a, 3);
    unsigned int ab = (get_nibble(b, 3) * (blend + 1) >> 4);

    b = set_nibble(b, ab, 3);

    if (ab == 0xf)        /* b is covering a */
        return b;
    else if (ab == 0)     /* b is invisible */
        return a;
    else if (aa == 0)     /* a is invisble */
        return b;
    else if (aa == 0xf)   /* a is opaque */
        return nibble(0xf, 3) |
            nibble(((get_nibble(b, 2) * (ab + 1)) >> 4) + ((get_nibble(a, 2) * (16 - ab)) >> 4), 2) | /* R */
            nibble(((get_nibble(b, 1) * (ab + 1)) >> 4) + ((get_nibble(a, 1) * (16 - ab)) >> 4), 1) | /* G */
            nibble(((get_nibble(b, 0) * (ab + 1)) >> 4) + ((get_nibble(a, 0) * (16 - ab)) >> 4), 0);  /* B */
                          /* both a & b have alpha */
    return nibble(max(aa, ab), 3) |
        nibble(((get_nibble(b, 2) * ab) / (aa + ab)) + ((get_nibble(a, 2) * aa) / (aa + ab)), 2) |    /* R */
        nibble(((get_nibble(b, 1) * ab) / (aa + ab)) + ((get_nibble(a, 1) * aa) / (aa + ab)), 1) |    /* G */
        nibble(((get_nibble(b, 0) * ab) / (aa + ab)) + ((get_nibble(a, 0) * aa) / (aa + ab)), 0);     /* B */
}

void draw_pixel(int x, int y, pixel_t color, unsigned int blend)
{
    if(x < 0 || y < 0 || x > ROW_LENGTH - 1 || y > COL_HEIGHT - 1)
        return;

    pixel_t * dst = frame + (y * COL_HEIGHT) + x;
    *dst = pixel_blend(*dst, color, blend);
}

static inline font_char_t * get_font_char(const font_t *font, int ch)
{
    /* If a character is out of range, the first will be returned. Usually it's space (' '). */
    ch = min(font->max, ch);
    ch -= font->min;
    ch = max(0, ch);
    return (font_char_t *)(font->data + font->lookup[ch]);
}

int string_width(const font_t * font, const char * str)
{
    if (!str)
        return 0;

    int result = 0;
    while (*str)
        result += get_font_char(font, *str++)->advance;

    return result;
}

void draw_string(const font_t * font, int x, int y, pixel_t color, const char * str)
{
    if (!str)
        return;

    while (*str) {
        font_char_t * fc = get_font_char(font, *str++);
        for (int cy = 0, cc = 0; cy < fc->h; cy++)
            for (int cx = 0; cx < fc->w; cx++, cc++)
                draw_pixel(x + cx + fc->left, y + cy - fc->top, color,
                        (fc->buffer[cc / 4] >> ((cc % 4) * 4)) & 0x0f);

        x += fc->advance;
    }
}

void draw_string_aligned(const font_t * font, int x, int y, int w, int h,
        pixel_t color, unsigned int flags, const char *str)
{
    char l[1024];
    char * lines[16]; // Max 16 lines
    int line = 1;

    if (!str || (w <= 0) || (h <= 0))
        return;

    strcpy(l, str);
    lines[0] = l;

    if (flags & WRAP) {
        char * last_space = NULL;
        char * p = l;

        while (*p) {
            if (*p == '\n') {                 /* linebreak */
                *p = '\0';
                lines[line++] = ++p;
                last_space = NULL;
                continue;
            }
            else if (*p == ' ') {             /* space, check wrapping */
                *p = '\0';
                if (string_width(font, lines[line - 1]) > w) {  /* wrap ! */
                    if (last_space == NULL)   /* no space on this line */
                        p++;
                    else {                    /* wrap at previous space */
                        *p = ' ';
                        *last_space = '\0';
                        p = last_space + 1;
                    }
                    lines[line++] = p;
                    last_space = NULL;
                    continue;
                }
                last_space = p;
                *p = ' ';
            }
            p++;
        }
        if (string_width(font, lines[line - 1]) > w) {
            /* Final line too long -> wrap once more */
            if (last_space != NULL) {         /* wrap at previous space */
                *last_space = '\0';
                lines[line++] = last_space + 1;
            }
        }
    }

    switch (flags & NOKIA_ALIGN_V) {
        case TOP:      y += font->height;  break;
        case VCENTER:  y += (font->height + h - (font->height * (line - 1))) / 2;  break;
        case BOTTOM:   y += h - (font->height * (line - 1));  break;
    }

    for (int i = 0; i < line; i++) {
        int px = x;
        switch (flags & NOKIA_ALIGN_H) {
            case CENTER:  px += (w - string_width(font, lines[i])) / 2;  break;
            case RIGHT:   px += w - string_width(font, lines[i]);  break;
        }
        draw_string(font, px, y + i * font->height, color, lines[i]);
    }
}

static bool intersect(int x1, int y1, int w1, int h1,
                      int x2, int y2, int w2, int h2,
                      int * xr, int * yr, int * wr, int * hr)
{
    int x3 = x1 + w1, y3 = y1 + h1, x4 = x2 + w2, y4 = y2 + h2;
    *xr = max(x1, x2); *wr = min(x3 - *xr, x4 - *xr);
    *yr = max(y1, y2); *hr = min(y3 - *yr, y4 - *yr);
    if (*wr <= 0 || *hr <= 0) { /* no overlap */
        *xr = 0; *yr = 0; *wr = 0; *hr = 0;
        return false;
    }
    return true;
}

void draw_image(const image_t * img, int x, int y)
{
    int dx, dy, dw, dh;

    if (intersect(0, 0, ROW_LENGTH, COL_HEIGHT, x, y, img->w, img->h, &dx, &dy, &dw, &dh)) {
        const pixel_t * src = img->buffer + ((dy - y) * img->w) + (dx - x);
        pixel_t * dst = frame + (dy * ROW_LENGTH) + dx;

        for (; dh; dh--, src += img->w - dw, dst += ROW_LENGTH - dw)
            for (int i = dw; i; i--, dst++, src++)
                *dst = pixel_blend(*dst, *src, 0xf);
    }
}

static bit_buffer_t *line_buffer;

void switchbacklight(int state){
    if(state)
        last_click=xTaskGetTickCount();
    if(esp_reset_reason() == ESP_RST_BROWNOUT){
      gpio_set_level(ENSCR_PIN,0);
      printf("has a brownout, not turning backlight on")	;
      return;
    }
    gpio_set_level(ENSCR_PIN,state);
}

void init_lcd(int type)
{
    esp_err_t ret;
    //int i;
    gpio_config_t io_conf;
    driver = type;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask =  (1ULL<<LCD_SCK) |  (1ULL<<LCD_DIO) | (1ULL<<LCD_RST) |  (1ULL<<LCD_CS);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    LCD_SCK_L;
    LCD_DIO_L;
    dl_us(10);
    LCD_CS_H;
    dl_us(10);
    LCD_RST_L;
    dl_us(200);
    LCD_SCK_H;
    LCD_DIO_H;
    LCD_RST_H;


    spi_bus_config_t buscfg={
        .mosi_io_num=LCD_DIO,
        .sclk_io_num=LCD_SCK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1
    };
    spi_device_interface_config_t devcfg={
        .clock_speed_hz=30000000,               //Clock out at 1 MHz
        .mode=3,                                //SPI mode 3

        .queue_size=50,                          //We want to be able to queue 7 transactions at a time
        .pre_cb=NULL,
        .cs_ena_pretrans = 0,
        .cs_ena_posttrans = 0,
        .spics_io_num=LCD_CS,               //CS pin
        /* .pre_cb=lcd_spi_pre_transfer_callback, //Specify pre-transfer callback to handle D/C line
           .post_cb=lcd_spi_post_transfer_callback //Specify pre-transfer callback to handle D/C line*/
    };
    gpio_config_t io_conf2={
        .intr_type = GPIO_PIN_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL<<LCD_SCK) |  (1ULL<<LCD_DIO) |  (1ULL<<LCD_RST) |  (1ULL<<LCD_CS),
        .pull_down_en = 0,
        .pull_up_en = 0
    };
    gpio_config(&io_conf2);

    driver = type;

    line_buffer = bit_buffer_alloc(((ROW_LENGTH + 1) / 2 * 3) * 9);

    ret=spi_bus_initialize(HSPI_HOST, &buscfg, 1);
    assert(ret==ESP_OK);
    //Attach the LCD to the SPI bus
    ret=spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
    assert(ret==ESP_OK);
    do_spi_init();


    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask =  (1ULL<<ENSCR_PIN);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}



void do_spi_init()
{
    LCD_CS_H;
    dl_us(10);
    LCD_RST_L;
    dl_us(200);
    LCD_RST_H;

    if (driver == PHILLIPS) {
        bit_buffer_clear(line_buffer);
        bit_buffer_add(line_buffer, 9, CMD(SLEEPOUT));  // Sleep Out (0x11)
        bit_buffer_add(line_buffer, 9, CMD(BSTRON));    // Booster voltage on (0x03)
        bit_buffer_add(line_buffer, 9, CMD(DISPON));    // Display on (0x29)
        // lcd_send(LCD_COMMAND,INVON);		// Inversion on (0x20)
        // 12-bit color pixel format:
        bit_buffer_add(line_buffer, 9, CMD(PCOLMOD));   // Color interface format (0x3A)
        bit_buffer_add(line_buffer, 9, DATA(0x03));     // 0b011 is 12-bit/pixel mode
        bit_buffer_add(line_buffer, 9, CMD(MADCTL));    // Memory Access Control(PHILLIPS)

        bit_buffer_add(line_buffer, 9, DATA(0xC0));     // Mirror X & Y -> rotate display 180 deg
        bit_buffer_add(line_buffer, 9, CMD(SETCON));    // Set Contrast(PHILLIPS)
        bit_buffer_add(line_buffer, 9, DATA(0x3f));

        bit_buffer_add(line_buffer, 9, CMD(NOPP));      // nop(PHILLIPS)

        lcd_send_bit_buffer(spi, line_buffer);
    }
}

void lcd_sync()
{
    bit_buffer_clear(line_buffer);
    bit_buffer_add(line_buffer, 9, CMD((driver == EPSON ? PASET : PASETP)));
    bit_buffer_add(line_buffer, 9, DATA(0));
    bit_buffer_add(line_buffer, 9, DATA(131));
    bit_buffer_add(line_buffer, 9, CMD((driver == EPSON ? CASET : CASETP)));
    bit_buffer_add(line_buffer, 9, DATA(0));
    bit_buffer_add(line_buffer, 9, DATA(131));
    bit_buffer_add(line_buffer, 9, CMD((driver == EPSON ? RAMWR : RAMWRP)));
    lcd_send_bit_buffer(spi, line_buffer);

    uint16_t * p = frame;
    for (int y = 0; y < COL_HEIGHT; y++) {
        bit_buffer_clear(line_buffer);
        for (int x = 0; x < ROW_LENGTH; x += 2, p += 2) {
            bit_buffer_add(line_buffer, 9, DATA((((*p) >> 4) & 0xff)));
            bit_buffer_add(line_buffer, 9, DATA(((*p & 0x0F) << 4) | ((*(p + 1) >> 8) & 0x0F)));
            bit_buffer_add(line_buffer, 9, DATA((*(p + 1) & 0xff)));
        }
        lcd_send_bit_buffer(spi, line_buffer);
        bit_buffer_clear(line_buffer);
    }
}

void bruconlogo()
{
    draw_image(&img_brucon, 0, 0);
}

void MapWestL(void* arg)
{
    draw_image(&img_westvleteren, 0, 0);
}

void MapNovoL(void* arg)
{
    draw_image(&img_map, 0, 0);
}

void lcd_clearB12(uint16_t color)
{
    for (uint16_t * p = frame; p < frame + (ROW_LENGTH * COL_HEIGHT); p++)
        *p = color;
}

void lcd_contrast(char setting) {
    bit_buffer_clear(line_buffer);
    if (driver == EPSON)
	{
		setting &= 0x3F;	// 2 msb's not used, mask out
        bit_buffer_add(line_buffer, 9, CMD(VOLCTR));    // electronic volume, this is the contrast/brightness(EPSON)
		bit_buffer_add(line_buffer, 9, DATA(setting));  // volume (contrast) setting - course adjustment,  -- original was 24
		bit_buffer_add(line_buffer, 9, DATA(3));        // TODO: Make this coarse adjustment variable, 3's a good place to stay
	}
	else if (driver == PHILLIPS)
	{
		setting &= 0x7F;	// msb is not used, mask it out
        bit_buffer_add(line_buffer, 9, CMD(SETCON));    // contrast command (PHILLIPS)
		bit_buffer_add(line_buffer, 9, DATA(setting));  // volume (contrast) setting - course adjustment,  -- original was 24
	}
    lcd_send_bit_buffer(spi, line_buffer);
};

void lcd_setArc(int x0, int y0, int radius, int arcSegments[], int numSegments, int lineThickness, int color){};
void lcd_setCircle (int x0, int y0, int radius, int color, int lineThickness){};

void lcd_setStr(char *pString, int x, int y, int fColor, int bColor, char uselastfill, char newline)
{
    const font_t *f = &font_opensans_10;

    if (!newline)
        draw_string(f, y, x + f->height, fColor, pString);
    else
        draw_string_aligned(f, y + 2, x, ROW_LENGTH - y - 4, COL_HEIGHT - x, fColor, WRAP | CENTER | TOP, pString);
}

static void setPixel(int color, unsigned char x, unsigned char y)
{
        frame[y * ROW_LENGTH + x] = color;
}

void lcd_setLine(int x0, int y0, int x1, int y1, int color)
{
        int dy = abs(y1 - y0); // Difference between y0 and y1
        int dx = abs(x1 - x0); // Difference between x0 and x1
        int stepy = (y1 < y0 ? -1 : 1);
        int stepx = (x1 < x0 ? -1 : 1);

        dy <<= 1; // dy is now 2*dy
        dx <<= 1; // dx is now 2*dx
        setPixel(color, x0, y0);

        if (dx > dy)
        {
                int fraction = dy - (dx >> 1);
                while (x0 != x1)
                {
                        if (fraction >= 0)
                        {
                                y0 += stepy;
                                fraction -= dx;
                        }
                        x0 += stepx;
                        fraction += dy;
                        setPixel(color, x0, y0);
                }
        }
        else
        {
                int fraction = dx - (dy >> 1);
                while (y0 != y1)
                {
                        if (fraction >= 0)
                        {
                                x0 += stepx;
                                fraction -= dy;
                        }
                        y0 += stepy;
                        fraction += dx;
                        setPixel(color, x0, y0);
                }
        }
}



void lcd_setRect(int x0, int y0, int x1, int y1, unsigned char fill, int color)
{
    // check if the rectangle is to be filled
    unsigned int xstart,xend,ystart,yend;

    if (fill == 1) {
        xstart = min(x0, x1);
        xend   = max(x0, x1);
        ystart = min(y0, y1);
        yend   = max(y0, y1);

        /* TODO: x & y swapped ??? */
        for (int y = xstart; y <= xend; y++)
            for (int x = ystart; x <= yend; x++)
                frame[y * ROW_LENGTH + x] = color;
    }
    else {
        // best way to draw an unfilled rectangle is to draw four lines
        lcd_setLine(x0, y0, x1, y0, color);
        lcd_setLine(x0, y1, x1, y1, color);
        lcd_setLine(x0, y0, x0, y1, color);
        lcd_setLine(x1, y0, x1, y1, color);
    }
}

void lcd_printLogo(void){};
void lcd_printBMP(char * image_main){}; //prints an image (BMP);
void lcd_off(void){};
void lcd_on(void){};


#define RAND_NR_STR 13
char * randstr[RAND_NR_STR] = {
//  "Drink reponsibly"
    "drive",
    "dd",
    "sudo",
    "ssh 2 production",
    "devops",
    "update firmware",
    "write in c",
    "write in ASM",
    "write shellcodes",
    "heap feng shui",
    "heap spray",
    "0 day",
    "solder",
    
};

char * randco2str[RAND_NR_STR] = {
//  "Drink reponsibly"
  //"Bart De Wever   ",
    "bad breath",
    "lack of shower",
    "a bad capacitor",
    "CH4+poopoo",
    "Boris Johnson",
    "Bart De Wever",
    "Eric Zemmour",
    "2 many people",
    "overclocking",
    "herve cheese",
    "Richard Cheese",
    "TaunTaun's gut",
    "Magic smoke",
    
};

uint32_t readmeL(void* arg){
   preventbacklighttimeoutTask = 1;
   lcd_clearB12(0);
   lcd_setStr("For shit+giggles",2,0,B12_WHITE,0,1,0);
   lcd_setStr("The badge is part of a",18,0,B12_WHITE,0,1,0);
   lcd_setStr("CO2 measuring swarm",34,0,B12_RED,0,1,0);
   lcd_setStr("Blink color selfexplanatory",50,0,B12_WHITE,0,1,0);
   lcd_setStr("Blue is nodata",66,0,B12_WHITE,0,1,0);
   lcd_setStr("Alcool is pollution",82,0,B12_WHITE,0,1,0);   
   lcd_sync();
   return(0);
}

uint32_t VivaLaVodkaL(void* arg){
    preventbacklighttimeoutTask = 1;
    
    char * tmp_str= (char*)calloc(50,sizeof(char));;
    int32_t score = getBruCONConfigUint32("AlcCal");
    char * p;TickType_t tickstart;
    sensorheat(1);
    if(arg==NULL){      

      lcd_clearB12(0); last_click = xTaskGetTickCount();
      lcd_setStr("Drink Responsibly",2,0,B12_WHITE,0,1,0);
      lcd_setStr("  This is a TOY",18,0,B12_WHITE,0,1,0);
      lcd_setStr(" DO NOT TRUST IT",34,0,B12_RED,0,1,0);
      lcd_setStr(" Don't drink &",56,0,B12_WHITE,0,1,0);
      bootloader_random_enable();
      p =randstr[esp_random()%RAND_NR_STR];
      bootloader_random_disable();
      lcd_setStr(p,72,64-((strlen(p)/2)*8),B12_WHITE,0,1,0);
      tickstart = xTaskGetTickCount();
      lcd_sync();
    }else{
      lcd_clearB12(B12_WHITE);
      last_click = xTaskGetTickCount();
      //lcd_setStr("DrinkResponsibly",2,0,B12_WHITE,0,1,0);
      lcd_setStr("Measuring Air Quality",2 ,0,B12_EMERALD,0,1,0);
      lcd_setStr("Bad?Could be "   ,18,0,B12_BLUE ,0,1,0);
      lcd_setStr("C02 or...       ",34,0,B12_BLUE   ,0,1,0);
                
      bootloader_random_enable();
      //lcd_setStr(" ",56,0,B12_WHITE ,0,1,0);
      p =randco2str[esp_random()%RAND_NR_STR];
      bootloader_random_disable();
      lcd_setStr(p,56,64-((strlen(p)/2)*8),B12_BLUE,0,1,0);
      tickstart = xTaskGetTickCount();
      lcd_sync();
    }   
    vTaskDelay(100 / portTICK_PERIOD_MS);
    while((xTaskGetTickCount() -  tickstart) < 2000 ){
      preventbacklighttimeoutTask = 1;
      if(arg==NULL){
	lcd_setStr(" Sensor heating",95,0,B12_RED,0,1,0); lcd_sync();
	vTaskDelay(500 / portTICK_PERIOD_MS);
	lcd_setRect(90,0,108 ,131, 1, 0);
	lcd_sync();

      }else{
	lcd_setStr(" Sensor heating",95,0,B12_RED,0,1,0); lcd_sync();
	vTaskDelay(500 / portTICK_PERIOD_MS);
	lcd_setRect(90,0,108 ,131, 1, B12_WHITE);
	lcd_sync();

      }
	vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    
    tickstart = xTaskGetTickCount();
    
    //xTaskCreate( &  getAlcTask  , "getAlc" , 4096, NULL , 5| portPRIVILEGE_BIT , &Tasktemp );
    while((xTaskGetTickCount() -  tickstart) < 1500 ){
      if(arg==NULL){
	lcd_setStr(" Blow on Sensor",90,0,B12_GREEN,0,1,0);
	lcd_sync();
	vTaskDelay(500 / portTICK_PERIOD_MS);
	lcd_setRect(90,0,108 ,131, 1, 0);
      }
      else{
	lcd_setStr(" Wait...",90,0,B12_GREEN,0,1,0);
	lcd_sync();
	vTaskDelay(500 / portTICK_PERIOD_MS);
	lcd_setRect(90,0,108 ,131, 1, B12_WHITE);
      }
	lcd_sync();
	vTaskDelay(500 / portTICK_PERIOD_MS);
      
    }

    
    int32_t Alc_level = getSensor();
    sensorheat(0);
    
    //vTaskDelete(Tasktemp);
    score = abs(Alc_level - score);
    if(score < 0)
      score=0;
    
    if(arg==NULL){
      lcd_setRect(90,0,108 ,131, 1, 0);
      sprintf(tmp_str,"Alc/breath:%d",score);
    }
    else{
      lcd_setRect(90,0,108 ,131, 1, B12_WHITE);
      sprintf(tmp_str,"bad breath:%d",score);

    }
    lcd_setStr(tmp_str,95,0,B12_RED,0,1,0);
    lcd_sync();	vTaskDelay(500 / portTICK_PERIOD_MS);
    printf("SCORE:%d\n",score);
    preventbacklighttimeoutTask = 0;
    last_click = xTaskGetTickCount();
    if(arg==NULL)
      free(tmp_str);
    setnotaskbar(0);
    return score;
}



// vim: expandtab:ts=4:sw=4
