/*!
    \file  main.c
    \brief the example of EXTI which generates an interrupt request and toggle the LED

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

static int key_cnt = 0;

#define USER_KEY_PORT           GPIOA
#define USER_KEY_PIN            GPIO_PIN_0

#define LED_G   LED1
#define LED_B   LED2
#define LED_R   LED3

#define LED_G_ON     gd_rvstar_led_on(LED_G)
#define LED_G_OFF    gd_rvstar_led_off(LED_G)

#define LED_B_ON     gd_rvstar_led_on(LED_B)
#define LED_B_OFF    gd_rvstar_led_off(LED_B)

#define LED_R_ON     gd_rvstar_led_on(LED_R)
#define LED_R_OFF    gd_rvstar_led_off(LED_R)

/*!
    \brief      this function handles external lines 10 to 15 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/

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

void EXTI0_IRQHandler(void)
{
    exti_interrupt_flag_clear(EXTI_0);
    key_cnt = key_cnt + 1;
    rgb_toggle(key_cnt);
    // if (RESET != exti_interrupt_flag_get(KEY_B_PIN)){
    //     exti_interrupt_flag_clear(KEY_B_PIN);

    //     if(RESET == gd_eval_key_state_get(KEY_B_PIN)){
    //         gd_eval_led_toggle(LED3);
    //     }
    // }
}

//gpio exti
void key_exit(void)
{
        rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_AF);
        /* configure button pin as input */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_0);


        /* configure key EXTI line */
    exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_FALLING);


        // ECLIC_Register_IRQ(EXTI0_IRQn, ECLIC_NON_VECTOR_INTERRUPT,
        //                             ECLIC_LEVEL_TRIGGER, 1, 1,
        //                             EXTI0_IRQn_IRQHandler);

        
    /* Global interrupt enable*/
    __enable_irq();

    /* connect key EXTI line to key GPIO pin */
    gpio_exti_source_select(GPIOA, GPIO_PIN_0);


    exti_interrupt_flag_clear(EXTI_0);


}
//gpio init
void user_gpio_init(void)
{
    gd_rvstar_led_init(LED_G);
    gd_rvstar_led_init(LED_B);
    gd_rvstar_led_init(LED_R);

    //gd_rvstar_key_init(0, KEY_MODE_GPIO);
    //key_exit();
}

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/

int main(void)
{
    user_gpio_init();





    /* enable the Wakeup clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_AF);

    /* configure button pin as input */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_0);

    /* enable and set key EXTI interrupt to the lowest priority */
    ECLIC_Register_IRQ(EXTI0_IRQn,ECLIC_NON_VECTOR_INTERRUPT,ECLIC_LEVEL_TRIGGER,1,1,EXTI0_IRQHandler);

    /* Global interrupt enable */
    __enable_irq();
    /* connect key EXTI line to key GPIO pin */
    gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_0);

    /* configure key EXTI line */
    exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_interrupt_flag_clear(EXTI_0);
    while(1){
    }


    while (1);
}

