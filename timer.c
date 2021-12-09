#include "timer.h"
#include <stm32f4xx.h>
#include "filter.h"

void init_96khz_timer(void) {
  RCC->APB1ENR|=RCC_APB1ENR_TIM4EN; //timer 4 clock enabled
  TIM4->DIER|=TIM_DIER_UIE;  //timer update interrupt enabled
  
  TIM4->PSC=5-1;
  TIM4->ARR=187;
  TIM4->CNT=0;  //zero timer counter
  NVIC->ISER[0]|=(1u<<30);  //timer 4 global interrupt enabled
  TIM4->CR1|=TIM_CR1_CEN; //start timer counter
}

void TIM4_IRQHandler(void) {  //TIMER 4 INTERRUPT SERVICE ROUTINE
  TIM4->SR&=~TIM_SR_UIF;  //clear interrupt flag in status register

  GPIOB->ODR |= (1 << 3);
  filter();
  GPIOB->ODR &= ~(1 << 3);
}
