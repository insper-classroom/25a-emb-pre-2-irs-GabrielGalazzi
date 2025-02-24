#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

const int RED_LED_PIN = 4;
const int GREEN_LED_PIN = 6;

volatile int redLedFlag = 0;
volatile int greenLedFlag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    redLedFlag = ! redLedFlag;
  }
  else if (events == 0x8) {
    greenLedFlag = !greenLedFlag;
  }
}


int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  gpio_init(RED_LED_PIN);
  gpio_set_dir(RED_LED_PIN, GPIO_OUT);

  gpio_init(GREEN_LED_PIN);
  gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);

  while (true) {

    if (redLedFlag == 1) {
      gpio_put(RED_LED_PIN, 1);
    }
    else if (redLedFlag == 0){
      gpio_put(RED_LED_PIN, 0);
    }

    if (greenLedFlag == 1) {
      gpio_put(GREEN_LED_PIN, 1);
    }
    else if (greenLedFlag == 0){
      gpio_put(GREEN_LED_PIN, 0);
    }


  }
}