#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <esp_spi_flash.h>
#include <esp_event.h>
#include "bootloader_random.h"
#include <esp_int_wdt.h>
#include <esp_task_wdt.h> 
#include <stdint.h>
#include "nokialcd.h"
#include "settings.h"
#include "wifi.h"
#include "menu.h"
#include "sensor.h"
#include "soc/rtc_wdt.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include "esp_log.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include "brucon_nvs.h"

#define COL_RED "\033[1;31m"
#define COL_STOP "\033[0m"

#define WIFI_CONNECT_TIMEOUT 200

extern volatile char calAlcSens;

enum GUI_MAIN_STATE_E { GSTATE_INIT, GSTATE_MAIN_MENU, GSTATE_MENU_CLICKED ,GSTATE_FETCHING_SCHED, GSTATE_ENROLLING};
enum GUI_MAIN_STATE_E main_state= GSTATE_INIT;
bool clicked_gui = true;
uint8_t clicked_gui_value = 0;

uint8_t mac[6] ;
volatile char* macstr;
char* hostname;

uint32_t click_value,click_level;
uint32_t stoppedwifiat;

void manage_click(uint32_t value,uint32_t level ){

  switch(main_state){
  case GSTATE_INIT:
    break;
  case GSTATE_MAIN_MENU:
      click_value = value;
      click_level= level;
      main_state = GSTATE_MENU_CLICKED;
    break;
  case GSTATE_MENU_CLICKED:
      break;
  case GSTATE_FETCHING_SCHED:
    break;
  case GSTATE_ENROLLING:
      break;
  }
}



volatile char preventbacklighttimeoutTask = 1;

void backlighttimeoutTask()
{
  while(1){
    vTaskDelay(10000);      
    if(!preventbacklighttimeoutTask)
      if((xTaskGetTickCount()-last_click)>1000){
	printf("backlighttimeout: %d\n",(xTaskGetTickCount()-last_click));
	switchbacklight(0);
      }
  }
}



#define WIFI_TIMEOUT 3000  //30s



void wifitimeoutTask()
{
  while(1){
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    if(wifiIsConnected()){
      // printf("backlighttimeout: %d\n",xTaskGetTickCount()-last_click);
      printf("stopping Wifi in : %d ticks\n",WIFI_TIMEOUT-(xTaskGetTickCount()-last_click));
      if((xTaskGetTickCount()-last_click)>WIFI_TIMEOUT){
	printf("stopping Wifi\n");
	BruconWifiStop();
	stoppedwifiat=xTaskGetTickCount();
      }
    }else{
      //we are reconnecting in 5 min
      vTaskDelay(5000 / portTICK_PERIOD_MS);
      printf("restarting Wifi in %d \n",
	     get_wifi_recotime()-(xTaskGetTickCount()-stoppedwifiat)
	     );
      if( (xTaskGetTickCount()-stoppedwifiat) >=  get_wifi_recotime()){
	printf("restarting Wifi\n");
	needWifi(1);
	
      }

    }
  }

}



void gui()
{
  init_lcd(PHILLIPS);
  char * tut = calloc(50,1);
  rtc_wdt_disable();
  TaskHandle_t Tasktemp=NULL;;
  char get_sched_attempt =0;
  char get_sched_max_attempt =3;
  TickType_t tickstart = xTaskGetTickCount();
  menu_mgt_func = manage_click_menu_orig;

  switchbacklight(0);

  while(1){
    TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed=1;
    TIMERG0.wdt_wprotect=0;

    switch(main_state){
    case GSTATE_INIT:
      bruconlogo();
      // vTaskDelay(500 / portTICK_PERIOD_MS);
      //      lcd_clearframeB12(B12_WHITE);
      if(wifiIsConnected()){
        //  switchbacklight(1);
	sprintf(tut,"Connected:%s",get_wifi_netname());
	if(getBruCONConfigFlag("haveCSR")){
	  main_state=GSTATE_ENROLLING;
	} else {
	  main_state=GSTATE_FETCHING_SCHED;

	}
      } else {
	sprintf(tut,"Connecting....");
	printf("Connecting....%d / %d\n",(xTaskGetTickCount() -  tickstart) , (WIFI_CONNECT_TIMEOUT * portTICK_PERIOD_MS));

	if(     (xTaskGetTickCount() -  tickstart) > (WIFI_CONNECT_TIMEOUT * portTICK_PERIOD_MS)   ) {
	  // more than 10 sec to connect to wifi, fallback unconnected
	  for (int i = 0 ; i<10;i++)
	    printf("NO WIFI, fallback ! \n");

	  main_state = GSTATE_MAIN_MENU;
	}
      }
      *(tut+16)=0;
      lcd_setStr(tut,116,0,B12_BLACK,B12_WHITE,1,0);
      lcd_sync();
      vTaskDelay(500 / portTICK_PERIOD_MS);
      break;

    case GSTATE_ENROLLING:
      if(isgettingClientCert){
	bruconlogo();
	sprintf(tut,"Enrolling...");
	*(tut+16)=0;
	lcd_setStr(tut,116,0,B12_BLACK,B12_WHITE,1,0);
	lcd_sync();
	vTaskDelay(500 / portTICK_PERIOD_MS);
      } else {
	if(getBruCONConfigFlag("haveClientCert")==0){
	  printf("getting client cert\n");

	  isgettingClientCert = 1;
	  xTaskCreatePinnedToCore( task_getclientcert , "getClientCert" , 8192, NULL , 5| portPRIVILEGE_BIT , &Tasktemp ,0);
	} else {
	  if(Tasktemp){
	    vTaskDelete(Tasktemp);
	    Tasktemp=NULL;
	  }
	  restore_clicert(&clicert,&pk_ctx_clicert);
	  main_state=GSTATE_FETCHING_SCHED;
	  //switchbacklight(1);
	}
      }
      break;
    case GSTATE_MAIN_MENU:
      preventbacklighttimeoutTask=0;
      display_menu(clicked_gui_value);
      vTaskDelay(1);
      break;
    case GSTATE_MENU_CLICKED:
      manage_click_menu(click_value, click_level );
      main_state = GSTATE_MAIN_MENU;

      break;

    case GSTATE_FETCHING_SCHED:
      if( (netsched == NULL) ){
	if(get_sched_attempt==get_sched_max_attempt){
	  if(Tasktemp){
	    vTaskDelete(Tasktemp);
	    Tasktemp=NULL;
	  }
	  main_state=GSTATE_MAIN_MENU;
	  break;
	}
	if(isgettingsched){
	  bruconlogo();
	  sprintf(tut,"get sched:%d/%d",get_sched_attempt,get_sched_max_attempt);
	  *(tut+16)=0;
	  lcd_setStr(tut,116,0,B12_BLACK,B12_WHITE,1,0);
	  lcd_sync();
	  vTaskDelay(500 / portTICK_PERIOD_MS);
	} else {
	  printf("get sched:%d/%d\n",++get_sched_attempt,get_sched_max_attempt);
	  vTaskDelay(100 / portTICK_PERIOD_MS);
	  isgettingsched=1;
	  xTaskCreatePinnedToCore( get_sched_task , "getSched" , 8192, NULL , 5| portPRIVILEGE_BIT , &Tasktemp ,0);
	}
      } else {
	vTaskDelete(Tasktemp);
	main_state=GSTATE_MAIN_MENU;
	break;
      }



      break;

    }
    esp_task_wdt_reset();
  }
}


esp_err_t event_handler(void *ctx, system_event_t *event)
{
  if( event->event_id == SYSTEM_EVENT_STA_START ||
      event->event_id == SYSTEM_EVENT_STA_GOT_IP||
      event->event_id == SYSTEM_EVENT_STA_CONNECTED||
      event->event_id == SYSTEM_EVENT_STA_DISCONNECTED||
      event->event_id == SYSTEM_EVENT_STA_STOP){
    wifi_event_cb(ctx,event);
  }
  return ESP_OK;
}




void app_main()
{
  printf("BruCON Bage 2021\n");
  //disableCore0WDT(); disableCore1WDT();
  /* Print chip information */
  esp_chip_info_t chip_info;
  TaskHandle_t Tasktemp;
  rtc_wdt_disable();
  esp_efuse_mac_get_default(mac);
  esp_chip_info(&chip_info);  
  hostname = (char*)calloc(40,sizeof(char));
  macstr=hostname+12;
  sprintf(hostname,"BruconBadge-%02X:%02X:%02X:%02X:%02X:%02X",
	  mac[0] , mac[1] , mac[2],mac[3] , mac[4] , mac[5]);
  printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, MAC %s @APB %d TickFreq:%d\n",
         chip_info.cores,
         (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
         (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
         macstr,
         APB_CLK_FREQ,
         configTICK_RATE_HZ
	 );
  printf("silicon revision %d, ", chip_info.revision);
  printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
	 (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

  nvs_flash_init();
  esp_netif_init ();//tcpip_adapter_init();
  char taskret=0;
  ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );

  /*
  if(getBruCONConfigFlag("haveKeys")){
    BruCONErase_key("haveKeys");
    BruCONErase_key("haveClientCert");
    }
*/
  
  printf(COL_RED"have keys ? %d\n"COL_STOP, getBruCONConfigFlag("haveKeys"));

  if(getBruCONConfigFlag("haveKeys") == 0){
    bootloader_random_enable();
    isgeneratingRSA=1;
    xTaskCreatePinnedToCore( task_genrsa      , "genRSA" , 16384, &taskret , 5| portPRIVILEGE_BIT , &Tasktemp ,0);

    while(isgeneratingRSA){
      vTaskDelay(CONFIG_ESP_INT_WDT_TIMEOUT_MS-10);
      TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
      TIMERG0.wdt_feed=1;
      TIMERG0.wdt_wprotect=0;
      vTaskDelay(100/portTICK_PERIOD_MS);
      
    }
    vTaskDelete(Tasktemp);
    bootloader_random_disable();
  }

  if(getBruCONConfigFlag("haveAlcCal") == 0){
    calAlcSens=1;
    xTaskCreate(&calAlcTask,"CAL Alc", 4096,NULL, 3| portPRIVILEGE_BIT , &Tasktemp);
    while(calAlcSens){

      printf("CALIBRATING ALC\n");
      //printf("CAL : %d\n",calAlcSens);
      vTaskDelay(1000);
    }
    vTaskDelete(Tasktemp);
  }

  
  // printf(COL_RED"have csr ? %d\n"COL_STOP, getBruCONConfigFlag("haveCSR"));
  //printf(COL_RED"have client cert ? %d\n"COL_STOP, getBruCONConfigFlag("haveClientCert"));
  if(getBruCONConfigFlag("haveClientCert")){
    restore_clicert(&clicert,&pk_ctx_clicert);
  }
  
  // esp_log_level_set("*",ESP_LOG_VERBOSE);

  xTaskCreatePinnedToCore          (&gui                 , "guiTask"             , 10240, NULL, 5| portPRIVILEGE_BIT , NULL,1);
  xTaskCreate                      (&wificonnect         , "wifiTask"            , 10240, NULL, 6| portPRIVILEGE_BIT, NULL);
  //  xTaskCreatePinnedToCore          (&wificonnect         , "wifiTask"            , 8192, NULL, 6| portPRIVILEGE_BIT, NULL,1);
   
     xTaskCreate            (&backlighttimeoutTask, "backlighttimeoutTask", 2048, NULL, 0| portPRIVILEGE_BIT, NULL);
     xTaskCreate            (&wifitimeoutTask     , "wifitimeoutTask"     , 2048, NULL, 0| portPRIVILEGE_BIT, NULL);
  
  while(1)  {
    /* vTaskDelay((CONFIG_ESP_INT_WDT_TIMEOUT_MS-10)/portTICK_PERIOD_MS);
    TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed=1;
    TIMERG0.wdt_wprotect=0;*/
    vTaskDelay(1000);
  }



}
