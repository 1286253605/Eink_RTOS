
#include<Arduino.h>

#include "Root_Page.h"
#include "System_Init.h"
#include "pic.h"
/* include fonts */
#include <Fonts/FreeMonoBold9pt7b.h>





void DrawDinosaurGIF( void )
{
    my_display.setFullWindow();
    my_display.fillScreen( GxEPD_WHITE );

    my_display.drawInvertedBitmap( DINOSAUR_POS_X, DINOSAUR_POS_Y, pic_dinosaur_1, DINOSAUR_WIDTH, DINOSAUR_HEIGH, GxEPD_BLACK );
    my_display.nextPage();

    my_display.setPartialWindow( 0, 0, my_display.width(), my_display.height() );

    return;
}

void DrawTestText()
{    
    my_display.setFullWindow();
    my_display.fillScreen( GxEPD_WHITE );

    PicShowInPage( 0 );
    my_display.nextPage();

    /* 划分局部刷新窗口 */
    // my_display.setPartialWindow( 0, 0, my_display.width(), my_display.height() );
    return;
}

void DrawSelectPage( void )
{
    my_display.setFullWindow();
    my_display.fillScreen( GxEPD_WHITE );
    my_display.fillScreen( GxEPD_BLACK );
    my_display.fillScreen( GxEPD_WHITE );
    /* 划分局部刷新窗口 */
    my_display.setPartialWindow( 0, 0, my_display.width(), my_display.height() );
    my_display.nextPage();
    return;
}

void DrawSelectPageLoop( uint8_t mode_now )
{
    // my_display.setPartialWindow( 0, 0, my_display.width(), my_display.height() );
    /* 开了局部刷新但是需要将全屏刷新为白 否则框会留痕迹 局刷不会闪屏 */
    my_display.fillRect( 0, 0, my_display.width(), my_display.height(), GxEPD_WHITE );
    my_display.fillRect( /*x*/0, /*y*/20*mode_now - 16, /*w*/128, /*h*/24, /*c*/GxEPD_BLACK );
    my_display.fillRect( /*x*/1, /*y*/20*mode_now - 15, /*w*/126, /*h*/22, /*c*/GxEPD_WHITE );  /* 宽和高都要-2,因为边宽为1 */
    
    my_u8g2_fonts.setCursor( 4, 20 );
    my_u8g2_fonts.print( "1.配网" );
    my_u8g2_fonts.setCursor( 4, 40 );
    my_u8g2_fonts.print( "2.无网模式" );

    my_u8g2_fonts.setCursor( 172, 20 );
    my_u8g2_fonts.print( "选择" );
    my_u8g2_fonts.setCursor( 172, 60 );
    my_u8g2_fonts.print( "确定" );

    my_display.nextPage();
}

void DrawWebserverPage( void )
{
    my_display.setFullWindow();
    my_display.fillScreen( GxEPD_WHITE );
    /* 划分局部刷新窗口 */
    my_display.setPartialWindow( 0, 0, my_display.width(), my_display.height() );
    my_display.drawInvertedBitmap( DINOSAUR_POS_X, 15, pic_dinosaur_1, DINOSAUR_WIDTH, DINOSAUR_HEIGH, GxEPD_BLACK );
    
    my_u8g2_fonts.setCursor( DINOSAUR_POS_X - 30, 15 + 75 );
    my_u8g2_fonts.print( "正在启动服务器..." );

    my_display.nextPage();
    return;
}

void DrawDinosaurGIF( uint8_t counter, uint16_t x, uint16_t y )
{
    if( counter % 2 == 1 )
    {
        my_display.fillRect( x, y,
                    DINOSAUR_WIDTH, DINOSAUR_HEIGH, GxEPD_WHITE );
        my_display.drawInvertedBitmap( x, y, 
                    pic_dinosaur_1, DINOSAUR_WIDTH, DINOSAUR_HEIGH, GxEPD_BLACK );
    }
    else
    {
        my_display.fillRect( x, y, 
                    DINOSAUR_WIDTH, DINOSAUR_HEIGH, GxEPD_WHITE );
        my_display.drawInvertedBitmap( x, y,
                    pic_dinosaur_2, DINOSAUR_WIDTH, DINOSAUR_HEIGH, GxEPD_BLACK );
    }
    my_display.nextPage();

    return;
}

void DrawWeather( void )
{
    
    return;
}
