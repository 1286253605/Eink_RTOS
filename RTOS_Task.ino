#include<Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "RTOS_Task.h"
#include "Eink_Arduinov1.h"
#include "Root_Page.h"


SemaphoreHandle_t sema_key_boot;
SemaphoreHandle_t sema_key_mode;
SemaphoreHandle_t sema_key_keep;

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
    uint8_t LED_Status = HIGH;
    sema_key_boot = xSemaphoreCreateCounting( 10, 0 );      /* MaxCount:10; start:0 */
    sema_key_mode = xSemaphoreCreateCounting( 10, 0 );  
    sema_key_keep = xSemaphoreCreateCounting( 10, 0 );
    for(;;)
    {
        /****************************************************************/
        if( xSemaphoreTake( sema_key_boot, pdMS_TO_TICKS( 50 ) ) == pdTRUE )
            Serial.printf( "boot pressed\t count:%d\n", uxSemaphoreGetCount( sema_key_boot ) );        
        else
            Serial.println( "Boot No Pressed" );
        /****************************************************************/
        if( xSemaphoreTake( sema_key_mode, pdMS_TO_TICKS( 50 ) ) == pdTRUE )
            Serial.printf( "Mode pressed\t count:%d\n", uxSemaphoreGetCount( sema_key_mode ) );        
        else
            Serial.println( "Mode No Pressed" );
        /****************************************************************/
        if( xSemaphoreTake( sema_key_keep, pdMS_TO_TICKS( 50 ) ) == pdTRUE )
            Serial.printf( "Keep pressed\t count:%d\n", uxSemaphoreGetCount( sema_key_keep ) );
        else
            Serial.println( "Keep No Pressed" );


        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
    }
}

void Task_KeyDetect( void* args )
{
    

    uint8_t status_key_mode = 0;
    uint8_t status_key_boot = 0;
    uint8_t status_key_keep = 0;
    for(;;)
    {
        status_key_mode = digitalRead( PIN_MODE );
        status_key_boot = digitalRead( PIN_BOOT_9 );
        status_key_keep = digitalRead( PIN_KEEP );
        
        if( status_key_mode == LOW )                    /* 需要做消抖处理 否则会一下子填满信号量 */
        {
            vTaskDelay( pdMS_TO_TICKS( 50 ) );
            status_key_mode = digitalRead( PIN_MODE );
            if(  status_key_mode == LOW )        
            {
                xSemaphoreGive( sema_key_mode );
                vTaskDelay( pdMS_TO_TICKS( 10 ) );
            }
        }
            
        if( status_key_boot == LOW )
        {
            vTaskDelay( pdMS_TO_TICKS( 50 ) );
            status_key_boot = digitalRead( PIN_BOOT_9 );
            if( status_key_boot == LOW )      
            {
                xSemaphoreGive( sema_key_boot );
                vTaskDelay( pdMS_TO_TICKS( 10 ) );
            }
        }

        if( status_key_keep == LOW )
        {
            vTaskDelay( pdMS_TO_TICKS( 50 ) );
            status_key_keep = digitalRead( PIN_KEEP );
            if( status_key_keep == LOW )      
            {
                xSemaphoreGive( sema_key_keep );
                vTaskDelay( pdMS_TO_TICKS( 10 ) );
            }
        }
        
        vTaskDelay( pdMS_TO_TICKS( 10 ) );
    }
}
