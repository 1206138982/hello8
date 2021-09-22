#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define LED0_PORT   GPIOA
#define LED0_PIN    GPIO_Pin_6
#define LED0_RCC_ENABLE()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE)
#define LED0_POWER_ON()   GPIO_ResetBits(LED0_PORT,LED0_PIN)
#define LED0_POWER_OFF()   GPIO_SetBits(LED0_PORT,LED0_PIN)

#define LED1_PORT   GPIOA
#define LED1_PIN    GPIO_Pin_7
#define LED1_RCC_ENABLE()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE)
#define LED1_POWER_ON()   GPIO_ResetBits(LED1_PORT,LED1_PIN)
#define LED1_POWER_OFF()   GPIO_SetBits(LED1_PORT,LED1_PIN)

#define LED1 PAout(6)
#define LED2 PAout(7)

void LED_Init(void);

#endif
