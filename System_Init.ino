#include<Arduino.h>
#include "System_Init.h"
#include "RTOS_Task.h"
#include "Eink_Arduinov1.h"

void SystemHardwareInit( void )
{
    Serial.begin( 115200 );
    pinMode( PIN_BOOT_9, INPUT );
    pinMode( PIN_LED, OUTPUT );

    
    return;
}

void SystemSoftwareInit( void )
{
    xTaskCreate( Task_Print,    "PRINT",    (1024)*1,   NULL,   IDLE_PRIORITY+1,    NULL );

    return;
}


