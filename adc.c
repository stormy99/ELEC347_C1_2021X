#include "adc.h"
#include <stm32f4xx.h>

void init_adc() {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  //enable GPIOA
  GPIOA->MODER |= 3 << (2 * 6);  //set pin to analogue mode
  
  RCC->APB2ENR|=RCC_APB2ENR_ADC1EN; //ADC clock 1 enable
  ADC1->SQR1&=~ADC_SQR1_L;  //set number of conversions per sequence to 1
  ADC1->SQR3&=~ADC_SQR3_SQ1;  //clear channel select bits
  ADC1->SQR3|=0;  //set channel
  ADC1->CR2|=ADC_CR2_ADON;  //enable ADC
  
}

int read_input(void) {
  ADC1->CR2|=ADC_CR2_SWSTART; //start ADC conversion
  while((ADC1->SR&ADC_SR_EOC)==0){__NOP();}	//wait for ADC conversion complete
  return ADC1->DR;  //return converted value
}