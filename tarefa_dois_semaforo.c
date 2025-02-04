#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#define btn_pin 5
#define debounce_delay_us 200000
#define led1_pin 11
#define led2_pin 12
#define led3_pin 13
#define led_interval_ms 3000

static volatile uint8_t led_index = 0;
static volatile bool timer_active = false;

static void handle_button_press(uint gpio, uint32_t events);
int64_t led_timer_callback(alarm_id_t alarm_id, void *user_data);

int main()
{
    stdio_init_all();

    // configura pinos dos leds como saída
    gpio_init(led1_pin); gpio_set_dir(led1_pin, GPIO_OUT); gpio_put(led1_pin, 0);
    gpio_init(led2_pin); gpio_set_dir(led2_pin, GPIO_OUT); gpio_put(led2_pin, 0);
    gpio_init(led3_pin); gpio_set_dir(led3_pin, GPIO_OUT); gpio_put(led3_pin, 0);

    // configura botão com pull-up e interrupção
    gpio_init(btn_pin);
    gpio_set_dir(btn_pin, GPIO_IN);
    gpio_pull_up(btn_pin);
    gpio_set_irq_enabled_with_callback(btn_pin, GPIO_IRQ_EDGE_FALL, true, &handle_button_press);

    while (true)
    {   printf("Sistema ligado!\n");
        sleep_ms(10000); // loop ocioso
    }
}

// Função de interrupção acionada pelo botão
static void handle_button_press(uint gpio, uint32_t events)
{
    static volatile uint32_t last_press_time = 0;

    // Ignora interrupções de outros pinos
    if (gpio != btn_pin)
        return;

    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // verifica debounce e ativa temporizador
    if (current_time - last_press_time > debounce_delay_us)
    {
        if (!gpio_get(btn_pin) && !timer_active)
        {
            led_index = 0;
            timer_active = true;
            add_alarm_in_ms(1, led_timer_callback, NULL, false);
        }
        last_press_time = current_time;
    }
}
// Função de callback para controlar os LEDs em intervalos definidos
int64_t led_timer_callback(alarm_id_t alarm_id, void *user_data)
{
    // acende leds conforme índice
    gpio_put(led1_pin, led_index <= 0);
    gpio_put(led2_pin, led_index <= 1);
    gpio_put(led3_pin, led_index <= 2);

    timer_active = (led_index < 3);

    led_index++;
    return timer_active ? (led_interval_ms * 1000) : 0;
}
