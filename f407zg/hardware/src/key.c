#include "key.h"
#include "delay.h" 

void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOA,GPIOBʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9; //KEY1 KEY0 ��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��PB8,PB9
	
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
 
} 

void KEY0_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOA,GPIOBʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��PB8,PB9

}

void KEY1_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOA,GPIOBʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��PB8,PB9
}

void keys_init(char key_n)
{
	switch (key_n)
	{
	case 0:
		KEY0_init();
		EXTI8_Init();
		break;
	
	case 1:
		KEY1_init();
		EXTI9_Init();
		break;

	default:
		break;
	}
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!

uint8_t Key_Flag=0;//按键键值

uint8_t  key_up=1;//按键按松开标志

uint16_t Key_times[3]={0,0,0};//检测到按键按下去的次数

uint16_t Key_Time_out[3]={0,0,0};//如果按键未持续按下，则认为是抖动，抖动超时后，清除按键记次值



void KEY_Scan(void)
{	 
	
	if(Key_times[0]>0)
	{
		++Key_Time_out[0];
		
		if(Key_Time_out[0]>KeyShake_overflow)//检测是否超时
    {
			Key_Time_out[0]=0;//清除超时溢出
			Key_times[0]=0;   //清除按键记次
		}
	}
	
	if(Key_times[1]>0)
	{
		++Key_Time_out[1];
		
		if(Key_Time_out[1]>KeyShake_overflow)//检测是否超时
    {
			Key_Time_out[1]=0;//清除超时溢出
			Key_times[1]=0;   //清除按键记次
		}
	}
	
	if(Key_times[2]>0)
	{
		++Key_Time_out[2];
		
		if(Key_Time_out[2]>KeyShake_overflow)//检测是否超时
    {
			Key_Time_out[2]=0;//清除超时溢出
			Key_times[2]=0;   //清除按键记次
		}
	}
	
		
	if(KEY0==0||KEY1==0||WK_UP==1)
	{
		
		key_up=0;//当前有按键按下
		
    if(WK_UP==1)
			{
				 Key_times[0]++;
				
				 if(Key_times[0]>=KeyShake_Time)
				 { 
					 Key_Time_out[0]=0;//清除超时溢出
					 Key_times[0]=0;//清除一次计数
				   Key_Flag=1;//如果连续检测30mS次，检测到按键一直在按下，则确定是按键按下去了

				 }
			}
		
		else if(KEY0==0)
			{	
				 Key_times[1]++;
				
				 if(Key_times[1]>=KeyShake_Time)
				 {
					 Key_Time_out[1]=0;//清除超时溢出
           Key_times[1]=0;//清除一次计数					 
				   Key_Flag= 2;      //返回按键值
			 
				 } 
				
			}
		else if(KEY1==0)
			{
				Key_times[2]++;
				
				if(Key_times[2]>=KeyShake_Time)
				 {
					 Key_Time_out[2]=0;//清除超时溢出
           Key_times[2]=0;//清除一次计数					 
				   Key_Flag= 3;      //返回按键值
						
				 }	
				
			}
	}
	else if(KEY0==1&&KEY1==1&&WK_UP==0)//无任何按键按下
	{
		
		key_up=1;
		
	}
	
 		
}
