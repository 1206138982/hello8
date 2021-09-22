#include "exti.h"
#include "delay.h" 
#include "key.h"
#include "stdio.h"

extern char KEY0_PUSH;
extern char KEY1_PUSH;
void JumpToISP(void);

void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//����
	if(WK_UP==1)	 
	{
		printf("jump to isp model\r\n");
		// JumpToISP();
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	
//�ⲿ�ж�9_5�������
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);	//����
// 	if(KEY0==0)	  
// 	{				 
//    LED1=!LED1; 
// 	 EXTI_ClearITPendingBit(EXTI_Line9);//���LINE9�ϵ��жϱ�־λ 
// 	}	
// 	if(KEY1==0)	  
// 	{				 
//    LED2=!LED2; 
// 	 EXTI_ClearITPendingBit(EXTI_Line8);//���LINE8�ϵ��жϱ�־λ 
// 	}		
	 
}
	   
//�ⲿ�жϳ�ʼ������

void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource9);//PB9 ���ӵ��ж���9
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource8);//PB8 ���ӵ��ж���8

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 ���ӵ��ж���0
	
  /* ����EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����
	
	/* ����EXTI_Line8,9 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line8 | EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}

void EXTI3_IRQHandler(void)
{
	delay_ms(15);
  KEY0_PUSH = 1;
  // printf("push key 0!\r\n");
	EXTI_ClearITPendingBit(EXTI_Line3);  //���EXTI0��·����λ
}

void EXTI3_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
	
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI4_IRQHandler(void)
{
	delay_ms(15);
  KEY1_PUSH = 1;
  // printf("push key 1!\r\n");
	EXTI_ClearITPendingBit(EXTI_Line4);  //���EXTI0��·����λ
}

void EXTI4_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
	
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

#define ISPAddress (uint32_t)0x1FFF0000 
void JumpToISP(void)
{
    //������ת����λ���裬�����һЩ���ܵ��������������з���ʼ��DeInit����SysTick��
    //���Ź�һ����ʼ�����ܱ��رգ�������ʹ���˿��Ź������ڵ��øú���ǰ�������ȸ�λϵͳ�����ڳ�ʼ�����Ź�֮ǰ���øú�����
    uint32_t ispJumpAddr;//ISP�������ת��ַ���ȳ������
    uint32_t ispSpValue;//IAP�����SP��ֵ����ջָ��
    void (*Jump_To_ISP)(void);//����һ������ָ��

    
    SysTick->CTRL=0x00;       //�رռ�����
    SysTick->VAL =0X00;       //��ռ�����	
//		__set_FAULTMASK(1);        //�ر������ж�
		//__set_CONTROL(0);		  //��PSPָ���л�ΪMSPָ�룬������APPʹ��OS���
//        NVIC_SystemReset();      //NVIC����
    if (((*(__IO uint32_t*)ISPAddress) & 0x2FFE0000 ) == 0x20000000)
    { 
        ispSpValue  = *(__IO uint32_t*)ISPAddress;
        ispJumpAddr = *(__IO uint32_t*)(ISPAddress+4);
            
        /* ��ʼ�� Stack Pointer */
        __set_MSP(ispSpValue);
            
        /* Jump to isp */
        Jump_To_ISP = (void (*)(void))ispJumpAddr;
        Jump_To_ISP();
    }
}
