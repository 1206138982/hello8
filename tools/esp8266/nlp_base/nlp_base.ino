#include <Arduino.h>
#include <ESP8266WiFi.h>    //如果使用的是ESP32请将此处替换为“WIFI.h”
#include <WiFiClient.h>
#include <Ticker.h> 

#define USE_SOFTWARE_SERIAL    0   //使用 SoftwareSerial 语音识别出错概率较高，一般前一两个汉字大概率会出错
#define LED_PIN    2

#if defined(USE_SOFTWARE_SERIAL) && USE_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
SoftwareSerial uart1(14,12);//RX=d5,GPIO14,TX=d6,GPIO12
#define SerialX uart1
#else
#define SerialX Serial
#endif

// String Key = "kEy3701a0635063d428";
const char *host = "123.57.38.57";
String comdata = "";
String KeyMark = "";
// String KeyMark = "<key>"+Key+"</key>";

String nlp_key = "";
String wifi_ssid = "";
String wifi_password = "";
int nlpkey_is_ready = 0;
int wifi_ssid_is_ready = 0;
int wifi_password_is_ready = 0;
 
Ticker flipper;
WiFiClient client;
 
void flip() { //间隔一段时间发送一次数据用来维持连接
   client.print(KeyMark);
}
 
void setup()
{
    int led_state = 1,i;
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN,led_state);
#if defined(USE_SOFTWARE_SERIAL) && USE_SOFTWARE_SERIAL
    uart1.begin(115200);
#endif
    WiFi.mode(WIFI_STA);
    Serial.println();
    delay(500);
    Serial.println("ready to receive data \r\r\n");
    get_wifi_info();
    WiFi.begin(wifi_ssid,wifi_password);
    Serial.println("Connecting...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        digitalWrite(LED_PIN,led_state);
        if(led_state)
            led_state = 0;
        else
            led_state = 1;
    }
    Serial.println();
    Serial.println("connect to WIFI success!!");
    digitalWrite(LED_PIN,0);
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
        SerialX.write(c);
    }
    if(client_rece){
      client_rece = 0;
      SerialX.print("\r\r\n");
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
        while (SerialX.available() > 0){
            comdata += char(SerialX.read());  //每次读一个char字符，并相加
            delay(2);
        }
        if (comdata.length() > 0){
            if(nlpkey_is_ready){
                nlp_key.concat(comdata);
                KeyMark = "<key>"+nlp_key+"</key>";
                nlpkey_is_ready = 0;
                SerialX.print("OK");
            }
            if(wifi_ssid_is_ready){
                wifi_ssid.concat(comdata);
                wifi_ssid_is_ready = 0;
                SerialX.print("OK");
            }
            else if(wifi_password_is_ready){
                wifi_password.concat(comdata);
                wifi_password_is_ready = 0;
                SerialX.print("OK");
            }
            if(comdata.compareTo("nlp_key") == 0){
                nlpkey_is_ready = 1;
                SerialX.print("OK");
            }
            if(comdata.compareTo("wifi_ssid") == 0){
                wifi_ssid_is_ready = 1;
                SerialX.print("OK");
            }
            else if(comdata.compareTo("wifi_password") == 0){
                wifi_password_is_ready = 1;
                SerialX.print("OK");
            }
            else if(comdata.compareTo("AT")==0 || comdata.compareTo("at")==0){
                SerialX.print("OK");
            }
            comdata = "";
        }
        if(wifi_ssid.length()>0 && wifi_password.length()>0){
            Serial.println("get the ssid and password");
            break;
        }
    }
}
