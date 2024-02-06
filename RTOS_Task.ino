#include<Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "RTOS_Task.h"
#include "Eink_Arduinov1.h"
#include "Root_Page.h"

SemaphoreHandle_t sema_binary_keys = NULL;
SemaphoreHandle_t muxtex_handler_keys_now = NULL;
uint8_t key_num_now = ENUM_NO_KEY_NOW;

void Task_DrawGif( void* args )
{
    for(;;)
    {
        DrawDinosaurGIF();
        vTaskDelay( pdMS_TO_TICKS( 20 ) );
    }
    return;
}

void Task_Print( void* args )
{
    for(;;)
    {
        xSemaphoreTake( muxtex_handler_keys_now, portMAX_DELAY );
        uint8_t temp_key = key_num_now;
        key_num_now = ENUM_NO_KEY_NOW;
        xSemaphoreGive( muxtex_handler_keys_now );

        if( temp_key == ENUM_KEY_BOOT )
        {
            /* 可以在此处挂起/恢复任务 */
            Serial.printf( "BOOT Pressed -%d-\n", temp_key );
        }
        
        vTaskDelay( pdMS_TO_TICKS( 100 ) );
        
    }
}

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
