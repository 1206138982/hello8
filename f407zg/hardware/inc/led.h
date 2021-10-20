#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define LED0_PORT   GPIOF
#define LED0_PIN    GPIO_Pin_9
#define LED0_RCC_ENABLE()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
#define LED0_POWER_ON()   GPIO_ResetBits(LED0_PORT,LED0_PIN)
#define LED0_POWER_OFF()   GPIO_SetBits(LED0_PORT,LED0_PIN)

#define LED1_PORT   GPIOF
#define LED1_PIN    GPIO_Pin_10
#define LED1_RCC_ENABLE()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE)
#define LED1_POWER_ON()   GPIO_ResetBits(LED1_PORT,LED1_PIN)
#define LED1_POWER_OFF()   GPIO_SetBits(LED1_PORT,LED1_PIN)

#define LED0 PFout(9)
#define LED1 PFout(10)

void LED_Init(void);
void leds_init(char led_n);
void led_set_status(char led_n,char status);

#endif
