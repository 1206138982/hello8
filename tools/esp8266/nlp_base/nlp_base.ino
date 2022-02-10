#include <Arduino.h>
#include <ESP8266WiFi.h>    //如果使用的是ESP32请将此处替换为“WIFI.h”
#include <WiFiClient.h>
#include <Ticker.h> 

String Key = "kEy3701a0635063d428";
const char *host = "123.57.38.57";
String comdata = "";
String KeyMark = "<key>"+Key+"</key>";

String wifi_ssid = "";
String wifi_password = "";
int wifi_ssid_is_ready = 0;
int wifi_password_is_ready = 0;
 
Ticker flipper;
WiFiClient client;
 
void flip() { //间隔一段时间发送一次数据用来维持连接
   client.print(KeyMark);
}
 
void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    Serial.println();
    Serial.println("ready to receive data");
    get_wifi_info();
    WiFi.begin(wifi_ssid,wifi_password);
    Serial.println("Connecting...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("connect to WIFI success!!");
    if (!client.connect("123.57.38.57", 443))
    {
        Serial.println("Connection to host failed");
        delay(1000);
        return;
    }
    else{
          client.print(KeyMark);
    }
    flipper.attach(180, flip);//每隔180秒执行一次回调函数
}

int client_rece = 0;
void loop()
{
    while (Serial.available() > 0)      //检测串口是否有用户数据
    {
        comdata += char(Serial.read());
        delay(2);
    }
    while (client.available() > 0)   //打印服务器返回的数据
    {
        client_rece = 1;
        char c = client.read();
        Serial.write(c);
    }
    if(client_rece){
      client_rece = 0;
      Serial.write('\r');
      Serial.write('\n');
    }
    if (comdata.length() > 0)
    {
        String SendMsg = comdata + KeyMark;
        //Serial.println(SendMsg);  //选择是否打印出用户输入
        client.print(SendMsg);
        comdata = "";
    }
 
}

void get_wifi_info(void)
{
    while(true){
        while (Serial.available() > 0){
            comdata += char(Serial.read());  //每次读一个char字符，并相加
            delay(2);
        }
        if (comdata.length() > 0){
            if(wifi_ssid_is_ready){
                wifi_ssid.concat(comdata);
                wifi_ssid_is_ready = 0;
                Serial.print("OK");
            }
            else if(wifi_password_is_ready){
                wifi_password.concat(comdata);
                wifi_password_is_ready = 0;
                Serial.print("OK");
            }
            if(comdata.compareTo("wifi_ssid") == 0){
                wifi_ssid_is_ready = 1;
                Serial.print("OK");
            }
            else if(comdata.compareTo("wifi_password") == 0){
                wifi_password_is_ready = 1;
                Serial.print("OK");
            }
            else if(comdata.compareTo("AT")==0 || comdata.compareTo("at")==0){
                Serial.print("OK");
            }
            comdata = "";
        }
        if(wifi_ssid.length()>0 && wifi_password.length()>0){
            Serial.println("get the ssid and password");
            break;
        }
    }
}
