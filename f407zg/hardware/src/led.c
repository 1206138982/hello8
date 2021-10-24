#include "led.h" 

void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10设置高，灯灭

}

void LED0_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  LED0_RCC_ENABLE();

  GPIO_InitStructure.GPIO_Pin = LED0_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(LED0_PORT, &GPIO_InitStructure);
  
  LED0_POWER_OFF();

}

void leds_init(char led_n)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	switch(led_n){
		case 0:
			LED0_RCC_ENABLE();
			GPIO_InitStructure.GPIO_Pin = LED0_PIN;
			GPIO_Init(LED0_PORT, &GPIO_InitStructure);
			LED0_POWER_OFF();
			break;
		case 1:
			LED1_RCC_ENABLE();
			GPIO_InitStructure.GPIO_Pin = LED1_PIN;
			GPIO_Init(LED1_PORT, &GPIO_InitStructure);
			LED1_POWER_OFF();
			break;
		default:
			printf("error input led_n\r\n");
			break;
	}
}

void led_set_status(char led_n,char status)
{
	switch (led_n)
	{
		case 0:
			if(status)
				LED0_POWER_ON();
			else
				LED0_POWER_OFF();
			break;
		case 1:
			if(status)
				LED1_POWER_ON();
			else
				LED1_POWER_OFF();
			break;
		default:
			break;
	}
}
