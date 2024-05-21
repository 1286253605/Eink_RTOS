#include<Arduino.h>
#include "my_ntp.h"

const char *ntpServer = "time1.cloud.tencent.com";
const long gmtOffset_sec = 8 * 60 * 60;     /* 文章中的 -8*3600是错的 */
const int daylightOffset_sec = 0;

void printLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }

    Serial.println(&timeinfo, "%A, %Y-%m-%d %H:%M:%S");
}


/* 进入功能页面前调用 */
void ntp_init()
{
    if( WiFi.status() != WL_CONNECTED )
    {
        Serial.println( "WiFi Disconnected. NTP Init ERROR" );
    }
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
    return;
}   

void updateLocalTime()
{
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}
