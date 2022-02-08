#include <Arduino.h>
#include <ESP8266WiFi.h>    //如果使用的是ESP32请将此处替换为“WIFI.h”
#include <WiFiClient.h>
#include <Ticker.h> 
 
#define WIFISSID "helloworld123456"
#define PASSWD  "HelloWorld123456"
String Key = "kEy3701a0635063d428";
 
const char *host = "123.57.38.57";
String comdata = "";
String KeyMark = "<key>"+Key+"</key>";
 
Ticker flipper;
WiFiClient client;
 
void flip() { //间隔一段时间发送一次数据用来维持连接
   client.print(KeyMark);
}
 
void setup()
{
    Serial.begin(115200);
    Serial.println("Connecting...\n");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFISSID,PASSWD); // change it to your ussid and password
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
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
 
void loop()
{
  while (Serial.available() > 0)      //检测串口是否有用户数据
    {
        comdata += char(Serial.read());
        delay(2);
    }
    while (client.available() > 0)   //打印服务器返回的数据
        {
          char c = client.read();
          Serial.write(c);
        }
    if (comdata.length() > 0)
    {
        String SendMsg = comdata + KeyMark;
        //Serial.println(SendMsg);  //选择是否打印出用户输入
        client.print(SendMsg);
        comdata = "";
    }
 
}
