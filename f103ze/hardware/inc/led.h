
#ifndef LED_H
#define LED_H

#define LED0_PORT   GPIOB
#define LED0_PIN    GPIO_Pin_5
#define LED0_RCC_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE)
#define LED0_POWER_ON()   GPIO_ResetBits(LED0_PORT,LED0_PIN)
#define LED0_POWER_OFF()   GPIO_SetBits(LED0_PORT,LED0_PIN)

#define LED1_PORT   GPIOE
#define LED1_PIN    GPIO_Pin_5
#define LED1_RCC_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE)
#define LED1_POWER_ON()   GPIO_ResetBits(LED1_PORT,LED1_PIN)
#define LED1_POWER_OFF()   GPIO_SetBits(LED1_PORT,LED1_PIN)

#define LED2_PORT   GPIOC
#define LED2_PIN    GPIO_Pin_13
#define LED2_RCC_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE)
#define LED2_POWER_ON()   GPIO_ResetBits(LED2_PORT,LED2_PIN)
#define LED2_POWER_OFF()   GPIO_SetBits(LED2_PORT,LED2_PIN)

#define POWER_G_IO_PORT						GPIOB
#define POWER_G_IO_PIN						GPIO_Pin_5
#define POWER_G_IO_RCC_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE)	
#define POWER_R_IO_PORT						GPIOA
#define POWER_R_IO_PIN						GPIO_Pin_5
#define POWER_R_IO_RCC_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)	
#define LED_PowerG()					do{ GPIO_SetBits(POWER_G_IO_PORT,POWER_G_IO_PIN); GPIO_ResetBits(POWER_R_IO_PORT,POWER_R_IO_PIN);	}while(0)
#define LED_PowerR()					do{ GPIO_ResetBits(POWER_G_IO_PORT,POWER_G_IO_PIN); GPIO_SetBits(POWER_R_IO_PORT,POWER_R_IO_PIN);	}while(0)
#define LED_PowerOff()					do{ GPIO_ResetBits(POWER_G_IO_PORT,POWER_G_IO_PIN); GPIO_ResetBits(POWER_R_IO_PORT,POWER_R_IO_PIN);	}while(0)

void LED_Init(void);
void leds_init(char led_n);
void led_set_status(char led_n,char status);

#endif
