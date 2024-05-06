#ifndef _RTOS_TASK_H
#define _RTOS_TASK_H

#define TIMER_ID_DRAW_GIF       0
#define TIMER_ID_DRAW_TT        1
#define PIC_FLUSH_TIME_GAP_MS   500

extern SemaphoreHandle_t muxtex_keys;
extern SemaphoreHandle_t muxtex_handler_keys_now;

void Task_Print( void* args );
void Task_KeyDetect( void* args );
void Task_DrawGif( void* args );
void Task_Select( void* args );
void Task_DrawWeather( void* args );
uint8_t TaskFunc_GetKey( void );

#define AUTO_UPDATE_WEATHER_GAP ( pdMS_TO_TICKS(60*60*1000) )

void ChangeTask( TaskHandle_t task_resume, uint8_t* first_flag );
enum KEY_NOW 
{
    ENUM_NO_KEY_NOW  = 0,
    ENUM_KEY_BOOT    = 1,
    ENUM_KEY_KEEP    = 1<<1,
    ENUM_KEY_MODE    = 1<<2
};

#endif