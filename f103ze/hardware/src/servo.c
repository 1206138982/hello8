#include "servo.h"
#include "stm32f10x.h"
#include "stdio.h"

void servo_attach(char servo_n)
{
    switch(servo_n){
        case 0:
            TIM2_CH2_init(200,7199);
            break;
        case 1:
            TIM2_CH3_init(200,7199);
            break;
        default:
            printf("cannot find servo\r\n");
            break;
    }
}

void servo_0_write(int angle)
{
    if(angle>=0 && angle<=180){
        angle = (int)(angle/180.0*20)+5;
        TIM_SetCompare2(TIM2,angle);
    }
    else{
        printf("error angle input in %s\r\n",__func__);
    }
}

void servo_1_write(int angle)
{
    if(angle>=0 && angle<=180){
        angle = (int)(angle/180.0*20)+5;
        TIM_SetCompare3(TIM2,angle);
    }
    else{
        printf("error angle input in %s\r\n",__func__);
    }
}
