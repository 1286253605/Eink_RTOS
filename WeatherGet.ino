#include<Arduino.h>
#include <ArduinoJson.h>
#include "WiFiConfig.h"
#include "HTTPClient.h"

#include "WeatherGet.h"


struct ActualWeather actual_weather;
struct FutureWeather future_weather;
struct LifeIndex life_index;



/* 处理的错误在列表内返回true 不在则返回false */
bool XinzhiErrorCheck( char status_code[] )
{
    String z;
    if (String(status_code) == "AP010001")
        z = "API 请求参数错误";
    else if (String(status_code) == "AP010002")
        z = "没有权限访问这个 API 接口";
    else if (String(status_code) == "AP010003")
        z = "API 密钥 key 错误";
    else if (String(status_code) == "AP010004")
        z = "签名错误";
    else if (String(status_code) == "AP010005")
        z = "你请求的 API 不存在";
    else if (String(status_code) == "AP010006")
        z = "没有权限访问这个地点";
    else if (String(status_code) == "AP010007")
        z = "JSONP 请求需要使用签名验证方式";
    else if (String(status_code) == "AP010008")
        z = "没有绑定域名";
    else if (String(status_code) == "AP010009")
        z = "API 请求的 user-agent 与你设置的不一致";
    else if (String(status_code) == "AP010010")
        z = "没有这个地点";
    else if (String(status_code) == "AP010011")
        z = "无法查找到指定 IP 地址对应的城市";
    else if (String(status_code) == "AP010012")
        z = "你的服务已经过期";
    else if (String(status_code) == "AP010013")
        z = "访问量余额不足";
    else if (String(status_code) == "AP010014")
        z = "访问频率超过限制";
    else if (String(status_code) == "AP010015")
        z = "暂不支持该城市的车辆限行信息";
    else if (String(status_code) == "AP010016")
        z = "暂不支持该城市的潮汐数据";
    else if (String(status_code) == "AP010017")
        z = "请求的坐标超出支持的范围";
    else if (String(status_code) == "AP100001")
        z = "心知系统内部错误：数据缺失";
    else if (String(status_code) == "AP100002")
        z = "心知系统内部错误：数据错误";
    else if (String(status_code) == "AP100003")
        z = "心知系统内部错误：服务内部错误";
    else if (String(status_code) == "AP100004")
        z = "心知系统内部错误：网关错误";
    else
        return false;
    return true;
}

/* 处理天气实况返回数据 */
/* String结构比较复杂 使用引用传递而不是使用指针传递 */
bool ParseActualWeather( String& content, struct ActualWeather *data )
{
    DynamicJsonDocument json( 1536 );   // 分配内存
    DeserializationError error = deserializeJson( json, content );  // 解析JSON
    if( error )
    {
        Serial.printf( "实况天气加载失败: %s", error.c_str() );
        return false;
    }

    /* 检查获取天气数据时是否出错 */
    if( json["status_code"].isNull() == 0 )
    {
        strcpy( data->status_code, json["status_code"] );
        if( ! XinzhiErrorCheck( data->status_code ) )
        {
            Serial.println( "实况天气异常" );
            Serial.println( data->status_code );
        }
    }
        // 复制我们感兴趣的字符串 ,先检查是否为空，空会导致系统无限重启
    // isNull()检查是否为空 空返回1 非空0
    if (json["results"][0]["location"]["name"].isNull() == 0)
        strcpy(data->city, json["results"][0]["location"]["name"]);

    if (json["results"][0]["now"]["text"].isNull() == 0)
        strcpy(data->weather_name, json["results"][0]["now"]["text"]);

    if (json["results"][0]["now"]["code"].isNull() == 0)
        strcpy(data->weather_code, json["results"][0]["now"]["code"]);

    if (json["results"][0]["now"]["temperature"].isNull() == 0)
        strcpy(data->temp, json["results"][0]["now"]["temperature"]);

    if (json["results"][0]["last_update"].isNull() == 0)
        strcpy(data->last_update, json["results"][0]["last_update"]);

    return true;
}

bool ParseFutureWeather( String& content, struct FutureWeather *data )
{
    DynamicJsonDocument json( 2560 );
    DeserializationError error = deserializeJson( json, content );
    if ( error )
    {
        Serial.println( "未来天气JSON配置失败" );
        Serial.println( error.c_str() );
        return false;
    }

    if ( json["status_code"].isNull() == 0 )
    {
        strcpy( data->status_code, json[ "status_code" ] );
        
        if ( !XinzhiErrorCheck( data->status_code ) )
        {
            Serial.println( "未来天气异常" );
            Serial.println( data->status_code );
        }
    }

    // 复制我们感兴趣的字符串，先检查是否为空，空会复制失败导致系统无限重启
    if (json["results"][0]["daily"][0]["date"].isNull() == 0) //日期
        strcpy(data->date0, json["results"][0]["daily"][0]["date"]);
    if (json["results"][0]["daily"][1]["date"].isNull() == 0)
        strcpy(data->date1, json["results"][0]["daily"][1]["date"]);
    if (json["results"][0]["daily"][2]["date"].isNull() == 0)
        strcpy(data->date2, json["results"][0]["daily"][2]["date"]);

    if (json["results"][0]["daily"][0]["text_day"].isNull() == 0) //白天天气现象
        strcpy(data->date0_text_day, json["results"][0]["daily"][0]["text_day"]);
    if (json["results"][0]["daily"][1]["text_day"].isNull() == 0)
        strcpy(data->date1_text_day, json["results"][0]["daily"][1]["text_day"]);
    if (json["results"][0]["daily"][2]["text_day"].isNull() == 0)
        strcpy(data->date2_text_day, json["results"][0]["daily"][2]["text_day"]);

    if (json["results"][0]["daily"][0]["text_night"].isNull() == 0) //晚间天气现象
        strcpy(data->date0_text_night, json["results"][0]["daily"][0]["text_night"]);
    if (json["results"][0]["daily"][1]["text_night"].isNull() == 0)
        strcpy(data->date1_text_night, json["results"][0]["daily"][1]["text_night"]);
    if (json["results"][0]["daily"][2]["text_night"].isNull() == 0)
        strcpy(data->date2_text_night, json["results"][0]["daily"][2]["text_night"]);

    if (json["results"][0]["daily"][0]["high"].isNull() == 0)
        strcpy(data->date0_high, json["results"][0]["daily"][0]["high"]); //最高温度
    if (json["results"][0]["daily"][1]["high"].isNull() == 0)
        strcpy(data->date1_high, json["results"][0]["daily"][1]["high"]);
    if (json["results"][0]["daily"][2]["high"].isNull() == 0)
        strcpy(data->date2_high, json["results"][0]["daily"][2]["high"]);

    if (json["results"][0]["daily"][0]["low"].isNull() == 0) //最低温度
        strcpy(data->date0_low, json["results"][0]["daily"][0]["low"]);
    if (json["results"][0]["daily"][1]["low"].isNull() == 0)
        strcpy(data->date1_low, json["results"][0]["daily"][1]["low"]);
    if (json["results"][0]["daily"][2]["low"].isNull() == 0)
        strcpy(data->date2_low, json["results"][0]["daily"][2]["low"]);

    if (json["results"][0]["daily"][0]["humidity"].isNull() == 0) //湿度
        strcpy(data->date0_humidity, json["results"][0]["daily"][0]["humidity"]);

    if (json["results"][0]["daily"][0]["wind_scale"].isNull() == 0) //风力等级
        strcpy(data->date0_wind_scale, json["results"][0]["daily"][0]["wind_scale"]);
    // 这不是强制复制，你可以使用指针，因为他们是指向"内容"缓冲区内，所以你需要确保
    // 当你读取字符串时它仍在内存中
    return true;
}


bool ParseLifeIndex( String& content, struct LifeIndex *data )
{
    DynamicJsonDocument json( 1536 );
    DeserializationError error = deserializeJson( json, content );
    if ( error )
    {
        Serial.println( "生活指数JSON配置失败" );
        Serial.println( error.c_str() );
        return false;
    }

    if ( json["status_code"].isNull() == 0 )
    {
        strcpy( data->status_code, json[ "status_code" ] );
        
        if ( !XinzhiErrorCheck( data->status_code ) )
        {
            Serial.println( "生活指数异常" );
            Serial.println( data->status_code );
        }
    }

    if (json["results"][0]["suggestion"]["car_washing"]["brief"].isNull() == 0) // 洗车
        strcpy(data->car_washing, json["results"][0]["suggestion"]["car_washing"]["brief"]);

    if (json["results"][0]["suggestion"]["dressing"]["brief"].isNull() == 0) // 穿衣
        strcpy(data->dressing, json["results"][0]["suggestion"]["dressing"]["brief"]);

    if (json["results"][0]["suggestion"]["flu"]["brief"].isNull() == 0) // 流感
        strcpy(data->flu, json["results"][0]["suggestion"]["flu"]["brief"]);

    if (json["results"][0]["suggestion"]["sport"]["brief"].isNull() == 0) // 运动
        strcpy(data->sport, json["results"][0]["suggestion"]["sport"]["brief"]);

    if (json["results"][0]["suggestion"]["travel"]["brief"].isNull() == 0) // 旅游
        strcpy(data->travel, json["results"][0]["suggestion"]["travel"]["brief"]);

    if (json["results"][0]["suggestion"]["uv"]["brief"].isNull() == 0) // 紫外线指数
        strcpy(data->uvi, json["results"][0]["suggestion"]["uv"]["brief"]);

    return true;
}

String callHttps(String url)
{
    String payload;
    Serial.print("requesting URL: ");
    Serial.println(url);
    HTTPClient https;
    if (https.begin(url))
    {

        int httpsCode = https.GET();
        if (httpsCode > 0) // 判断有无返回值
        {
            /*payload = https.getString();
            Serial.println(payload);
            return payload;*/
            if (httpsCode == 200 || httpsCode == 304 || httpsCode == 403 || httpsCode == 404 || httpsCode == 500) // 判断请求是正确
            {
                payload = https.getString();
                //        Serial.println(payload);
                Serial.println(" ");
                // Serial.println( payload.c_str() );
                return payload;
            }
            else
            {
                Serial.print("请求错误：");
                Serial.println(httpsCode);
                Serial.println(" ");
                char *httpsCode_c = new char[8];
                itoa(httpsCode, httpsCode_c, 10); // int转char*
                payload = "{\"status_code\":\"" + String("请求错误:") + String(httpsCode_c) + "\"}";
                return payload;
            }
        }
        else
        {
            Serial.println(" ");
            Serial.print("GET请求错误：");
            Serial.println(httpsCode);
            Serial.printf("[HTTPS] GET... 失败, 错误: %s\n", https.errorToString(httpsCode).c_str());
            payload = "{\"status_code\":\"" + String(https.errorToString(httpsCode).c_str()) + "\"}";
            // Serial.println(payload);
            return payload;
        }
    }
    else
    {
        Serial.printf("[HTTPS] 无法连接服务器\n");
        payload = "{\"status_code\":\"" + String("无法连接服务器") + "\"}";
        return payload;
    }
    https.end();
}

void UpdataWeatherData()
{
    //拼装实况未来API地址
    String url_FutureWeather = "https://api.seniverse.com/v3/weather/daily.json";
    url_FutureWeather += "?key=" + target_site_authcode;
    url_FutureWeather += "&location=ip";
    url_FutureWeather += "&language=zh-Hans";
    url_FutureWeather += "&unit=c";
    url_FutureWeather += "&start=0";
    url_FutureWeather += "&days=3";

    //拼装实况天气API地址
    String url_ActualWeather = "https://api.seniverse.com/v3/weather/now.json";
    url_ActualWeather += "?key=" + target_site_authcode;
    url_ActualWeather += "&location=ip";
    url_ActualWeather += "&language=zh-Hans";
    url_ActualWeather += "&unit=c";

    //拼装生活指数
    String url_LifeIndex = "https://api.seniverse.com/v3/life/suggestion.json";
    url_LifeIndex += "?key=" + target_site_authcode;
    url_LifeIndex += "&location=ip";
    url_LifeIndex += "&language=zh-Hans";

    String str_temp = "";
    str_temp = callHttps( url_FutureWeather );
    ParseFutureWeather( str_temp, &future_weather );

    str_temp = callHttps( url_ActualWeather );
    ParseActualWeather( str_temp, &actual_weather );

    str_temp = callHttps( url_LifeIndex );
    ParseLifeIndex( str_temp, &life_index );

    return;
}

void SetDefaultWeatherValue()
{
    strcpy( actual_weather.city, "青岛" );

    // actual_weather.weather_code = "1";
    // actual_weather.weather_name = "晴";
    // actual_weather.temp = "15";
    // actual_weather.last_update = "2024-04-27T23:27:36+08:00";

    // life_index.dressing = "炎热";
    // life_index.flu = "少发";
    // life_index.sport = "适宜";
    // life_index.travel = "适宜";
    // life_index.uvi = "强";

    // future_weather.date0 = "2024-05-06";
    // future_weather.date0_text_day = "晴";
    // future_weather.date0_text_night = "晴";

    strcpy(actual_weather.weather_code, "1");
    strcpy(actual_weather.weather_name, "晴");
    strcpy(actual_weather.temp, "120");
    strcpy(actual_weather.last_update, "2024-04-27T23:27:36+08:00");

    strcpy(life_index.dressing, "炎热");
    strcpy(life_index.flu, "少发");
    strcpy(life_index.sport, "适宜");
    strcpy(life_index.travel, "适宜");
    strcpy(life_index.uvi, "强");

    strcpy(future_weather.date0, "2024-05-06");
    strcpy(future_weather.date0_text_day, "晴");
    strcpy(future_weather.date0_text_night, "晴");

}
