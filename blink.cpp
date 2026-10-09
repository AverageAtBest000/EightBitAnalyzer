#include "pico/stdlib.h"
#include <hardware/gpio.h>
#include <hardware/timer.h>
#include <stdio.h>

int main() {
  const int sample_cap = 100;
  int samples[sample_cap];
  long sample_times[sample_cap];

  stdio_init_all();

  const uint LED_PIN = 25;
  const uint READ_PIN = 2;
  const uint TEST_PIN = 3;

  gpio_init(LED_PIN);
  gpio_init(READ_PIN);
  gpio_init(TEST_PIN);

  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_set_dir(READ_PIN, GPIO_IN);
  gpio_set_dir(TEST_PIN, GPIO_OUT);

  gpio_put(TEST_PIN, false);

  gpio_pull_down(READ_PIN);

  bool test_state = false;
  int i = 0;
  int sample_count = 0;
  long start_time = time_us_64();

  while (sample_count < sample_cap) {

    int read_pin_state = gpio_get(READ_PIN);
    gpio_put(LED_PIN, read_pin_state);

    if (i == 10) {
      i = 0;
      test_state = !test_state;
      gpio_put(TEST_PIN, test_state);
    }
    i++;

    samples[sample_count] = read_pin_state;
    sample_times[sample_count] = time_us_64() - start_time;

    sample_count++;
    sleep_ms(50);
  }

  printf("[ ");
  for (int i = 0; i < sample_cap; i++) {
    printf("%d ", samples[i]);
    printf("%llu,%d\n", (unsigned long long)sample_times[i], samples[i]);
    if (i != sample_cap - 1)
      printf(",");
  }
  printf(" ]\n");
}
