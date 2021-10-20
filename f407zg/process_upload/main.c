#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "inout.h"

int main(void)
{ 
	delay_init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
// user init functions
	while(1)
	{
// user while functions
	}
}
