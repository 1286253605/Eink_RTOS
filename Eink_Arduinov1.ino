#include<Arduino.h>
#include "Eink_Arduinov1.h"
#include "System_Init.h"
#include "RTOS_Task.h"
#include "Root_Page.h"



void setup()
{
    SystemHardwareInit();
    SystemSoftwareInit();
}



void loop()
{
    vTaskDelay( pdMS_TO_TICKS( 20 ) );
}



