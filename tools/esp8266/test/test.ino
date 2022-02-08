#include <Arduino.h>
#include <ESP8266WiFi.h>

String comdata = "";
String wifi_ssid = "";
String wifi_password = "";
int wifi_ssid_is_ready = 0;
int wifi_password_is_ready = 0;
int uart_rx_enable = 1;

void get_wifi_info(void)
{
    while(true){
        while (Serial.available() > 0){
            comdata += char(Serial.read());  //每次读一个char字符，并相加
            delay(2);
        }
        if (comdata.length() > 0){
            Serial.print("length:");
            Serial.println(comdata.length());
            Serial.println(comdata); //打印接收到的字符
            if(wifi_ssid_is_ready){
                Serial.println("set the wifi ssid");
                wifi_ssid.concat(comdata);
                wifi_ssid_is_ready = 0;
                Serial.println(wifi_ssid.length());
                Serial.println(wifi_ssid);
            }
            else if(wifi_password_is_ready){
                Serial.println("set the wifi password");
                wifi_password.concat(comdata);
                wifi_password_is_ready = 0;
                Serial.println(wifi_password.length());
                Serial.println(wifi_password);
            }
            if(comdata.compareTo("wifi_ssid") == 0){
                wifi_ssid_is_ready = 1;
                Serial.print("OK");
            }
            else if(comdata.compareTo("wifi_password") == 0){
                wifi_password_is_ready = 1;
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

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    get_wifi_info();
    WiFi.begin(wifi_ssid,wifi_password); // change it to your ussid and password
    Serial.println("Connecting......");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("connect to WIFI success!!");
}

void loop()
{
    Serial.println(wifi_ssid);
    Serial.println(wifi_password);
    delay(3000);
}
