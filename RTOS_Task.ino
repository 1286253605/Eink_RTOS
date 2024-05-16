#include<Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "RTOS_Task.h"
#include "Eink_Arduinov1.h"
#include "Root_Page.h"
#include "WiFiConfig.h"
#include "WiFi.h"
#include "pic.h"
#include "my_ntp.h"
#include "WeatherGet.h"
#include "esp_sleep.h"

/* 屏幕排线折叠 朝向屏幕右上方是MODE 右下方是KEEP */
#define KEY_NEXT_PAGE               ENUM_KEY_BOOT
#define KEY_SELECT_CHANGE           ENUM_KEY_MODE
#define KEY_CONFIRM                 ENUM_KEY_KEEP
#define KEY_FUNCTION_NEXT_PAGE      ENUM_KEY_MODE
#define KEY_FUNCTION_CONFIRM        ENUM_KEY_KEEP
#define KEY_FUNCTION_UPDATE         ENUM_KEY_BOOT


#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  15         // duration ESP32 will go to sleep (in seconds) (120 seconds = 2 minutes)
#define digitalToggle(x) digitalWrite(x, !digitalRead(x))
#define BOTTON_PIN_BITMASK  ((1ul<<1) | (1ul<<8))        // GPIOs 1 and 8

/**********************************************
    Global
**********************************************/
/* Semaphore */
SemaphoreHandle_t sema_binary_keys = NULL;
SemaphoreHandle_t muxtex_handler_keys_now = NULL;


/* Timer */
// TimerHandle_t timer_drawTT  = NULL;
// TimerHandle_t timer_drawGIF = NULL;

/* Global variables */
uint8_t key_num_now = ENUM_NO_KEY_NOW;
// uint8_t _counter_dtt        = 0;
// uint8_t _counter_drawGIF    = 0;


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
    Task 
**********************************************/

/* 画Gif任务 & 配网 */
void Task_DrawGif( void* args )
{
    /* 用于判断是否为第一次进入页面 被创建后进入循环和切换页面进入循环都属于第一次进入页面 需要刷新加载静态的内容 */
    static uint8_t  _first_loop_flag    = pdTRUE;
    /* 500ms刷新一帧 刷新间隔过低无法正常显示 */
    static uint32_t _last_counter       = 0;
    uint32_t pic_counter = 0;
    
    /* 配网相关 */
    boolean config_flag = false;
    uint32_t tick_start = 0;

    config_flag = CheckWiFiConfigInFlash();
    if( config_flag )   WiFi.begin( target_wifi_ssid.c_str(), target_wifi_passwd.c_str() );
    
    for(;;)
    {
        if( _first_loop_flag == pdTRUE )
        {
            _first_loop_flag = pdFALSE;
            DrawDinosaurGIF();                              /* Init */
            _last_counter = 0;
            tick_start = xTaskGetTickCount();
        }

        if( config_flag )                                   /* 如果Flash中有WiFi信息则进行连接 */
        {
            if( WiFi.status() == WL_CONNECTED )             /* 检查WiFi连接状态 */
            {
                // vTaskResume()                            /* 进入功能界面 */
                ntp_init();
                vTaskResume( THt_DrawTT );
                // vTaskResume( THt_TaskWeather );
                vTaskSuspend( NULL );
            }
            else                                            /* 没连上 */
            {
                /* 15s时间内没连接上 进入配网界面 */
                if( ( xTaskGetTickCount() - tick_start ) > pdMS_TO_TICKS( 15000 ) )
                {
                    vTaskResume( THt_DrawSelect );
                    vTaskSuspend( NULL );
                }
            }
        }
        else                                                /* Flash中没有WiFi信息 直接进入配网选择页面 */
        {
            my_u8g2_fonts.setCursor( 10 , DINOSAUR_POS_Y + 100 );
            my_u8g2_fonts.print( "未配置WiFi 进入配置页面中 :P" );
            my_display.nextPage();
            vTaskDelay( pdMS_TO_TICKS( 3000 ) );
            vTaskResume( THt_DrawSelect );
            vTaskSuspend( NULL );
        }

        /* 当前Tick减去之前的Tick大于规定的间隔 画下一帧 */
        if( pdMS_TO_TICKS( PIC_FLUSH_TIME_GAP_MS ) <  xTaskGetTickCount() - _last_counter  )
        {
            /* 更新当前值 */
            _last_counter = xTaskGetTickCount();
            pic_counter++;
            DrawDinosaurGIF( pic_counter, DINOSAUR_POS_X, DINOSAUR_POS_Y );
        }

        // ChangeTask( THt_DrawTT, &_first_loop_flag );
        vTaskDelay( pdMS_TO_TICKS( 50 ) );
    }
    return;
}




/* 展示图片任务 懒得改任务名了  */
void Task_DrawTestText( void* args )
{
    static uint8_t _first_loop_flag = pdTRUE;
    static uint8_t pic_now      = 0;
    static uint8_t pic_before   = 0;
    static uint32_t target_tick = 0;

    for(;;)
    {

        if( _first_loop_flag == pdTRUE )
        {
            target_tick = 0;
            _first_loop_flag = pdFALSE;
            DrawTestText();
            vTaskDelay( pdMS_TO_TICKS( 100 ) );
            gpio_wakeup_enable( GPIO_NUM_1, GPIO_INTR_LOW_LEVEL );           /* 触发唤醒的GPIO */
            esp_sleep_enable_gpio_wakeup();
            esp_light_sleep_start();
        }
        esp_sleep_wakeup_cause_t wake_cause = esp_sleep_get_wakeup_cause();
        if( wake_cause == ESP_SLEEP_WAKEUP_GPIO )
        {
            target_tick = xTaskGetTickCount() + pdMS_TO_TICKS( 3*1000 );
            while( xTaskGetTickCount() <= target_tick )
            {
                if( pic_before != pic_now ) 
                {
                    PicShowInPage( pic_now );
                    pic_before = pic_now;
                }

                uint8_t temp_key = TaskFunc_GetKey();
                /* 画下一张图片 */
                if( temp_key == KEY_FUNCTION_CONFIRM )
                {
                    // pic_now++;
                    // if( pic_now >= PIC_MAX_NUM) pic_now = 0;
                    vTaskDelay( pdMS_TO_TICKS( 20 ) );
                }
                if( temp_key == KEY_FUNCTION_NEXT_PAGE )
                {
                    _first_loop_flag = pdTRUE;
                    vTaskResume(THt_TaskWeather);
                    vTaskSuspend( NULL );
                }
                if( temp_key == KEY_FUNCTION_UPDATE )
                {
                    pic_now++;
                    if( pic_now >= PIC_MAX_NUM) pic_now = 0;
                    vTaskDelay( pdMS_TO_TICKS( 20 ) );
                }
            }
            target_tick = 0;
            esp_light_sleep_start();

        } else { esp_light_sleep_start(); }



    }
}

/* 天气界面任务 */
void Task_DrawWeather( void* args )
{
    static uint8_t first_loop_flag = pdTRUE;
    static uint32_t target_tick = 0;
    static uint32_t last_auto_update_time = 0;
    uint8_t manual_update_flag = pdFALSE;
    uint8_t need_update_UI = pdFALSE;
    SetDefaultWeatherValue();
    /* 配置为GPIO拉低时唤醒 */
    /* PIN_KEEP == GPIO_NUM_1 */
    /* PIN_MODE == GPIO_NUM_8 */
    gpio_wakeup_enable( GPIO_NUM_1, GPIO_INTR_LOW_LEVEL );           /* 触发唤醒的GPIO */
    
    esp_sleep_enable_gpio_wakeup();
    esp_sleep_enable_timer_wakeup( TIME_TO_SLEEP * uS_TO_S_FACTOR );  /* 规定时间触发一次唤醒 */
    
    for(;;)
    {
        if(  pdTRUE == first_loop_flag )
        {
            target_tick = 0;
			first_loop_flag = pdFALSE;
            DrawWeatherPageAll();
            UpdataWeatherData();        /* 更新之后才会刷新 所以会稍有延迟 */
            DrawWeatherPageAll();

            vTaskDelay( pdMS_TO_TICKS( 1000 ) );
            gpio_wakeup_enable( GPIO_NUM_1, GPIO_INTR_LOW_LEVEL );           /* 触发唤醒的GPIO */
            esp_sleep_enable_gpio_wakeup();
            esp_sleep_enable_timer_wakeup( TIME_TO_SLEEP * uS_TO_S_FACTOR );  /* 规定时间触发一次唤醒 */
            esp_light_sleep_start();        /* 初始化之后就第一次进入Light Sleep */
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
                    UpdataWeatherData();
                    DrawWeatherPageAll();
                }
                if( temp_key == KEY_FUNCTION_NEXT_PAGE )
                {
                    first_loop_flag = pdTRUE;
                    // vTaskResume(THt_DrawTT);
                    vTaskResume(THt_TaskClock);
                    vTaskSuspend( NULL );
                    break; /* 任务恢复后从此处开始运行 所以需要手动再按一下更新键 */
                }
                vTaskDelay( pdMS_TO_TICKS( 20 ) );
            }
            target_tick = 0;
            esp_light_sleep_start();
        } else if( wake_cause == ESP_SLEEP_WAKEUP_TIMER )
        {
                // /* 用于验证Timer触发唤醒功能 */
                // first_loop_flag = pdTRUE;
                // gpio_wakeup_disable( GPIO_NUM_1 );
                // // gpio_wakeup_disable( GPIO_NUM_8 );
                // vTaskResume( THt_DrawTT );
                // vTaskSuspend( NULL );
                // /* 用于验证Timer触发唤醒功能 */

            UpdataWeatherData();
            DrawWeatherPageAll();
            vTaskDelay( pdMS_TO_TICKS(50) );
            esp_light_sleep_start();
        }
    }
}

/* 选择配网或无网界面 */
void Task_Select( void* args )
{
    static uint8_t first_loop_flag = pdTRUE;
    TaskHandle_t task_to_change = NULL;
    uint8_t mode_now = 1;

    for(;;)
    {
        if(  pdTRUE == first_loop_flag )
        {
            first_loop_flag = pdFALSE;
            mode_now = 1;
            DrawSelectPage();
        }

        DrawSelectPageLoop( mode_now );

        uint8_t temp_key = TaskFunc_GetKey();

        if( temp_key == KEY_SELECT_CHANGE )
        {
            if( mode_now < 2 )  
                mode_now++;
            else 
                mode_now = 1;
        }
        else if( temp_key == KEY_CONFIRM )
        {
            switch ( mode_now )
            {
                case 1:/* 配网 */
                    vTaskResume( THt_TaskWebserver );
                    vTaskSuspend( NULL );
                    break;
                
                case 2:/* 无网展示模式 */
                    vTaskResume( THt_DrawTT );
                    vTaskSuspend( NULL );
                    break;
            }
        }
        
        
    }
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
        else if ( temp_key == ENUM_KEY_KEEP )
        {
            Serial.printf( "KEEP Pressed -%d-\n", temp_key );
        }
        else if ( temp_key == ENUM_KEY_MODE )
        {
            Serial.printf( "MODE Pressed -%d-\n", temp_key );
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

/* 配网服务器任务 */
void Task_Webserver( void* arg )
{
    uint32_t last_counter = 0;
    uint8_t pic_counter = 0;

    DrawWebserverPage();
    SetupConfig();

    for(;;)
    {
        /* 没有客户机连接就直接跳过处理请求环节 */
        if( WiFi.status() != WL_CONNECTED )
        {
            WebseverLoop();
        }
        if( pdMS_TO_TICKS( PIC_FLUSH_TIME_GAP_MS ) < xTaskGetTickCount() - last_counter )
        {
            last_counter = xTaskGetTickCount();
            pic_counter++;
            DrawDinosaurGIF( pic_counter, DINOSAUR_POS_X, 15 );
        }

    }
}

/* 检测按钮&切换任务 每个任务之后都有切换到下一个任务的重复代码 封装成函数 */
void ChangeTask( TaskHandle_t task_resume, uint8_t* first_flag )
{
    uint8_t temp_key = TaskFunc_GetKey();
    if( temp_key == KEY_NEXT_PAGE )
    {
        *first_flag = pdTRUE;
        vTaskResume( task_resume );
        vTaskSuspend( NULL );
        vTaskDelay( pdMS_TO_TICKS( 20 ) );
    }
    return;
}

