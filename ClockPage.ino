#include<Arduino.h>
#include "System_Init.h"
#include "WeatherResources.h"
#include "ClockPage.h"
#include "ClockPageRes.h"
#include "time.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "RTOS_Task.h"
#include "my_ntp.h"

#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  60         // duration ESP32 will go to sleep (in seconds) (120 seconds = 2 minutes)
#define KEY_NEXT_PAGE               ENUM_KEY_BOOT
#define KEY_SELECT_CHANGE           ENUM_KEY_MODE
#define KEY_CONFIRM                 ENUM_KEY_KEEP
#define KEY_FUNCTION_NEXT_PAGE      ENUM_KEY_MODE
#define KEY_FUNCTION_CONFIRM        ENUM_KEY_KEEP
#define KEY_FUNCTION_UPDATE         ENUM_KEY_BOOT


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
    // my_display.setPartialWindow( 0, 0, my_display.width(), my_display.height() );
    return;
}

void DrawClockPageAll( void )
{

    uint8_t try_time = 0;
    struct tm local_time;
    my_display.setFullWindow();
    my_display.fillScreen( GxEPD_WHITE );
    my_display.nextPage();
    // my_display.setPartialWindow( 0, 0, my_display.width(), my_display.height() );
    // while( !getLocalTime( &local_time ) )
    // {
    //     vTaskDelay( pdMS_TO_TICKS( 100 ) );
    //     if( ++try_time > 10 ) break;
    // }
    void updateLocalTime();
    if( !getLocalTime( &local_time ) )
    {
        my_display.nextPage();
        my_display.fillRect( POS_TIME_NUM_X, POS_TIME_NUM_Y, 200, TIME_NUM_HEIGHT, GxEPD_WHITE );
        DrawClockNumBig( POS_TIME_NUM_X, POS_TIME_NUM_Y, 0 );
        DrawClockNumBig( POS_TIME_NUM_X + 52, POS_TIME_NUM_Y, 0 );
        DrawClockNumSmall( POS_TIME_NUM_X + 112, POS_TIME_NUM_Y + 14, 0 );
        DrawClockNumSmall( POS_TIME_NUM_X + 152, POS_TIME_NUM_Y + 14, 0 );
        my_display.nextPage();
        
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


void Task_DrawClock( void* args )
{
    static uint8_t _first_loop_flag = pdTRUE;
    uint32_t _last_counter = 0;                  /* 记录Tick值 */
    uint32_t target_tick = 0;

    gpio_wakeup_enable( GPIO_NUM_1, GPIO_INTR_LOW_LEVEL );
    esp_sleep_enable_gpio_wakeup();
    esp_sleep_enable_timer_wakeup( TIME_TO_SLEEP*uS_TO_S_FACTOR );

    for(;;)
    {
        if( _first_loop_flag == pdTRUE )
        {
            _first_loop_flag = pdFALSE;
            DrawClockPageAll();
            esp_light_sleep_start();
        }

        esp_sleep_wakeup_cause_t wake_cause = esp_sleep_get_wakeup_cause();
        if( wake_cause == ESP_SLEEP_WAKEUP_GPIO )
        {
            target_tick = xTaskGetTickCount() + pdMS_TO_TICKS( 5*1000 );    /* 5s进行按键检测 进行接下来的操作 */
            while( xTaskGetTickCount() <= target_tick )
            {
                uint8_t temp_key = TaskFunc_GetKey();
                if( temp_key == KEY_FUNCTION_UPDATE )
                {
                    DrawClockPageAll();
                }
                if( temp_key == KEY_FUNCTION_NEXT_PAGE )
                {
                    _first_loop_flag = pdTRUE;
                    vTaskResume( THt_DrawTT );
                    vTaskSuspend( NULL );
                    break; /* 任务恢复后从此处开始运行 所以需要手动再按一下更新键 */
                }
                vTaskDelay( pdMS_TO_TICKS( 20 ) );
            }
            target_tick = 0;
            esp_light_sleep_start();
        } else if( wake_cause == ESP_SLEEP_WAKEUP_TIMER )
        {
            // /* Test */
            // _first_loop_flag = pdTRUE;
            // vTaskResume( THt_DrawTT );
            // vTaskSuspend( NULL );
            /* !!!! 重新唤醒之后没法局刷 and 不知道为什么 TODO */
            DrawClockPageAll(); 
            esp_light_sleep_start();
        }
        

    }
}