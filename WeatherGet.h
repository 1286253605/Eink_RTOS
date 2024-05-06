#ifndef _WEATHER_GET_H_
#define _WEATHER_GET_H_

void UpdataWeatherData();
void SetDefaultWeatherValue();
struct ActualWeather // 实况天气
{
    char status_code[64];           // 错误代码
    char city[16];         // 城市名称
    char weather_name[16]; // 天气现象名称
    char weather_code[4];           // 天气现象代码
    char temp[5];            // 温度
    char last_update[25];           // 最后更新时间
} ;

struct FutureWeather  // 未来天气
{
    char status_code[64]; // 错误代码

    char date0[14];            // 今天日期
    char date0_text_day[20];   // 白天天气现象名称
    char date0_code_day[4];    // 白天天气现象代码
    char date0_text_night[16]; // 晚上天气现象名称
    char date0_code_night[4];  // 晚上天气现象代码
    char date0_high[5]; // 最高温度
    char date0_low[5];  // 最低温度
    char date0_humidity[5];    // 相对湿度
    char date0_wind_scale[5];  // 风力等级

    char date1[14];                   // 明天日期
    char date1_text_day[20]; // 白天天气现象名称
    char date1_code_day[4];           // 白天天气现象代码
    char date1_text_night[16];        // 晚上天气现象名称
    char date1_code_night[4];         // 晚上天气现象代码
    char date1_high[5];        // 最高温度
    char date1_low[5];         // 最低温度
    // char date1_humidity[5];     //相对湿度

    char date2[14];                   // 后天日期
    char date2_text_day[20]; // 白天天气现象名称
    char date2_code_day[4];           // 白天天气现象代码
    char date2_text_night[16];        // 晚上天气现象名称
    char date2_code_night[4];         // 晚上天气现象代码
    char date2_high[5];        // 最高温度
    char date2_low[5];         // 最低温度
    // char date2_humidity[5];     //相对湿度
} ;

struct LifeIndex // 生活指数
{
    char status_code[64]; // 错误代码
    char car_washing[13]; // 洗车
    char dressing[13];    // 穿衣
    char flu[13];         // 流感
    char sport[13];       // 运动
    char travel[13];      // 旅游
    char uvi[13];         // 紫外线指数
} ;

// extern struct ActualWeather actual_weather;
// extern struct FutureWeather future_weather;
// extern struct LifeIndex life_index;

#endif
