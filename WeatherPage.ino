#include<Arduino.h>
#include "System_Init.h"
#include "WeatherPage.h"
#include "WeatherResources.h"



void DrawWeatherStateLogo( String tianqi )
{
    // String tianqi = actual.weather_name;
    if (tianqi == "多云" || tianqi == "晴间多云" || tianqi == "大部多云")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, duoyun, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "晴")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, qing, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "阴")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, ying, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "阵雨")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, zhenyu, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "雷阵雨")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, leizhenyu, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "雷阵雨伴有冰雹")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, leiyubingbao, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "小雨")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, xiaoyu, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "中雨")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, zhongyu, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "大雨")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, dayu, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "暴雨")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, baoyu, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "大暴雨")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, dabaoyu, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "特大暴雨")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, tedabaoyu, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "冻雨")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, dongyu, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "雨夹雪")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, yujiaxue, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "阵雪")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, zhenxue, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "小雪")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, xiaoxue, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "中雪")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, zhongxue, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "大雪")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, daxue, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "暴雪")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, baoxue, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "浮尘")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, fuchen, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "扬沙")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, yangsha, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "沙尘暴")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, shachenbao, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "强沙尘暴")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, qiangshachenbao, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "雾")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, dawu, 64, 64, GxEPD_BLACK); 
    }
    else if (tianqi == "霾")
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, mai, 64, 64, GxEPD_BLACK); 
    }
    else
    {
        my_display.drawInvertedBitmap(POS_X_WEATHER_LOGO, POS_Y_WEATHER_LOGO, weizhi, 64, 64, GxEPD_BLACK); 
    }
}

void DrawWeatherPageAll( void )
{
    


    return;
}
