// See LICENSE for license details.
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "nuclei_sdk_soc.h"
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


/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    int state = 0;
    user_gpio_init();

    while(1)
    {
        state++;
        delay_1ms(1000);
        rgb_toggle(state);
    }
}
