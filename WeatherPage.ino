#include<Arduino.h>
#include "System_Init.h"
#include "WeatherPage.h"
#include "WeatherGet.h"
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

void InitWeatherPage()
{
    my_display.setFullWindow();
    my_display.fillScreen( GxEPD_WHITE );
    my_display.nextPage();
    my_display.setPartialWindow( 0, 0, my_display.width(), my_display.height() );
    return;
}

void DrawWeatherPageAll( void )
{
    InitWeatherPage();

    String str_temp = "";
    str_temp += actual_weather.weather_name;
    DrawWeatherStateLogo( str_temp );
    my_display.drawInvertedBitmap( POS_CITY_LOGO_X, POS_CITY_LOGO_Y, dingwei, 32, 28, GxEPD_BLACK );
    str_temp = "";
    
    my_u8g2_fonts.setCursor( POS_CITY_TXT_X, POS_CITY_TXT_Y );
    str_temp = "城市:"; str_temp += actual_weather.city;
    my_u8g2_fonts.print( str_temp.c_str() );
    str_temp = "";

    my_u8g2_fonts.setCursor( POS_TEMP_NOW_TXT_X, POS_TEMP_NOW_TXT_Y );
    str_temp = "当前温度:"; 
    str_temp += actual_weather.temp;
    str_temp += "度";
    my_u8g2_fonts.print( str_temp.c_str() );
    str_temp = "";
    
    my_u8g2_fonts.setCursor( POS_UPDATE_TXT_X, POS_UPDATE_TXT_Y );
    str_temp = "日期:"; 
    for( uint8_t i=0; i < 10; i++ )  str_temp += actual_weather.last_update[i];
    my_u8g2_fonts.print( str_temp.c_str() );
    str_temp = "";

    my_u8g2_fonts.setCursor( POS_MAXMIN_TEMP_TXT_X, POS_MAXMIN_TEMP_TXT_Y );
    str_temp = "TODAY TEMP : "; 
    str_temp += future_weather.date0_low;
    str_temp += "~";str_temp += future_weather.date0_high;
    my_u8g2_fonts.print( str_temp.c_str() );
    str_temp = "";

    // my_u8g2_fonts.setCursor( POS_DAYNIGHT_TXT_X, POS_DAYNIGHT_TXT_Y );
    // str_temp = "TODAY:"; 
    // str_temp += future_weather.date0_code_day;
    // str_temp += "~";str_temp += future_weather.date0_code_night;
    // my_u8g2_fonts.print( str_temp.c_str() );
    // str_temp = "";

    my_u8g2_fonts.setCursor( POS_CLOTHING_TXT_X, POS_CLOTHING_TXT_Y);
    str_temp = "穿衣:"; 
    str_temp += life_index.dressing;
    my_u8g2_fonts.print( str_temp.c_str() );
    str_temp = "";

    my_u8g2_fonts.setCursor( POS_SPORT_TEXT_X, POS_SPORT_TEXT_Y);
    str_temp = "运动:"; 
    str_temp += life_index.sport;
    my_u8g2_fonts.print( str_temp.c_str() );
    str_temp = "";

    my_u8g2_fonts.setCursor( POS_FLU_TEXT_X, POS_FLU_TEXT_Y);
    str_temp = "流感:"; 
    str_temp += life_index.flu;
    my_u8g2_fonts.print( str_temp.c_str() );
    str_temp = "";

    my_u8g2_fonts.setCursor( POS_MANBA_OUT_TEXT_X, POS_MANBA_OUT_TEXT_Y );
    str_temp = "出游:"; 
    str_temp += life_index.travel;
    my_u8g2_fonts.print( str_temp.c_str() );
    str_temp = "";

    my_u8g2_fonts.setCursor( POS_DAY111_TEXT_X, POS_DAY111_TEXT_Y );
    str_temp = "明天 : "; 
    str_temp += future_weather.date1_low;
    str_temp += "~"; 
    str_temp += future_weather.date1_high ;
    str_temp += "度  ";
    str_temp += future_weather.date1_text_day;
    my_u8g2_fonts.print( str_temp.c_str() );
    str_temp = "";

    my_u8g2_fonts.setCursor( POS_DAY222_TEXT_X, POS_DAY222_TEXT_Y );
    str_temp = "后天 : "; 
    str_temp += future_weather.date2_low;
    str_temp += "~"; 
    str_temp += future_weather.date2_high;
    str_temp += "度  ";
    str_temp += future_weather.date2_text_day;
    my_u8g2_fonts.print( str_temp.c_str() );
    str_temp = "";

    my_display.nextPage();
    return;
}

