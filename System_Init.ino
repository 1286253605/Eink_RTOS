#include<Arduino.h>
#include<Wire.h>

#include "System_Init.h"
#include "RTOS_Task.h"
#include "Eink_Arduinov1.h"


// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>


/* Global Var */
/* U8G2字体设置 */
U8G2_FOR_ADAFRUIT_GFX my_u8g2_fonts;
/* 显示屏驱动 */
GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> my_display( GxEPD2_154( /*CS=*/7, /*DC=*/4, /*RST=*/5, /*BUSY=*/6 ) );





void SystemHardwareInit( void )
{
    Serial.begin( 115200 );
    _GPIOInit();
    _DisplayInit();

    return;
}

void SystemSoftwareInit( void )
{
    xTaskCreate( Task_Print,        "PRINT",    (1024)*1,   NULL,   IDLE_PRIORITY+1,    NULL );
    xTaskCreate( Task_KeyDetect,    "MODE",     (1024)*1,   NULL,   IDLE_PRIORITY+1,    NULL );
    xTaskCreate( Task_DrawGif,      "GIF",      (1024)*4,   NULL,   IDLE_PRIORITY+1,    NULL );
    return;
}

void _DisplayInit( void )
{
    /* 屏幕SPI */
    /*
    #include "pins_arduino.h"
        static const uint8_t SS    = 7;
        static const uint8_t MOSI  = 3;
        static const uint8_t MISO  = 10;
        static const uint8_t SCK   = 2;
    */
    SPI.begin( /*SCK*/2, /*MISO*/10, /*MOSI*/3, /*SS*/7 );

    my_display.init();
    my_u8g2_fonts.begin( my_display );      /* u8g2连接到GxEPD */
    my_display.setRotation( 2 );            /* 竖屏 */
    my_display.firstPage();
    my_display.display( 1 );                /* 局刷 */

    my_u8g2_fonts.setForegroundColor( GxEPD_BLACK );
    my_u8g2_fonts.setBackgroundColor( GxEPD_WHITE );
    my_u8g2_fonts.setFont( chinese_city_gb2312 );

    my_u8g2_fonts.setCursor( 20, 20 );
    my_u8g2_fonts.print( "hahaha1" );
    my_display.nextPage();
}

void _GPIOInit( void )
{
    pinMode( PIN_BOOT_9, INPUT );
    pinMode( PIN_MODE, INPUT );
    pinMode( PIN_KEEP, INPUT_PULLUP );
    pinMode( PIN_LED, OUTPUT );

    return;
}