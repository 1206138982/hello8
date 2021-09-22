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
	LED_Init();
	EXTIX_Init();
	
	while(1)
	{
		LED0_POWER_ON();
		delay_ms(2000);
		LED0_POWER_OFF();
		delay_ms(200);
		printf("hello worrld\r\n");
	}
}
