#include<Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "RTOS_Task.h"
#include "Eink_Arduinov1.h"
#include "Root_Page.h"

#define KEY_NEXT_PAGE ENUM_KEY_BOOT


/**********************************************
    Global
**********************************************/
/* Semaphore */
SemaphoreHandle_t sema_binary_keys = NULL;
SemaphoreHandle_t muxtex_handler_keys_now = NULL;

/* Timer */
TimerHandle_t timer_drawTT  = NULL;
TimerHandle_t timer_drawGIF = NULL;

/* Global variables */
uint8_t key_num_now = ENUM_NO_KEY_NOW;
uint8_t _counter_dtt        = 0;
uint8_t _counter_drawGIF    = 0;


/**********************************************
    Function
**********************************************/
uint8_t TaskFunc_GetKey( void )
{
    xSemaphoreTake( muxtex_handler_keys_now, portMAX_DELAY );
    uint8_t temp_key = key_num_now;
    key_num_now = ENUM_NO_KEY_NOW;
    xSemaphoreGive( muxtex_handler_keys_now );

    return temp_key;
}


/**********************************************
    Calback
**********************************************/
void _Timer_TaskDTT_Callback( void* id )
{
    _counter_dtt++;
    if( _counter_dtt >= 100 )
    {
        _counter_dtt = 0;
    }
}

void _Timer_TaskDrawGIF_Callback( void* id )
{
    _counter_drawGIF++;

}


/**********************************************
    Task 
**********************************************/

/* 画Gif任务 */
void Task_DrawGif( void* args )
{
    /* 用于判断是否为第一次进入页面 被创建后进入循环和切换页面进入循环都属于第一次进入页面 需要刷新加载静态的内容 */
    static uint8_t _first_loop_flag = pdTRUE;
    uint8_t _last_counter = _counter_drawGIF;
    /* 200ms刷新一帧 */
    timer_drawGIF = xTimerCreate( "TimerDrawGIF", pdMS_TO_TICKS( 200 ), pdTRUE, ( void* )0, _Timer_TaskDrawGIF_Callback );
    Serial.printf("nimasile lx1\n");
    for(;;)
    {
        if( _first_loop_flag == pdTRUE )
        {
            _first_loop_flag = pdFALSE;
            DrawDinosaurGIF();                  /* Init */
            xTimerStart( timer_drawGIF, 10 );
            Serial.printf("nimasile lx2\n");
        }

        /* 不相等说明已经更新 画下一帧 */
        if( _last_counter != _counter_drawGIF )
        {
            /* 更新当前值 */
            _last_counter = _counter_drawGIF;
            if( _last_counter % 2 == 1 )
            {
                my_display.fillRect( DINOSAUR_POS_X, DINOSAUR_POS_Y, DINOSAUR_WIDTH, DINOSAUR_HEIGH, GxEPD_WHITE );
                my_display.drawInvertedBitmap( DINOSAUR_POS_X, DINOSAUR_POS_Y, pic_dinosaur_2, DINOSAUR_WIDTH, DINOSAUR_HEIGH, GxEPD_BLACK );
            }
            else
            {
                my_display.fillRect( DINOSAUR_POS_X, DINOSAUR_POS_Y, DINOSAUR_WIDTH, DINOSAUR_HEIGH, GxEPD_WHITE );
                my_display.drawInvertedBitmap( DINOSAUR_POS_X, DINOSAUR_POS_Y, pic_dinosaur_1, DINOSAUR_WIDTH, DINOSAUR_HEIGH, GxEPD_BLACK );
            }
            my_display.nextPage();
        }

        /* 检测按键换页 */
        uint8_t temp_key = TaskFunc_GetKey();
        if( temp_key == KEY_NEXT_PAGE )
        {
            _first_loop_flag = pdTRUE;
            xTimerStop( timer_drawGIF, 0 );
            vTaskResume( THt_DrawTT );
            vTaskSuspend( NULL );
        }
        vTaskDelay( pdMS_TO_TICKS( 20 ) );
    }
    return;
}




/* 打印测试文本任务 */
void Task_DrawTestText( void* args )
{
    static uint8_t _first_loop_flag = pdTRUE;
    uint8_t _last_counter = _counter_dtt;
    timer_drawTT = xTimerCreate( "TimerDTT", pdMS_TO_TICKS( 1000 ), pdTRUE, (void*)1, _Timer_TaskDTT_Callback );    
    

    for(;;)
    {
        if( _first_loop_flag == pdTRUE )
        {
            _first_loop_flag = pdFALSE;
            DrawTestText();             /* Init */        
            xTimerStart( timer_drawTT, 10 );
        }

        if( _last_counter != _counter_dtt )
        {        
            _last_counter = _counter_dtt;
            my_display.fillRect( PAGE_TEXT_PARTIAL_POS_X, PAGE_TEXT_PARTIAL_POS_Y, PAGE_TEXT_PARTIAL_WIDTH, PAGE_TEXT_PARTIAL_HEIGHT, GxEPD_WHITE );
            my_u8g2_fonts.setCursor( PAGE_TEXT_PARTIAL_POS_X, PAGE_TEXT_PARTIAL_POS_Y );
            my_u8g2_fonts.printf( "牢大今年%d岁了!", _last_counter );
            my_display.nextPage();
        }

        uint8_t temp_key = TaskFunc_GetKey();
        if( temp_key == KEY_NEXT_PAGE )
        {
            _first_loop_flag = pdTRUE;
            xTimerStop( timer_drawTT, 0 );
            vTaskResume( THt_DrawGIF );
            vTaskSuspend( NULL );
        }
        
        vTaskDelay( pdMS_TO_TICKS( 20 ) );
    }

    return;
}

/* 按键测试打印任务 */
void Task_Print( void* args )
{
    for(;;)
    {
        uint8_t temp_key = TaskFunc_GetKey();
        if( temp_key == ENUM_KEY_BOOT )
        {
            /* 可以在此处挂起/恢复任务 */
            Serial.printf( "BOOT Pressed -%d-\n", temp_key );
        }

        
        vTaskDelay( pdMS_TO_TICKS( 100 ) );
        
    }
}

/* 按键检测任务 */
void Task_KeyDetect( void* args )
{
    /* System_Init.ino  INTR_Keys */
    for(;;)
    {
        if( xSemaphoreTake( sema_binary_keys, pdMS_TO_TICKS( 10 ) ) == pdTRUE )
        {
            vTaskDelay( pdMS_TO_TICKS( 20 ) );                                  /* 消抖 */

            xSemaphoreTake( muxtex_handler_keys_now, portMAX_DELAY );           /* 互斥地访问按键变量key_num_now */

            if( PIN_STATUS_BOOT == LOW )
            {
                key_num_now = ENUM_KEY_BOOT;
            }
            else if( PIN_STATUS_KEEP == LOW )
            {
                key_num_now = ENUM_KEY_KEEP;
            }
            else if( PIN_STATUS_MODE == LOW )
            {
                key_num_now = ENUM_KEY_MODE;
            }

            xSemaphoreGive( muxtex_handler_keys_now );
        }
    }
}


