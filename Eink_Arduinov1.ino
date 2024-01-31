#include<Arduino.h>
#include "Eink_Arduinov1.h"
#include "System_Init.h"
#include "RTOS_Task.h"




void setup()
{
    SystemHardwareInit();
    SystemSoftwareInit();
}



void loop()
{
    if( digitalRead( PIN_BOOT_9 ) == LOW )
    {
        vTaskDelay( pdMS_TO_TICKS( 100 ) );
        if( digitalRead( PIN_BOOT_9 ) == LOW )
        {
            Serial.println( "nmsl lx" );
            vTaskDelay( pdMS_TO_TICKS( 500 ) );
        }
    }
}



