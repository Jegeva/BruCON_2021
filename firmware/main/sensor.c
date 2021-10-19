#include "sensor.h"
#include "brucon_nvs.h"
#define DEFAULT_VREF 1100
#define NO_OF_SAMPLES 200
static esp_adc_cal_characteristics_t *adc_chars;
adc_unit_t unit = ADC_UNIT_1;
static const adc_atten_t atten = ADC_ATTEN_DB_11;
adc1_channel_t chan_sensor =ADC1_GPIO39_CHANNEL;


volatile char calAlcSens;
volatile char getAlcSens;
volatile uint16_t Alc_level;

void getSensorT();

void init_sensor (void){
    gpio_config_t io_conf;
    adc_unit_t unit = ADC_UNIT_1;
    
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(
			     unit,
			     atten,
			     ADC_WIDTH_BIT_12,
			     DEFAULT_VREF,
			     adc_chars
			     );
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1<<CONFIG_HEATER_MOSFET_PIN);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(chan_sensor, ADC_ATTEN_DB_11);
}


void calAlcTask(){
  TaskHandle_t Tasktemp;
  init_sensor();
  getAlcSens=1;
  gpio_set_level(CONFIG_HEATER_MOSFET_PIN,1);
  
  TickType_t tickstart = xTaskGetTickCount();
  printf("Heating for cal");
  while((xTaskGetTickCount() -  tickstart) < 5000 ){
    printf(".\n");
    vTaskDelay(500);
  }
  printf("\n");
  xTaskCreate( &  getSensorT  , "getSensor" , 4096, NULL , 5| portPRIVILEGE_BIT , &Tasktemp);

  while(getAlcSens){
  vTaskDelay(200);
  }
  vTaskDelete(Tasktemp);
  gpio_set_level(CONFIG_HEATER_MOSFET_PIN,0);
  printf("CAL Raw: %d\n", Alc_level);
  calAlcSens=0;
  setBruCONConfigUint32("AlcCal",Alc_level);
  setBruCONConfigFlag("haveAlcCal",1);
  while(1){ vTaskDelay(1000);};
}

void sensorheat(int on){
  if(!adc_chars)
    init_sensor();
  gpio_set_level(CONFIG_HEATER_MOSFET_PIN,on);
}

void waitsensor(){
  TickType_t tickstart = xTaskGetTickCount();
  while(((xTaskGetTickCount() -  tickstart)) < (10000/portTICK_PERIOD_MS) ){
    printf("w : %d %d %d.\n",xTaskGetTickCount(),tickstart,portTICK_PERIOD_MS);
    vTaskDelay(1000);
  }
}

void getSensorT(){
  getSensor();
  while(1)
  vTaskDelay(1000);
}

uint32_t getSensor(){
  if(!adc_chars)
    init_sensor();
  uint32_t adc_reading = 0;  

  sensorheat(1);
  waitsensor();

  //Multisamplingclear


  
  for (int i = 0; i < NO_OF_SAMPLES; i++) {
    if (unit == ADC_UNIT_1) {
      adc_reading += adc1_get_raw((adc1_channel_t)chan_sensor);
    }
  }
  adc_reading /= NO_OF_SAMPLES;
  sensorheat(0);
  //Convert adc_reading to voltage in mV
  uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
  printf("SENS Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);
  Alc_level=voltage;
  getAlcSens=0;
  return(voltage);
}

uint32_t heatandgetSensor(){
   sensorheat(1);
   waitsensor();
   uint32_t r = getSensor();
   sensorheat(0);
   return(r);
}
