#ifndef _RTOS_TASK_H
#define _RTOS_TASK_H

extern SemaphoreHandle_t muxtex_keys;
extern SemaphoreHandle_t muxtex_handler_keys_now;

void Task_Print( void* args );
void Task_KeyDetect( void* args );
void Task_DrawGif( void* args );

enum KEY_NOW 
{
    ENUM_NO_KEY_NOW  = 0,
    ENUM_KEY_BOOT    = 1,
    ENUM_KEY_KEEP    = 1<<1,
    ENUM_KEY_MODE    = 1<<2
};

#endif