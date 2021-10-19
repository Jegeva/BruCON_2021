#include "mqtt.h"
#include "esp_system.h"
#include "esp_log.h"
#include "wifi.h"
#include "leds.h"

static const char *TAG = "MQTT_Brucon";
uint8_t my_mac_addr[6] = {0};
#define MQTT_URI    "mqtts://" BADGE_HOST ":8883"
char * clicertpem = NULL;
#define CLIPKPEMSZ 1800
char * clipkpem = NULL;
esp_mqtt_client_handle_t client=NULL;
int client_started=0;
unsigned char* bssid_topicstr=NULL;
unsigned char* bssid_str=NULL;
unsigned char* bssid_msg=NULL;
volatile unsigned int ini=1;
volatile int stopping=0;

static void post_measure(uint32_t measure){
  sprintf((char*)bssid_msg,"%02x:%02x:%02x:%02x:%02x:%02x|%d"
	  ,my_mac_addr[0]
	  ,my_mac_addr[1]
	  ,my_mac_addr[2]
	  ,my_mac_addr[3]
	  ,my_mac_addr[4]
	  ,my_mac_addr[5]
	  ,measure
	  );
  
  esp_mqtt_client_publish(client,(char*)bssid_topicstr , (char*)bssid_msg, 0, 0, 0);

}



static void set_bssid_vars(
			   unsigned char **bssid_strp,
			   unsigned char **bssid_topicstrp ,
			   unsigned char** bssid_messagestrp  ){
  
  unsigned char* bssid_array =  get_curr_bssid();


  if(bssid_topicstr==NULL)
    bssid_topicstr = (unsigned char*)calloc(28,sizeof(char));
  if(bssid_str==NULL)
    bssid_str = (unsigned char*)calloc(19,sizeof(char));
  if(bssid_msg==NULL)
    bssid_msg = (unsigned char*)calloc(35,sizeof(char));
  
  sprintf((char*)bssid_str,"%02x:%02x:%02x:%02x:%02x:%02x"
	  ,bssid_array[0]
	  ,bssid_array[1]
	  ,bssid_array[2]
	  ,bssid_array[3]
	  ,bssid_array[4]
	  ,bssid_array[5]
	  );
  sprintf((char*)bssid_topicstr,"/topic/%s",bssid_str );
  sprintf((char*)bssid_msg,"%02x:%02x:%02x:%02x:%02x:%02x/%s"
	  ,my_mac_addr[0]
	  ,my_mac_addr[1]
	  ,my_mac_addr[2]
	  ,my_mac_addr[3]
	  ,my_mac_addr[4]
	  ,my_mac_addr[5]
	  ,bssid_str );
  
  *bssid_strp=bssid_str;  
  *bssid_topicstrp=bssid_topicstr;
  *bssid_messagestrp=bssid_msg;
}


int msg_id_connect;
int msg_id_accesspoint;
void mqtt_event_handler(
			       void *handler_args,
			       esp_event_base_t base,
			       int32_t event_id,
			       void *event_data
			       )
{
  ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
  esp_mqtt_event_handle_t event = event_data;
  esp_mqtt_client_handle_t client = event->client;
  int msg_id;
  uint32_t r;
  unsigned char* bssid_str;
  unsigned char* bssid_topicstr;
  unsigned char* bssid_messagestr;
  set_bssid_vars(&bssid_str,&bssid_topicstr,&bssid_messagestr);

  switch ((esp_mqtt_event_id_t)event_id) {
  case MQTT_EVENT_CONNECTED:

      
    printf("COMQTT %s",bssid_str);
    
    ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
    msg_id = esp_mqtt_client_subscribe(client, "/topic/CONNECT", 0);
    msg_id_connect = msg_id;
    
    ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
 



    msg_id = esp_mqtt_client_subscribe(client,(char*)bssid_topicstr, 1);
    msg_id_accesspoint=msg_id;
    ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

  

    
    break;
  case MQTT_EVENT_DISCONNECTED:
    ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
    break;

  case MQTT_EVENT_SUBSCRIBED:

    
    
    ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d topiclen %d", event->msg_id,event->topic_len);
    if(event){

      if(event->msg_id ==msg_id_connect){
	msg_id = esp_mqtt_client_publish(client, "/topic/CONNECT", (char*)bssid_messagestr, 0, 0, 0);
	ESP_LOGI(TAG, "sent publish CO successful, msg_id=%d", msg_id);
	msg_id = esp_mqtt_client_unsubscribe(client, "/topic/CONNECT");
	ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
	  
      }else{

	sprintf((char*)bssid_msg,"%02x:%02x:%02x:%02x:%02x:%02x|C"
		,my_mac_addr[0]
		,my_mac_addr[1]
		,my_mac_addr[2]
		,my_mac_addr[3]
		,my_mac_addr[4]
		,my_mac_addr[5]
	        );
	
	msg_id = esp_mqtt_client_publish(client,(char*)bssid_topicstr ,(char*)bssid_msg , 0, 0, 0);
	ESP_LOGI(TAG, "sent publish CO successful, msg_id=%d", msg_id);
      }
    }
      
    
    
    break;
  case MQTT_EVENT_UNSUBSCRIBED:
    ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
    break;
  case MQTT_EVENT_PUBLISHED:
    ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);   
    break;
  case MQTT_EVENT_DATA:
    ESP_LOGI(TAG, "MQTT_EVENT_DATA");
    if(stopping==1){
      sprintf((char*)bssid_msg,"%02x:%02x:%02x:%02x:%02x:%02x|D"
	      ,my_mac_addr[0]
	      ,my_mac_addr[1]
	      ,my_mac_addr[2]
	      ,my_mac_addr[3]
	      ,my_mac_addr[4]
	      ,my_mac_addr[5]
	      );
      if (strncmp(event->data, (char*)bssid_msg, event->data_len) == 0)
	{
	  stopping=0;
	};
    
    }else{
      
      sprintf((char*)bssid_msg,"%02x:%02x:%02x:%02x:%02x:%02x|M"
	      ,my_mac_addr[0]
	      ,my_mac_addr[1]
	      ,my_mac_addr[2]
	      ,my_mac_addr[3]
	      ,my_mac_addr[4]
	      ,my_mac_addr[5]
	      );
      if (strncmp(event->data, (char*)bssid_msg, event->data_len) == 0) {
	ESP_LOGI(TAG, "MQTT asks for a Breathmint... wait for it...");
	if(ini==0){
	  needWifi(1);
	  r=VivaLaToothpasteDirect(NULL);
	  sprintf((char*)bssid_msg,"%02x:%02x:%02x:%02x:%02x:%02x|R@%d"
		  ,my_mac_addr[0]
		  ,my_mac_addr[1]
		  ,my_mac_addr[2]
		  ,my_mac_addr[3]
		  ,my_mac_addr[4]
		  ,my_mac_addr[5]
		  ,r
		  );
	  msg_id = esp_mqtt_client_publish(client,(char*)bssid_topicstr ,(char*)bssid_msg , 0, 0, 0);
	  needWifi(0);
	}
      }

      if( (event->data[0] == 'V'){
	  if((event->data[1] == '|')){
	    msg_id=strtoll( (event->data+2),NULL,10);
	    if(msg_id > -1)
	      starttaskColorAdvertise(msg_id);
	    else
	      stoptaskColorAdvertise();
	
	  }

    }
    
    /*
    printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
    printf("DATA=%.*s\r\n", event->data_len, event->data);
    if (strncmp(event->data, "send binary please", event->data_len) == 0) {
      ESP_LOGI(TAG, "Sending the binary");
      send_binary(client);
    }
    */
    break;
  case MQTT_EVENT_ERROR:
    ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
    if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
      if(event->error_handle->esp_transport_sock_errno != 0){
	ESP_LOGI(TAG, "Last error code reported from esp-tls: 0x%x", event->error_handle->esp_tls_last_esp_err);
	ESP_LOGI(TAG, "Last tls stack error number: 0x%x", event->error_handle->esp_tls_stack_err);
	ESP_LOGI(TAG, "Last captured errno : %d (%s)",  event->error_handle->esp_transport_sock_errno,strerror(event->error_handle->esp_transport_sock_errno));
      }
    }
    else if (event->error_handle->error_type == MQTT_ERROR_TYPE_CONNECTION_REFUSED) {
      ESP_LOGI(TAG, "Connection refused error: 0x%x", event->error_handle->connect_return_code);
    } else {
      ESP_LOGW(TAG, "Unknown error type: 0x%x", event->error_handle->error_type);
    }
    break;
  default:
    ESP_LOGI(TAG, "Other event id:%d", event->event_id);
    break;
  }
  /*
  free(bssid_str);
  free(bssid_topicstr);
  free(bssid_messagestr);
  */
}


void MQTT_Start(){

  if(client == NULL){
    if(clicertpem==NULL)
      getBruCONConfigString("ClientCert",&clicertpem);
    if(clipkpem==NULL){
      clipkpem=(char*)calloc(CLIPKPEMSZ,sizeof(char)); // exactly 1675 pem normally
      mbedtls_pk_write_key_pem(getclicertpk(),(unsigned char*)clipkpem,CLIPKPEMSZ);
    }
    // printf("Cl : %s\n",clicertpem);
    // printf("PK : %s\n",clipkpem);    
    esp_mqtt_client_config_t mqtt_cfg;
    esp_read_mac(my_mac_addr,ESP_MAC_WIFI_STA);
  
    memset(&mqtt_cfg,0,sizeof(esp_mqtt_client_config_t));

    mqtt_cfg.uri = MQTT_URI;
  
    mqtt_cfg.client_cert_pem = clicertpem;
    mqtt_cfg.client_cert_len = 0;

    mqtt_cfg.client_key_pem = clipkpem;
    mqtt_cfg.client_key_len = 0;
   
    mqtt_cfg.cert_pem = (const char *)server_root_cert_pem_start;
    /*
      mqtt_cfg.cert_len = (size_t)(server_root_cert_pem_end-server_root_cert_pem_start);
    */
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
  }

  if(!client_started){
    printf("MQTTSTART\n");
    esp_mqtt_client_start(client);
    client_started=1;
  }
  
}


void MQTT_Stop(){
  printf("MQTTSTOP\n");
  char * bssid_mmsg = (char*)calloc(35,sizeof(char));
  sprintf((char*)bssid_mmsg,"%02x:%02x:%02x:%02x:%02x:%02x|D"
	  ,my_mac_addr[0]
	  ,my_mac_addr[1]
	  ,my_mac_addr[2]
	  ,my_mac_addr[3]
	  ,my_mac_addr[4]
	  ,my_mac_addr[5]
	  );
  ini=0;
  esp_mqtt_client_publish(client,(char*)bssid_topicstr , (char*)bssid_mmsg, 0, 0, 0);
  free(bssid_mmsg);
  stopping=1;
  while(stopping);
  if(client != NULL)
    esp_mqtt_client_stop(client);
  client_started=0;
}
