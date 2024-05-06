#include <Arduino.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include <WebServer.h>
#include <HTTPClient.h>
// #include <esp_wifi.h>
#include "WiFiConfig.h"
#include "html_css.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Global Variables */
String ssid_list = "";
const char *my_ap_ssid = "ESP32_Eink_WiFi";         /* 配网WiFi热点名称 */
const IPAddress my_ap_ip( 192, 168, 1, 1 );         /* 配网ESP32 IP地址 */
const IPAddress my_ap_mask( 255, 255, 255, 0 );     /* 配网子网掩码 */
WebServer my_webserver( 80 );                       /* 配网网页的端口 */
DNSServer my_dnsserver;

String target_wifi_ssid     = "";
String target_wifi_passwd   = "";
String target_site_authcode = "";               /* 心知天气密钥 */
String target_site_city     = "";


/* 配置WiFi主函数 */
void SetupConfig( void )
{
    WiFiScan();
    StartWebServer();
    return;
}

void WebseverLoop( void )
{
    my_dnsserver.processNextRequest();
    my_webserver.handleClient();
    return;
}

void WiFiScan( void )
{
    /* 使用终端模式 STA  作为连接WIFI的设备扫描当前环境所有的WIFI */
    WiFi.mode( WIFI_STA );
    WiFi.disconnect();
    vTaskDelay( pdMS_TO_TICKS( 100 ) );
    int AP_num = WiFi.scanNetworks();
    vTaskDelay( pdMS_TO_TICKS( 100 ) );

    for( int i = 0; i < AP_num; i++ )
    {
        ssid_list += "<option value=\"";
        ssid_list += WiFi.SSID( i );
        ssid_list += "\">";
        ssid_list += WiFi.SSID( i );
        ssid_list += "</option>";
    }
    vTaskDelay( pdMS_TO_TICKS( 100 ) );

}

/* 启动Web服务 */
void StartWebServer( void )
{
    WiFi.mode( WIFI_AP );
    WiFi.softAPConfig( my_ap_ip, my_ap_ip, my_ap_mask );
    WiFi.softAP( my_ap_ssid );
    /* 启动一个DNS服务器 监听53端口 所有域名请求都解析到 my_ap_ip地址 */
    my_dnsserver.start( 53, "*", my_ap_ip );  

    Serial.print( "Config Web Server :" );
    Serial.println( WiFi.localIP() );
    my_webserver.on( "/settings", WIFI_HTMLRootPage );
    my_webserver.on( "/", WIFI_HTMLSettingsPage );
    my_webserver.on( "/setap", WIFI_HTMLSetap );
    my_webserver.onNotFound( WIFI_HTMLNotFoundPage );

    my_webserver.begin();
}


String MakeHTMLPage( String title, String contents )
{
    String s = "<!DOCTYPE html><html><head>";
    s += "<meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
    s += "<title>";
    s += title;
    s += "</title>";
    s += contents;
    s += "</body></html>";
    return s;
}

/* Page "/settings" */
void WIFI_HTMLRootPage( void )
{
    String s = "";
    s += "<style>";
    s += style_css_input_select;
    s += style_css_button;
    s += style_css_body;
    s += "</style>";
    s += "</head><body>";
    s += "<div>";
    s += "<br><h1>配置界面</h1><br><form method=\"get\" action=\"setconfig\"><br>心知密钥:<input name=\"authcode\" length=64 type=\"text\">";
    s += "<br>NTP服务器:<input name=\"ntpServer\" length=64 type=\"text\">";  
    s += "<br>时区:<input name=\"timezone_offset\" length=64 type=\"text\">";         
    s += "<input name=\"保存并提交\"  type=\"submit\" value=\"提交\"></form>"; 
    s += "<br><a href=\"/\"><button>跳转到配置WiFi页面</button></a>";
    s += "</div>";

    my_webserver.send( 200, "text/html", MakeHTMLPage( "配置界面", s ) );
}

/* Page "/" */
void WIFI_HTMLSettingsPage( void )
{
    String s = "";
    s += "<style>";
    s += style_css_input_select;
    s += style_css_button;
    s += style_css_body;
    s += "</style>";
    s += "</head><body>";
    s += "<div>";
    s += "<h1>Wi-Fi配置</h1><p>请在选择WiFi名称后输入对应的WiFi密码</p>";
    s += "<form method=\"get\" action=\"setap\"><label>网络:</label><select name=\"ssid\">";
    s += ssid_list;
    s += "</select><br>密码:<input name=\"pass\" length=64 type=\"text\">";
    // s += "<p>首次使用务必填写心知密钥</p>";
    s += "<form method=\"get\" action=\"setap\">心知密钥:<input name=\"authcode\" length=64 type=\"text\"><br>";
    s += "城市缩写:<input name=\"city\" length=32 type=\"text\"><br>";
    s += "<input name=\"保存并提交\"  type=\"submit\" value=\"提交\"></form>";
    s += "<br><a href=\"/settings\"><button>跳转到配置各种参数页面</button></a>";
    s += "</div>";
    my_webserver.send(200, "text/html", MakeHTMLPage("Wi-Fi配置", s)); 
}


/* "/setap" */
void WIFI_HTMLSetap( void )
{


    target_wifi_ssid = urlDecode( my_webserver.arg( "ssid" ) );
    Serial.print( "SSID:\t" );          
    Serial.println( target_wifi_ssid );
    target_wifi_passwd = urlDecode( my_webserver.arg( "pass" ) );
    Serial.print( "Passwd:\t" );        
    Serial.println( target_wifi_passwd );
    target_site_authcode = urlDecode( my_webserver.arg( "authcode" ) );
    Serial.print( "authcode:\t" );      
    Serial.println( target_site_authcode );
    target_site_city = urlDecode( my_webserver.arg( "city" ) );
    Serial.print( "city:\t" );      
    Serial.println( target_site_city );

    if( ( target_wifi_ssid != "" ) && ( target_wifi_passwd != "" ) )
    {
        /* 清空数据再写入 但是不清除心知天气密钥 */
        for( uint32_t i = 0; i < ( TARGET_SSID_ADDR + TARGET_STRING_LEN * 2 ); i++ )
        {
            /* EEPROM库对象默认大小为4096字节 0~4095 */
            EEPROM.begin( 4096 );
            EEPROM.write( i, 0 );
            EEPROM.commit();
        }
        /*******************WIFISSID和Password写入Flash中 32+32字节*******************/
        for( uint8_t i = 0; i < target_wifi_ssid.length(); i++ )
        {
            EEPROM.begin( 4096 );
            EEPROM.write( TARGET_SSID_ADDR + i, target_wifi_ssid[ i ] );
            Serial.printf("char %d is %c\n", i, EEPROM.read( TARGET_SSID_ADDR + i ));
            EEPROM.commit();
        }

        for( uint8_t i = 0; i < target_wifi_passwd.length(); i++ )
        {
            EEPROM.begin( 4096 );
            EEPROM.write( TARGET_PASSWD_ADDR + i, target_wifi_passwd[ i ] );
            EEPROM.commit();
        }
    }

    /*******************心知天气密钥写入Flash 64字节*******************/
    if( target_site_authcode != "" )
    {
        /* 先清除后写入 心智天气密钥长度小于32字节 */
        for( uint32_t i = TARGET_AUTH_ADDR; i < ( TARGET_AUTH_ADDR + TARGET_STRING_LEN ); i++ )
        {
            EEPROM.begin( 4096 );
            EEPROM.write( i, 0 );
            EEPROM.commit();
        }

        for( uint32_t i = 0; i < target_site_authcode.length(); i++ )
        {
            EEPROM.begin( 4096 );
            EEPROM.write( TARGET_AUTH_ADDR + i, target_site_authcode[ i ] );
            EEPROM.commit();
        }

        Serial.printf( "Write AUTH to flash done ->%d\n", target_site_authcode.length() );
    } else {
        Serial.println( "Auth Code is EMPTY!" );
    }
    

    // /* 城市名称缩写 */
    // if( target_site_city != "" )
    // {
    //     /* 先清除后写入 心智天气密钥长度小于32字节 */
    //     for( uint32_t i = TARGET_CITY_ADDR; i < ( TARGET_CITY_ADDR + TARGET_STRING_LEN ); i++ )
    //     {
    //         EEPROM.begin( 4096 );
    //         EEPROM.write( i, 0 );
    //         EEPROM.commit();
    //     }

    //     for( uint32_t i = TARGET_CITY_ADDR; i < target_site_city.length(); i++ )
    //     {
    //         EEPROM.begin( 4096 );
    //         EEPROM.write( TARGET_CITY_ADDR + i, target_site_city[ i ] );
    //         EEPROM.commit();
    //     }

    //     Serial.println( "Write city to flash done" );
    // }

    // EEPROM.commit();
    EEPROM.end();
    // EEPROM.begin(4096);
    // String test_str ="";
    // for( uint8_t i = TARGET_SSID_ADDR; i < TARGET_SSID_ADDR + 32; i++ )
    // {
    //     char ch = EEPROM.read( i );
    //     if( ch != 0 )
    //     {
    //         test_str += char( EEPROM.read( i ) );
    //     }
    // }
    // Serial.printf( "Flash String :%s", test_str.c_str() );

    String s = "<head><meta charset=\"utf-8\"></head><h1>设置结束！</h1><p>设备即将在重启后接入 \"";
    s += target_wifi_ssid;
    s += "\"";
    my_webserver.send( 200, "text/html", MakeHTMLPage( "WiFi配置", s ) );
    vTaskDelay( pdMS_TO_TICKS( 2000 ) );
    ESP.restart();
}

/* Page Notfound */
void WIFI_HTMLNotFoundPage( void )
{
    /* 配置超链接跳转到配网Settings页面 */
    String s = "";
    s += "<style>";
    s += style_css_button;
    s += style_css_body;
    s += "</style>";
    s += "</head><body>";
    s += "<div><h1>配网模式</h1><p><a href=\"/\">点击配网</a></p></div>";
    my_webserver.send( 200, "text/html", MakeHTMLPage( "配网模式", s ) );
}


String urlDecode(String input)
{
    String s = input;
    s.replace("%20", " ");
    s.replace("+", " ");
    s.replace("%21", "!");
    s.replace("%22", "\"");
    s.replace("%23", "#");
    s.replace("%24", "$");
    s.replace("%25", "%");
    s.replace("%26", "&");
    s.replace("%27", "\'");
    s.replace("%28", "(");
    s.replace("%29", ")");
    s.replace("%30", "*");
    s.replace("%31", "+");
    s.replace("%2C", ",");
    s.replace("%2E", ".");
    s.replace("%2F", "/");
    s.replace("%2C", ",");
    s.replace("%3A", ":");
    s.replace("%3A", ";");
    s.replace("%3C", "<");
    s.replace("%3D", "=");
    s.replace("%3E", ">");
    s.replace("%3F", "?");
    s.replace("%40", "@");
    s.replace("%5B", "[");
    s.replace("%5C", "\\");
    s.replace("%5D", "]");
    s.replace("%5E", "^");
    s.replace("%5F", "-");
    s.replace("%60", "`");
    return s;
}

/* 检查Flash中的WiFi配置 没有配置内容则返回False 有则写入全局变量并返回True */
bool CheckWiFiConfigInFlash( void )
{
    target_wifi_ssid    = "";
    target_wifi_passwd  = "";
    Serial.println( "Reading Flash..." );
    /* 在读取之前需要初始化 */
    if( !EEPROM.begin( 4096 ) )
    {
        Serial.println("EEPROM Init Failed...");
        return false;
    }
    // vTaskDelay( pdMS_TO_TICKS( 50 ) );
    /* 如果Flash中没有WiFi信息 函数直接返回false */

    // for( uint8_t i = 0; i < 100; i++ )
    // {
    //     Serial.printf("char %d is %d\n", i, EEPROM.read( TARGET_SSID_ADDR + i ));
    //     vTaskDelay( pdMS_TO_TICKS(5) );
    // }

    if( EEPROM.read( TARGET_SSID_ADDR ) == 0 )
    {
        Serial.printf( "No WiFi config in flash\n" );
        return false;
    }

    for( uint8_t i = TARGET_SSID_ADDR; i < TARGET_SSID_ADDR + 32; i++ )
    {
        char ch = EEPROM.read( i );
        if( ( ch != 0 ) && ( ch != 255 ) )
        {
            target_wifi_ssid += char( EEPROM.read( i ) );
        }
    }
    Serial.printf( "WiFi SSID : %s\n", target_wifi_ssid.c_str() );

    for( uint8_t i = TARGET_PASSWD_ADDR; i < TARGET_PASSWD_ADDR + 32; i++ )
    {
        char ch = EEPROM.read( i );
        if( ( ch != 0 ) && ( ch != 255 ) )
        {
            target_wifi_passwd += char( EEPROM.read( i ) );
        }
    }
    Serial.printf( "WiFi Passwd : %s\n", target_wifi_passwd.c_str() );

    for( uint8_t i = TARGET_AUTH_ADDR; i < TARGET_AUTH_ADDR + 64; i++  )
    {
        char ch = EEPROM.read( i );
        Serial.printf( "->%d\n", ch );
        if( ( ch != 0 ) && ( ch != 255 )  )
        {
            target_site_authcode += char( EEPROM.read( i ) );
        }
    }
    Serial.printf( "Auth code : %s\n", target_site_authcode.c_str() );

    return true;
}


void WiFi_Init( void )
{
    if( true == CheckWiFiConfigInFlash() )
    {
        /* 如果Flash中有WiFi就进行链接 */
        Serial.printf( "Connecting SSID:%s, Passwd:%s", 
                            target_wifi_ssid.c_str(), target_wifi_passwd.c_str() );
        WiFi.begin( target_wifi_ssid.c_str(), target_wifi_passwd.c_str() );
        /* 还需要再检查链接是否成功 WiFi.status() == WL_CONNECTED */
    }
}

