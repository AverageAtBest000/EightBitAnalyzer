#include "pico/stdlib.h"
#include "shared.h"
#include <bitset>
#include <cstdint>
#include <hardware/gpio.h>
#include <hardware/timer.h>
#include <iostream>
#include <pico/time.h>
#include <pico/types.h>
#include <stdio.h>
#include <sys/_intsup.h>

void startPin(const uint PIN, bool isOut);

int main() {
  const int sample_cap = num_samples;
  uint8_t samples[sample_cap];
  uint64_t sample_times[sample_cap];

  stdio_init_all();

  std::uint8_t states(0);

  const uint LED_PIN = 25;

  const uint PIN1 = 2;
  const uint PIN2 = 3;
  const uint PIN3 = 4;
  const uint PIN4 = 5;
  const uint PIN5 = 6;
  const uint PIN6 = 7;
  const uint PIN7 = 8;
  const uint PIN8 = 9;

  startPin(LED_PIN, GPIO_OUT);
  startPin(PIN1, GPIO_IN);
  startPin(PIN2, GPIO_IN);
  startPin(PIN3, GPIO_IN);
  startPin(PIN4, GPIO_IN);
  startPin(PIN5, GPIO_IN);
  startPin(PIN6, GPIO_IN);
  startPin(PIN7, GPIO_IN);
  startPin(PIN8, GPIO_IN);

  while (true) {

    int ch = getchar();
    if (ch != 'g')
      continue;

    int sample_count = 0;
    uint64_t start_time = time_us_64();

    uint8_t pin_states = 0;
    absolute_time_t next_sample = get_absolute_time();

    while (sample_count < sample_cap) {

      sleep_until(next_sample);
      sample_times[sample_count] = time_us_64() - start_time;

      uint32_t all_states = gpio_get_all();

      pin_states = (uint8_t)(all_states >> PIN1);

      samples[sample_count] = pin_states;

      next_sample = delayed_by_ms(next_sample, 50);

      sample_count++;
    }

    for (int i = 0; i < sample_cap; i++)
      std::cout << sample_times[i] << ',' << std::bitset<8>(samples[i]) << '\n';

    std::cout.flush();
  }

  return 0;
}

void startPin(const uint PIN, bool isOut) {
  gpio_init(PIN);
  gpio_set_dir(PIN, isOut);

  if (!isOut)
    gpio_pull_down(PIN);
}
