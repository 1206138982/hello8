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
// user init functions 	
	while(1)
	{
// user while functions
	}

}
