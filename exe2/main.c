  #include "hardware/gpio.h"
  #include "pico/stdlib.h"
  #include <stdio.h>

  const int BTN_PIN_R = 28;
  const int LED_PIN = 4;

  volatile int ledFlag = 0;
  volatile uint64_t lastPressTime = 0;

  void debouncingButton(int input){

    int loopFlag = 1;

    while (loopFlag == 1){

    
        while (!gpio_get(input)) {
          sleep_ms(5);
        };
        sleep_ms(20);
        
        if (gpio_get(input)){

          loopFlag = 0;

        }

    }

    return;

  }

  void btn_callback(uint gpio, uint32_t events) {

    if (time_us_64() - lastPressTime > 50000) { //rise edge
      lastPressTime = time_us_64();
      ledFlag = !ledFlag;
    }
  }

  int main() {
    stdio_init_all();

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_RISE, true, &btn_callback);


    while (true) {
      printf("%i\n", lastPressTime);
      if(ledFlag == 1) {
        printf("LIGUEI MAIN\n");
        gpio_put(LED_PIN, 1);
      }
      else if (ledFlag == 0){
        printf("DESLIGUEI MAIN\n");
        gpio_put(LED_PIN, 0);
      }
    }
  }