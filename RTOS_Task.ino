#include<Arduino.h>
#include "RTOS_Task.h"
#include "Eink_Arduinov1.h"

void Task_Print( void* args )
{
    uint8_t LED_Status = HIGH;
    for(;;)
    {
        Serial.println( "caonima lx" );
        if( LED_Status == HIGH )
        {
            digitalWrite( PIN_LED, LOW );
            LED_Status = !LED_Status;
        }   
        else
        {
            digitalWrite( PIN_LED, HIGH );
            LED_Status = !LED_Status;
        }

        
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );

    }
}