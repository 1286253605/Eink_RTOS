#ifndef _WIFICONFIG_H
#define _WIFICONFIG_H

#define TARGET_SSID_ADDR    0
#define TARGET_PASSWD_ADDR  32
#define TARGET_AUTH_ADDR    64
#define TARGET_CITY_ADDR    96
#define TARGET_STRING_LEN   32

/* Function */
/**************************************************************************************/
String MakeHTMLPage( String title, String contents );
void WiFiScan( void );
void StartWebServer( void );
void WIFI_HTMLRootPage( void );
void WIFI_HTMLSettingsPage( void );
void WIFI_HTMLSetap( void );
void WIFI_HTMLNotFoundPage( void );
String urlDecode(String input);
bool CheckWiFiConfigInFlash( void );
void WiFi_Init( void );
void WebseverLoop( void );
/**************************************************************************************/



extern String target_wifi_ssid;
extern String target_wifi_passwd;
extern String target_site_authcode;

#endif