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
	pinMode(0,0);
	pinMode(1,0);
	
	while(1)
	{
		if(digitalRead(0))
			printf("get key 0 push\r\n");
		if(digitalRead(1))
			printf("get key 1 push\r\n");
	}
}
