#ifndef _WIFICONFIG_H
#define _WIFICONFIG_H

#define TARGET_SSID_ADDR    4000
#define TARGET_PASSWD_ADDR  4032
#define TARGET_AUTH_ADDR    4064

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
/**************************************************************************************/

#endif