#include "wifi.h"
#include "menu.h"
#include "mqtt.h"
#include "esp_wifi_types.h"

#include "freertos/event_groups.h"




ip_addr_t ip_Addr;
esp_ip4_addr_t ip;
esp_ip4_addr_t gw;
esp_ip4_addr_t msk;


volatile bool bConnected = false;
volatile bool bneedWifi = true;
volatile bool bDNSFound = false;

unsigned char curr_bssid[7];

unsigned char * get_curr_bssid(){
  return( (unsigned char *) &curr_bssid);
}

bool wifiIsConnected()
{
    return bConnected;

}

bool isdnsfound()
{
    return bDNSFound;

}

#define WIFI_BASE_TIMEOUT  30000 //300s
unsigned int wifi_recotime=WIFI_BASE_TIMEOUT;
void set_wifi_recotime(int s){
  wifi_recotime=s;
}
unsigned int get_wifi_recotime(){
  return wifi_recotime;
}



#define WIFI_REASON_DISCO_MAXN 33

int wifi_disco_reason_id[WIFI_REASON_DISCO_MAXN] = {
  WIFI_REASON_UNSPECIFIED,
  WIFI_REASON_AUTH_EXPIRE,
  WIFI_REASON_AUTH_LEAVE,
  WIFI_REASON_ASSOC_EXPIRE,
  WIFI_REASON_ASSOC_TOOMANY,
  WIFI_REASON_NOT_AUTHED,
  WIFI_REASON_NOT_ASSOCED,
  WIFI_REASON_ASSOC_LEAVE,
  WIFI_REASON_ASSOC_NOT_AUTHED,
  WIFI_REASON_DISASSOC_PWRCAP_BAD,
  WIFI_REASON_DISASSOC_SUPCHAN_BAD,
  WIFI_REASON_IE_INVALID,
  WIFI_REASON_MIC_FAILURE,
  WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT,
  WIFI_REASON_GROUP_KEY_UPDATE_TIMEOUT,
  WIFI_REASON_IE_IN_4WAY_DIFFERS,
  WIFI_REASON_GROUP_CIPHER_INVALID,
  WIFI_REASON_PAIRWISE_CIPHER_INVALID,
  WIFI_REASON_AKMP_INVALID,
  WIFI_REASON_UNSUPP_RSN_IE_VERSION,
  WIFI_REASON_INVALID_RSN_IE_CAP,
  WIFI_REASON_802_1X_AUTH_FAILED,
  WIFI_REASON_CIPHER_SUITE_REJECTED,

  WIFI_REASON_INVALID_PMKID,

  WIFI_REASON_BEACON_TIMEOUT,
  WIFI_REASON_NO_AP_FOUND,
  WIFI_REASON_AUTH_FAIL,
  WIFI_REASON_ASSOC_FAIL,
  WIFI_REASON_HANDSHAKE_TIMEOUT,
  WIFI_REASON_CONNECTION_FAIL,
  WIFI_REASON_AP_TSF_RESET,
  WIFI_REASON_ROAMING
} ;
char * wifi_disco_reason_str[WIFI_REASON_DISCO_MAXN] = {
    " UNSPECIFIED",
    " AUTH_EXPIRE",
    " AUTH_LEAVE",
    " ASSOC_EXPIRE",
    " ASSOC_TOOMANY",
    " NOT_AUTHED",
    " NOT_ASSOCED",
    " ASSOC_LEAVE",
    " ASSOC_NOT_AUTHED",
    " DISASSOC_PWRCAP_BAD",
    " DISASSOC_SUPCHAN_BAD",
    " IE_INVALID",
    " MIC_FAILURE",
    " 4WAY_HANDSHAKE_TIMEOUT",
    " GROUP_KEY_UPDATE_TIMEOUT",
    " IE_IN_4WAY_DIFFERS",
    " GROUP_CIPHER_INVALID",
    " PAIRWISE_CIPHER_INVALID",
    " AKMP_INVALID",
    " UNSUPP_RSN_IE_VERSION",
    " INVALID_RSN_IE_CAP",
    " 802_1X_AUTH_FAILED",
    " CIPHER_SUITE_REJECTED",
    " INVALID_PMKID",
    " BEACON_TIMEOUT",
    " NO_AP_FOUND",
    " AUTH_FAIL",
    " ASSOC_FAIL",
    " HANDSHAKE_TIMEOUT",
    " CONNECTION_FAIL",
    " AP_TSF_RESET",
    " ROAMING"
} ;

esp_err_t wifi_event_cb(void *ctx, system_event_t *event)
{
  system_event_sta_disconnected_t * disco;
  system_event_sta_connected_t * co;
  switch( event->event_id){
  case SYSTEM_EVENT_STA_START:
    printf("sta start\n");
    esp_wifi_connect();
    break;
  case SYSTEM_EVENT_STA_GOT_IP:
    printf("got ip\n");
    ip = event->event_info.got_ip.ip_info.ip;
    gw = event->event_info.got_ip.ip_info.gw;
    msk = event->event_info.got_ip.ip_info.netmask;
    bConnected = true;
    //     xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
   
    break;
  case SYSTEM_EVENT_STA_CONNECTED:
    co = (system_event_sta_connected_t *)&event->event_info;
    curr_bssid[0]=co->bssid[0];
    curr_bssid[1]=co->bssid[1];
    curr_bssid[2]=co->bssid[2];
    curr_bssid[3]=co->bssid[3];
    curr_bssid[4]=co->bssid[4];
    curr_bssid[5]=co->bssid[5];
    curr_bssid[6]=0;
    printf("connected! %x:%x:%x:%x:%x:%x\n",
	   co->bssid[0],co->bssid[1],co->bssid[2],
	   co->bssid[3],co->bssid[4],co->bssid[5]
	   
	   );

    break;


  case SYSTEM_EVENT_STA_STOP:
    printf("sta stop\n");
    bConnected = false;
    break;

  case SYSTEM_EVENT_STA_DISCONNECTED:
    disco = (system_event_sta_disconnected_t *)&event->event_info;
    int i=0;
    while( (i < WIFI_REASON_DISCO_MAXN) && (disco->reason !=wifi_disco_reason_id[i]))
      i++;
    if(i <  WIFI_REASON_DISCO_MAXN)	{
      printf("sta disco need:%d id:%d info:%d %s\n",bneedWifi,(int)event->event_id,disco->reason,wifi_disco_reason_str[i]);
    } else {
      printf("sta disco need:%d id:%d info: DUNNO...\n",bneedWifi,(int)event->event_id);
    }
    if(bneedWifi) esp_wifi_connect();
	
    bConnected = false;

    break;

  case SYSTEM_EVENT_STA_LOST_IP:
    /* This is a workaround as ESP32 WiFi libs don't currently
       auto-reassociate. */
    printf("sta lost ip\n");
    bConnected = false;
    //xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
    break;

  default:
    printf("unmanaged wifi event : %d\n",event->event_id);

    break;
  }

  return ESP_OK;
}

void BruconWifiStop()
{
  if(!bneedWifi){
    MQTT_Stop();
    esp_wifi_stop();
    bConnected = 0;    
  }  
}


void needWifi(bool need)
{
   if(bConnected)
     return;
    bneedWifi=need;
    while(!bConnected);

}

volatile char wifi_inited =0;
void wificonnect()
{

  wifi_init_config_t cfg= WIFI_INIT_CONFIG_DEFAULT();;
  wifi_config_t sta_config_base={
    .sta = {
      .ssid = WIFI_SSID,
      .password = WIFI_PASSWORD,
      /* Setting a password implies station will connect to all security modes including WEP/WPA.
       * However these modes are deprecated and not advisable to be used. Incase your Access point
       * doesn't support WPA2, these mode can be enabled by commenting below line */
      .threshold.authmode = WIFI_AUTH_WPA2_PSK,

      .pmf_cfg = {
	.capable = true,
	.required = false
      },
    },
  };;
  //wifi_config_t sta_config;

  wifi_config_t sta_config = {
    .sta = {
      .ssid = "",
      .password = "",
      /* Setting a password implies station will connect to all security modes including WEP/WPA.
       * However these modes are deprecated and not advisable to be used. Incase your Access point
       * doesn't support WPA2, these mode can be enabled by commenting below line */
      .threshold.authmode = WIFI_AUTH_WPA2_PSK,

      .pmf_cfg = {
	.capable = true,
	.required = false
      },
    },
  };
  
  while(1){
    if(bneedWifi || bConnected)
      printf("WIFI RQ ST n:%d c:%d\n",bneedWifi,bConnected);
    if(bConnected){	  
      bneedWifi = false;    
      MQTT_Start();
      vTaskDelay(10000 / portTICK_PERIOD_MS);
      continue;
    }
    if(bneedWifi){
      last_click = xTaskGetTickCount();
      if(wifi_inited == 0){
	
	ESP_ERROR_CHECK(esp_netif_init());
	esp_netif_create_default_wifi_sta();

	ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
	ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
	ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
	
	strcpy( (char*)sta_config.sta.ssid, get_wifi_netname() );
	strcpy( (char*)sta_config.sta.password, get_wifi_pass() );
	// printf("C : %s %s\n",sta_config.sta.ssid,sta_config.sta.password);
	

	printf("connecting to %s \n",sta_config.sta.ssid);
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
	ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
	
	wifi_inited=1;
      }

      /*
	esp_wifi_disconnect();
	esp_wifi_stop();
      */
      
      ESP_ERROR_CHECK( esp_wifi_start() );
      ESP_ERROR_CHECK( esp_wifi_set_max_tx_power(80));
      //ESP_ERROR_CHECK( esp_wifi_connect() );
      while( !bConnected )
	vTaskDelay(500/portTICK_PERIOD_MS);
      ;
      printf("Got IP: %s\n", inet_ntoa( ip ) );
      printf("Net mask: %s\n", inet_ntoa( msk ) );
      printf("Gateway: %s\n", inet_ntoa( gw ) );
            printf("nssid: %d:%d:%d:%d:%d:%d\n",
	     sta_config.sta.bssid[0],
	     sta_config.sta.bssid[1],
	     sta_config.sta.bssid[2],
	     sta_config.sta.bssid[3],
	     sta_config.sta.bssid[4],
	     sta_config.sta.bssid[5]
	     );

            IP_ADDR4( &ip_Addr, 0,0,0,0 );

	    //  MQTT_Start();
	     
      if(bConnected)
	bneedWifi = false;
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS);

  }

}
