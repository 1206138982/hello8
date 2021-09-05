#include "inout.h"
#include "stm32f10x.h"
#include "key_c8.h"

char KEY0_PUSH = 0;
char KEY1_PUSH = 0;

void pinMode(char pin_n,char is_out)
{
    if(is_out){
        leds_init(pin_n);
    }
    else{
        keys_init(pin_n);
    }
}

void digitalWrite(char led_n,char status)
{
    led_set_status(led_n,status);
}

char digitalRead(char key_n)
{
    switch(key_n){
        case 10:
            if(KEY0_PUSH){
                KEY0_PUSH = 0;
                return 1;
            }
            else{
                return 0;
            }
        case 11:
            if(KEY1_PUSH){
                KEY1_PUSH = 0;
                return 1;
            }
            else{
                return 0;
            }
        default:
            return 0;
    }
}
