#include "driver.h"
#include "stdio.h"
#include "pwm.h"

void motor_init(void)
{
	TIM2_CH34_Init(MAX_ARR,0);
    TIM12_CH12_Init(MAX_ARR,0);
}

void motor_set_speed(int speed_L,int speed_R)
{
    // if(RUNNING == 0)
    //     return ;
    if(speed_L>100 || speed_L<-100 || speed_R>100 || speed_R<-100){
        printf("set speed error!\r\n");
        return ;
    }
    if(speed_L >= 0){
        TIM_SetCompare3(TIM2,(int)(MAX_ARR*(1-speed_L/100.0)));
        TIM_SetCompare4(TIM2,MAX_ARR);
    }
    else if(speed_L < 0){
        TIM_SetCompare3(TIM2,MAX_ARR);
        TIM_SetCompare4(TIM2,(int)(MAX_ARR*(1+speed_L/100.0)));
    }
    if(speed_R >= 0){
        TIM_SetCompare1(TIM12,(int)(MAX_ARR*(1-speed_R/100.0)));
        TIM_SetCompare2(TIM12,MAX_ARR);
    }
    else if(speed_R < 0){
        TIM_SetCompare1(TIM12,MAX_ARR);
        TIM_SetCompare2(TIM12,(int)(MAX_ARR*(1+speed_R/100.0)));
    }
}
