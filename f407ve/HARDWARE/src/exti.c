#include "exti.h"
#include "delay.h" 
#include "key.h"
#include "stdio.h"

void JumpToISP(void);

void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(WK_UP==1)	 
	{
		printf("jump to isp model\r\n");
		JumpToISP();
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	
//外部中断9_5服务程序
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);	//消抖
// 	if(KEY0==0)	  
// 	{				 
//    LED1=!LED1; 
// 	 EXTI_ClearITPendingBit(EXTI_Line9);//清除LINE9上的中断标志位 
// 	}	
// 	if(KEY1==0)	  
// 	{				 
//    LED2=!LED2; 
// 	 EXTI_ClearITPendingBit(EXTI_Line8);//清除LINE8上的中断标志位 
// 	}		
	 
}
	   
//外部中断初始化程序

void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource9);//PB9 连接到中断线9
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource8);//PB8 连接到中断线8

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 连接到中断线0
	
  /* 配置EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置
	
	/* 配置EXTI_Line8,9 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line8 | EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}

#define ISPAddress (uint32_t)0x1FFF0000 
void JumpToISP(void)
{
    //程序跳转不复位外设，建议对一些可能导致问题的外设进行反初始化DeInit，如SysTick。
    //看门狗一旦初始化不能被关闭，因此如果使用了看门狗，则在调用该函数前，必须先复位系统，并在初始化看门狗之前调用该函数。
    uint32_t ispJumpAddr;//ISP程序的跳转地址，既程序入口
    uint32_t ispSpValue;//IAP程序的SP初值，即栈指针
    void (*Jump_To_ISP)(void);//定义一个函数指针

    
    SysTick->CTRL=0x00;       //关闭计数器
    SysTick->VAL =0X00;       //清空计数器	
//		__set_FAULTMASK(1);        //关闭所有中断
		//__set_CONTROL(0);		  //将PSP指针切换为MSP指针，适用于APP使用OS情况
//        NVIC_SystemReset();      //NVIC重置
    if (((*(__IO uint32_t*)ISPAddress) & 0x2FFE0000 ) == 0x20000000)
    { 
        ispSpValue  = *(__IO uint32_t*)ISPAddress;
        ispJumpAddr = *(__IO uint32_t*)(ISPAddress+4);
            
        /* 初始化 Stack Pointer */
        __set_MSP(ispSpValue);
            
        /* Jump to isp */
        Jump_To_ISP = (void (*)(void))ispJumpAddr;
        Jump_To_ISP();
    }
}
