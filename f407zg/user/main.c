#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "inout.h"

int main(void)
{ 
	delay_init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	pinMode(0,0);
	pinMode(1,0);
	while(1)
	{
		if(digitalRead(0))
			printf("get key 000\r\n");
		if(digitalRead(1))
			printf("get key 111\r\n");
		delay_ms(10);
	}
}
