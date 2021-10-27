#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "sccb.h"	
#include "ov2640.h"
#include "math.h"
#include "lcd.h"
#include "dcmi.h"
#include "sys.h"
#include "key.h"

int size_C=240,size_R=240;
u16 rgb_buf[240][240],gray;
u8 MAX_threshold=47,MIN_threshold=29 ;

int main(void)
{
	u16 i,j;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	delay_init(168);
	LCD_Init();
	POINT_COLOR=RED;//设置字体为红色
	while(OV2640_Init())//初始化OV2640
	{
		LCD_ShowString(30,130,240,16,16,"OV2640 ERR");
		delay_ms(200);
	    LCD_Fill(30,130,239,170,WHITE);
		delay_ms(200);
	}
	LCD_ShowString(30,130,200,16,16,"OV2640 OK");
	delay_ms(100);
	KEY_Init();
	OV2640_OutSize_Set(size_C,size_R);
    OV2640_RGB565_Mode();	//RGB565模式
    My_DCMI_Init();			//DCMI配置
    DCMI_DMA_Init((u32)rgb_buf,sizeof(rgb_buf)/4,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Enable);//DCMI DMA配置
    DCMI_Start(); 		//启动传输 
	OV2640_Special_Effects(2);
	
    while(1){
		LCD_SetCursor(0,0);  
		LCD_WriteRAM_Prepare();
		POINT_COLOR=RED;
		for(i=0;i<size_R;i++)
        {
            for(j=0;j<size_C;j++)
            {
                if(j==(size_C-1))
                {
                    LCD_SetCursor(0,i+1);  
                    LCD_WriteRAM_Prepare();		//开始写入GRAM
                }
                // LCD->LCD_RAM=rgb_buf[i][j];
                gray=((rgb_buf[i][j]>>11)*19595+((rgb_buf[i][j]>>5)&0x3f)*38469 +(rgb_buf[i][j]&0x1f)*7472)>>16;
                if(gray<=MAX_threshold&&gray>=MIN_threshold)                                   //这里是图像黑白二值化
                {
                    LCD->LCD_RAM=WHITE;
                }
                else
                {
                    LCD->LCD_RAM=BLACK;
                }

            }
        }
	}
}
