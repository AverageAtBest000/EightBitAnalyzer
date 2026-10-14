#include "pico/stdlib.h"
#include "shared.h"
#include <bitset>
#include <cstdint>
#include <hardware/gpio.h>
#include <hardware/timer.h>
#include <initializer_list>
#include <iostream>
#include <pico/time.h>
#include <pico/types.h>
#include <stdio.h>
#include <sys/_intsup.h>

int sum(std::initializer_list<uint8_t> list);
void startPin(const uint PIN, bool isOut);

int main() {
  const int sample_cap = num_samples;
  uint8_t samples[sample_cap];
  uint64_t sample_times[sample_cap];

  stdio_init_all();

  std::uint8_t states(0);

  const uint LED_PIN = 25;

  const uint PIN1 = 2;
  const uint PIN2 = 0;
  const uint PIN3 = 0;
  const uint PIN4 = 0;
  const uint PIN5 = 0;
  const uint PIN6 = 0;
  const uint PIN7 = 0;
  const uint PIN8 = 0;

  const uint TEST_PIN = 3;

  startPin(LED_PIN, GPIO_OUT);
  startPin(PIN1, GPIO_IN);
  startPin(PIN2, GPIO_IN);
  startPin(PIN3, GPIO_IN);
  startPin(PIN4, GPIO_IN);
  startPin(PIN5, GPIO_IN);
  startPin(PIN6, GPIO_IN);
  startPin(PIN7, GPIO_IN);
  startPin(PIN8, GPIO_IN);
  startPin(TEST_PIN, GPIO_OUT);

  gpio_pull_down(PIN1);
  gpio_pull_down(PIN2);
  gpio_pull_down(PIN3);
  gpio_pull_down(PIN4);
  gpio_pull_down(PIN5);
  gpio_pull_down(PIN6);
  gpio_pull_down(PIN7);
  gpio_pull_down(PIN8);

  while (true) {

    int ch = getchar();
    if (ch != 'g')
      continue;

    bool test_state = false;
    int i = 0;
    int sample_count = 0;
    uint64_t start_time = time_us_64();

    gpio_put(TEST_PIN, false);
    absolute_time_t next_sample = get_absolute_time();

    while (sample_count < sample_cap) {
      sleep_until(next_sample);
      sample_times[sample_count] = time_us_64() - start_time;

      uint8_t pin1_state = gpio_get(PIN1);
      uint8_t pin2_state = gpio_get(PIN2) * 2;
      uint8_t pin3_state = gpio_get(PIN3) * 4;
      uint8_t pin4_state = gpio_get(PIN4) * 8;
      uint8_t pin5_state = gpio_get(PIN5) * 16;
      uint8_t pin6_state = gpio_get(PIN6) * 32;
      uint8_t pin7_state = gpio_get(PIN7) * 64;
      uint8_t pin8_state = gpio_get(PIN8) * 128;

      gpio_put(LED_PIN, pin1_state);

      if (i == 10) {
        i = 0;
        test_state = !test_state;
        gpio_put(TEST_PIN, test_state);
      }
      i++;

      samples[sample_count] =
          sum({pin1_state, pin2_state, pin3_state, pin4_state, pin5_state,
               pin6_state, pin7_state, pin8_state});

      sample_count++;
      next_sample = delayed_by_ms(next_sample, 50);
    }
    for (int i = 0; i < sample_cap; i++)
      std::cout << sample_times[i] << ',' << std::bitset<8>(samples[i]) << '\n';

    std::cout.flush();
  }

  return 0;
}

int sum(std::initializer_list<uint8_t> list) {
  uint8_t sum = 0;

  for (auto i : list) {
    sum += i;
  }

  return sum;
}

void startPin(const uint PIN, bool isOut) {
  gpio_init(PIN);
  gpio_set_dir(PIN, isOut);
}
