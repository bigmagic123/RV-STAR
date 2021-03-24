// See LICENSE for license details.
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "nuclei_sdk_soc.h"
#include "nuclei_sdk_hal.h"

void led_config(void)
{
    for(int i=0; i<LEDn; i++)
    {
        gd_rvstar_led_init(i);
        gd_rvstar_led_on(i);
        delay_1ms(1000);
        gd_rvstar_led_off(i);
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
    led_config();

    while(1)
    {
        for(int i=0; i<LEDn; i++)
        {
            gd_rvstar_led_toggle(i);
            delay_1ms(1000);
        }
    }
}

