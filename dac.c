#include "stm32f4xx.h"
#include "dac.h"
#include "filter.h"

void init_dac(void) {
  
  GPIOB->MODER &= ~(3 << (2 * 14));
  GPIOB->MODER |= (1u << (2 * 14)); 
  GPIOB->PUPDR |= (1u << (2 * 14));
  
  GPIOA->MODER |= (3u << (2 * 4)); //DAC output set to analogue operation
  
  RCC->APB1ENR |= RCC_APB1ENR_DACEN;  //Enable DAC Clock
  DAC->CR |= DAC_CR_EN1;  //Enable DAC 1
}
