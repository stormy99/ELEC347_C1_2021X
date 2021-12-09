#include <stm32f4xx.h>
#include <stdio.h>
#include "pll_config.h"
#include "usart.h"
#include "adc.h"
#include "dac.h"
#include "timer.h"

static double pot = 0;

int main() {
  PLL_Config();
  SystemCoreClockUpdate();
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN |
                  RCC_AHB1ENR_GPIOBEN;
  
  GPIOB->MODER &= ~(3u << (2 * 3));
  GPIOB->MODER |= (1 << (2 * 3));
  GPIOB->ODR |= (1 << 3);
  
  init_usart();
  init_adc();
  init_dac();
  clear_usart();
  
  send_usart_str("test\n\r");
  
  init_96khz_timer();
  
  while(1) {
    __WFI();
  }
  
}
