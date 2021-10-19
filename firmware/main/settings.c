#include "settings.h"
#include "settings.priv.h"

char * ssid = WIFI_SSID; 
char * pass = WIFI_PASSWORD;
const char * get_wifi_netname()
{
  return ssid;

}

const char * get_wifi_pass(    )
{
  return pass;

}

char * get_client_cert();
