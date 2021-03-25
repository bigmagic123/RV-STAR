/*!
    \file  main.c
    \brief keyboard polling mode
    
    \version 2019-6-5, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/


#include <stdio.h>
#include "gd32vf103_libopt.h"
#include "nuclei_sdk_hal.h"

#define LED_G   LED1
#define LED_B   LED2
#define LED_R   LED3

#define LED_G_ON     gd_rvstar_led_on(LED_G)
#define LED_G_OFF    gd_rvstar_led_off(LED_G)

#define LED_B_ON     gd_rvstar_led_on(LED_B)
#define LED_B_OFF    gd_rvstar_led_off(LED_B)

#define LED_R_ON     gd_rvstar_led_on(LED_R)
#define LED_R_OFF    gd_rvstar_led_off(LED_R)

//gpio init
void user_gpio_init(void)
{
    gd_rvstar_led_init(LED_G);
    gd_rvstar_led_init(LED_B);
    gd_rvstar_led_init(LED_R);

    gd_rvstar_key_init(0, KEY_MODE_GPIO);
}

void rgb_toggle(int state)
{
    int cur_state = state % 3;
    if(cur_state == 0)
    {
        LED_G_ON;
        LED_B_OFF;
        LED_R_OFF;
    }

    if(cur_state == 1)
    {
        LED_G_OFF;
        LED_B_ON;
        LED_R_OFF;
    }

    if(cur_state == 2)
    {
        LED_G_OFF;
        LED_B_OFF;
        LED_R_ON;
    }
}

int main(void)
{
    int state = 0;
    user_gpio_init();

    while(1)
    {
        /* check whether the button is pressed */
        if(SET ==  gd_rvstar_key_state_get(0))
        {
            delay_1ms(50);
            /* check whether the button is pressed */
            if(SET == gd_rvstar_key_state_get(0))
            {
                /* toggle the LED */
                state++;
                rgb_toggle(state);
            }
            
            while(SET == gd_rvstar_key_state_get(0))
            {
            }
        }
    }    
}
