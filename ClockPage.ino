#include<Arduino.h>
#include "System_Init.h"
#include "WeatherResources.h"
#include "ClockPage.h"
#include "ClockPageRes.h"
#include "time.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void DrawClockNumSmall( uint8_t x, uint8_t y, uint8_t num )
{
    switch ( num )
    {
    case 0:
        my_display.drawInvertedBitmap( x, y, zero_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    case 1:
        my_display.drawInvertedBitmap( x, y, one_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    case 2:
        my_display.drawInvertedBitmap( x, y, two_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    case 3:
        my_display.drawInvertedBitmap( x, y, three_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    case 4:
        my_display.drawInvertedBitmap( x, y, four_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    case 5:
        my_display.drawInvertedBitmap( x, y, five_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    case 6:
        my_display.drawInvertedBitmap( x, y, six_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    case 7:
        my_display.drawInvertedBitmap( x, y, seven_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    case 8:
        my_display.drawInvertedBitmap( x, y, eight_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    case 9:
        my_display.drawInvertedBitmap( x, y, nine_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    default:
        my_display.drawInvertedBitmap( x, y, zero_s, TIME_NUM_SMALL_WIDTH, TIME_NUM_SMALL_HEIGHT, GxEPD_BLACK );
        break;
    }
}

void DrawClockNumBig( uint8_t x, uint8_t y, uint8_t num )
{
    switch ( num )
    {
    case 0:
        my_display.drawInvertedBitmap( x, y, zero, TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    case 1:
        my_display.drawInvertedBitmap( x, y, one,TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    case 2:
        my_display.drawInvertedBitmap( x, y, two,TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    case 3:
        my_display.drawInvertedBitmap( x, y, three, TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    case 4:
        my_display.drawInvertedBitmap( x, y, four, TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    case 5:
        my_display.drawInvertedBitmap( x, y, five, TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    case 6:
        my_display.drawInvertedBitmap( x, y, six, TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    case 7:
        my_display.drawInvertedBitmap( x, y, seven, TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    case 8:
        my_display.drawInvertedBitmap( x, y, eight, TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    case 9:
        my_display.drawInvertedBitmap( x, y, nine, TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    default:
        my_display.drawInvertedBitmap( x, y, zero, TIME_NUM_WIDTH, TIME_NUM_HEIGHT, GxEPD_BLACK );
        break;
    }
}

void InitClockPage( void )
{
    my_display.setFullWindow();
    my_display.fillScreen( GxEPD_WHITE );
    my_display.nextPage();
    my_display.setPartialWindow( 0, 0, my_display.width(), my_display.height() );
    return;
}

void DrawClockPageAll( void )
{

    uint8_t try_time = 0;
    struct tm local_time;
    // while( !getLocalTime( &local_time ) )
    // {
    //     vTaskDelay( pdMS_TO_TICKS( 100 ) );
    //     if( ++try_time > 10 ) break;
    // }
    if( !getLocalTime( &local_time ) )
    {
        my_display.nextPage();
        my_display.fillRect( POS_TIME_NUM_X, POS_TIME_NUM_Y, 200, TIME_NUM_HEIGHT, GxEPD_WHITE );
        DrawClockNumBig( POS_TIME_NUM_X, POS_TIME_NUM_Y, 0 );
        DrawClockNumBig( POS_TIME_NUM_X + 52, POS_TIME_NUM_Y, 0 );
        DrawClockNumSmall( POS_TIME_NUM_X + 112, POS_TIME_NUM_Y + 14, 0 );
        DrawClockNumSmall( POS_TIME_NUM_X + 152, POS_TIME_NUM_Y + 14, 0 );
        my_display.nextPage();
        vTaskDelay( pdMS_TO_TICKS( 100 ) );
    }
    else
    {
        my_display.fillRect( POS_TIME_NUM_X, POS_TIME_NUM_Y, 200, TIME_NUM_HEIGHT, GxEPD_WHITE );
        DrawClockNumBig( POS_TIME_NUM_X, POS_TIME_NUM_Y, local_time.tm_hour/10 );
        DrawClockNumBig( POS_TIME_NUM_X + 52, POS_TIME_NUM_Y, local_time.tm_hour%10 );
        DrawClockNumSmall( POS_TIME_NUM_X + 112, POS_TIME_NUM_Y + 14, local_time.tm_min/10 );
        DrawClockNumSmall( POS_TIME_NUM_X + 152, POS_TIME_NUM_Y + 14, local_time.tm_min%10 );
        my_display.nextPage();
    }
    

}

// void Task_DrawClock( void* args )
// {
//     static uint8_t  first_loop_flag    = pdTRUE;
//     static uint32_t target_tick        = 0;
//     for(;;)
//     {
//         if( first_loop_flag == pdTRUE )
//         {
//             first_loop_flag == pdFALSE;
//             InitClockPage();
//             DrawClockPageAll();
//         }

//         DrawClockPageAll();
//         Serial.println("Clock Task is running");
//         vTaskDelay( pdMS_TO_TICKS( 1000 ) );
//     }
// }

void Task_DrawClock( void* args )
{
    static uint8_t _first_loop_flag = pdTRUE;
    uint32_t _last_counter = 0;                  /* 记录Tick值 */
    uint32_t flush_counter = 0;

    for(;;)
    {
        if( _first_loop_flag == pdTRUE )
        {
            _first_loop_flag = pdFALSE;
            InitClockPage();
            DrawClockPageAll();
        }
        DrawClockPageAll();
        vTaskDelay( pdMS_TO_TICKS( 2000 ) );
    }
}