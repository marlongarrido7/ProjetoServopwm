#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22  // Pino onde o servomotor está conectado

void set_servo_angle(uint slice, uint level) {
    pwm_set_gpio_level(SERVO_PIN, level);
    sleep_ms(5000); // Aguarda 5 segundos
}

int main() {
    stdio_init_all();
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    
    pwm_set_clkdiv(slice, 125.0);
    pwm_set_wrap(slice, 20000);
    pwm_set_enabled(slice, true);
    
    // Posiciona o servo em 180 graus (2400us)
    set_servo_angle(slice, 2400);
    
    // Posiciona o servo em 90 graus (1470us)
    set_servo_angle(slice, 1470);
    
    // Posiciona o servo em 0 graus (500us)
    set_servo_angle(slice, 500);
    
    // Movimentação suave entre 0 e 180 graus
    while (true) {
        for (uint level = 500; level <= 2400; level += 5) {
            pwm_set_gpio_level(SERVO_PIN, level);
            sleep_ms(10);
        }
        for (uint level = 2400; level >= 500; level -= 5) {
            pwm_set_gpio_level(SERVO_PIN, level);
            sleep_ms(10);
        }
    }
}