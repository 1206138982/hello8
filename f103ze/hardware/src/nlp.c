#include "led_c8.h"
#include "stm32f10x.h"
#include "stdio.h"
#include "usart.h"
#include "esp8266.h"

unsigned char wifi_ssid[] = "helloworld123456";
unsigned char wifi_password[] = "HelloWorld123456";

uint8_t setup_nlp(void)
{
	Usart2_Init(115200);
	ESP8266_Clear();
    ESP8266_SendCmd("AT","OK");

/*    AT command test    */
	if(!ESP8266_SendCmd("AT","OK")){
		UsartPrintf(USART_DEBUG, "send AT success\r\n");
	}
	else{
		UsartPrintf(USART_DEBUG, "send AT fail\r\n");
        return 1;
	}
/*    send wifi ssid string    */
	if(!ESP8266_SendCmd("wifi_ssid","OK")){
		UsartPrintf(USART_DEBUG, "ready to send wifi_ssid\r\n");
	}
	else{
		UsartPrintf(USART_DEBUG, "send wifi_ssid not ready\r\n");
        return 1;
	}
	if(!ESP8266_SendCmd(wifi_ssid,"OK")){
		UsartPrintf(USART_DEBUG, "send wifi_ssid content success\r\n");
	}
	else{
		UsartPrintf(USART_DEBUG, "send wifi_ssid content fail\r\n");
        return 1;
	}
/*    send wifi password string    */
	if(!ESP8266_SendCmd("wifi_password","OK")){
		UsartPrintf(USART_DEBUG, "ready to send wifi_password\r\n");
	}
	else{
		UsartPrintf(USART_DEBUG, "send wifi_password not ready\r\n");
        return 1;
	}
	if(!ESP8266_SendCmd(wifi_password,"OK")){
		UsartPrintf(USART_DEBUG, "send wifi_password content success\r\n");
	}
	else{
		UsartPrintf(USART_DEBUG, "send wifi_password content fail\r\n");
        return 1;
	}

    return 0;
}
