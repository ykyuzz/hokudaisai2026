#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

/*
Definition of LED pins
*/
#define LED_PIN 25

/*
Definition of GPIO pins
*/
#define P_GAIN_PIN 26
#define I_GAIN_PIN 27
#define D_GAIN_PIN 28


/*
Definition of optointerrupter pins
*/
#define UPSTREAM_OPTOINTER_1_PIN 10
#define UPSTREAM_OPTOINTER_2_PIN 11
#define DOWNSTREAM_OPTOINTER_1_PIN 12
#define DOWNSTREAM_OPTOINTER_2_PIN 13


/*
Definition of Through-beam optosensor pins
*/
#define THROUGH_BEAM_OPTOINTER_LEFT_PIN 2
#define THROUGH_BEAM_OPTOINTER_RIGHT_PIN 3
#define THROUGH_BEAM_OPTOINTER_INIT_PIN 4



#define MAX_DUTY_CYCLE 0.6
/*
Because supply voltage is 5V, but the rated voltage of motor is 3V,
the duty cycle should be 60% or less.
*/



void main()
{
    float duty_cycle = 0.0;

    float led_bright_intervals[5] = {0.5, 1, 0.5, 1, 1};
    bool led_state = false;

    /*
    Initialize the ADC and GPIO pins
    */

    adc_init();

    adc_gpio_init(P_GAIN_PIN);
    adc_gpio_init(I_GAIN_PIN);
    adc_gpio_init(D_GAIN_PIN);

    adc_select_input(0);
    adc_select_input(1);
    adc_select_input(2);

    gpio_init(UPSTREAM_OPTOINTER_1_PIN);
    gpio_init(UPSTREAM_OPTOINTER_2_PIN);
    gpio_init(DOWNSTREAM_OPTOINTER_1_PIN);
    gpio_init(DOWNSTREAM_OPTOINTER_2_PIN);

    gpio_set_dir(UPSTREAM_OPTOINTER_1_PIN, GPIO_FUNC_PWM);
    gpio_set_dir(UPSTREAM_OPTOINTER_2_PIN, GPIO_FUNC_PWM);
    gpio_set_dir(DOWNSTREAM_OPTOINTER_1_PIN, GPIO_FUNC_PWM);
    gpio_set_dir(DOWNSTREAM_OPTOINTER_2_PIN, GPIO_FUNC_PWM);

    gpio_init(THROUGH_BEAM_OPTOINTER_LEFT_PIN);
    gpio_init(THROUGH_BEAM_OPTOINTER_RIGHT_PIN);
    gpio_init(THROUGH_BEAM_OPTOINTER_INIT_PIN);

    gpio_set_dir(THROUGH_BEAM_OPTOINTER_LEFT_PIN, GPIO_FUNC_PWM);
    gpio_set_dir(THROUGH_BEAM_OPTOINTER_RIGHT_PIN, GPIO_FUNC_PWM);
    gpio_set_dir(THROUGH_BEAM_OPTOINTER_INIT_PIN, GPIO_FUNC_PWM);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    /*
    PWM Settings
    */
    

    /*
    blink LED to indicate that the program is running and the microcontroller is working properly.
    */

    for(int i=0; i<5; i++){
        led_state = !led_state;
        gpio_put(LED_PIN, led_state);
        sleep_ms(led_bright_intervals[i] * 1000);
    }

    while(true){
        gpio_put(LED_PIN, 1);
         sleep_ms(500);
         gpio_put(LED_PIN, 0);
         sleep_ms(500);
    }
}
