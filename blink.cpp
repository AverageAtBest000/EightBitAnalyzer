#include "pico/stdlib.h"
#include <stdio.h>

int main() {

  stdio_init_all();

  const uint LED_PIN = 25;
  const uint READ_PIN = 2;

  gpio_init(LED_PIN);
  gpio_init(READ_PIN);

  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_set_dir(READ_PIN, GPIO_IN);

  gpio_pull_down(READ_PIN);
  while (true) {
    printf("%d\n", gpio_get(READ_PIN));
    if (gpio_get(READ_PIN) == 1)
      gpio_put(LED_PIN, 1);
    else
      gpio_put(LED_PIN, 0);

    sleep_ms(250);
  }
}
