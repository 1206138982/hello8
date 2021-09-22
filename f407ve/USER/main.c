#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "exti.h"

int main(void)
{ 
	uart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	EXTIX_Init();
	pinMode(0,1);
	pinMode(1,1);
	
	while(1)
	{
		digitalWrite(0,1);
		digitalWrite(1,0);
		delay_ms(1000);
		digitalWrite(0,0);
		digitalWrite(1,1);
		delay_ms(1000);
		printf("hello worrld\r\n");
	}
}
