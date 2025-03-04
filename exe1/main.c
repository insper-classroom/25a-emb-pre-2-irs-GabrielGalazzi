#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;

volatile int fallFlag = 0;
volatile int riseFlag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    //printf("fall \n");
    fallFlag  = 1;
  } else if (events == 0x8) { // rise edge
    //printf("rise \n");
    riseFlag = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if(fallFlag ==1){
      printf("fall \n");
      fallFlag =  0;
    }
    else if( riseFlag == 1){
      printf("rise \n");
      riseFlag = 0;
    }
  }
}
