#include "pico/stdlib.h"

int main() {
  const uint led_pin = 25;

  // init LED pin
  gpio_init(led_pin);
  gpio_set_dir(led_pin, GPIO_OUT);

  while (true) {

    // blink LED
    gpio_put(led_pin, true);
    sleep_ms(1000);
    gpio_put(led_pin, false);
    sleep_ms(1000);
  }
}
