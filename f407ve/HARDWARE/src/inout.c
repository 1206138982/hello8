#include "inout.h"

void pinMode(char pin_n,char is_out)
{
    if(is_out){
        leds_init(pin_n);
    }
    else{

    }
}

void digitalWrite(char led_n,char status)
{
    led_set_status(led_n,status);
}
