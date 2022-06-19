/*
******************************************************************************
File:     main.c

*/

#include "stm32f0xx.h"
#include <stdio.h>

#define button ((GPIOA->IDR) & GPIO_IDR_0)
uint16_t ADCValue;        // ADC value after conversion
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */


//===========================================================================
void init_ADC(void);
void init_GPIO(void);
//===========================================================================

int main(void)
{
	init_GPIO();                                   // initialiZe switches to input and LEDs to output
	init_ADC();                                   //  initialiseADC
	while(button);                               // exits loop when PA0 is pushed

	while(1)
	{
		ADC1 -> CR|= ADC_CR_ADSTART;       // start ADC conversion
		while(  ((ADC1 -> ISR) &  ADC_ISR_EOC) == 0 ); // conversion complete with EOC flag in ISR goes high
		ADCValue = ADC1 -> DR;            // save ADC value to "ADCValue"
		GPIOC -> ODR =ADCValue;          // Display ADC value on the LEDs}
	}
}

void init_ADC(void){
	//ENABLE ANALOGUE PARAMETERS
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	ADC1->CFGR1  |= ADC_CFGR1_RES_1;
	ADC1->CFGR1   &= ~ADC_CFGR1_CONT;

	ADC1 -> CFGR1&= ~ADC_CFGR1_ALIGN;       // right alignment
	ADC1 -> CFGR1&= ~ADC_CFGR1_CONT;       // CONT = 0: single-shot mode
	ADC1 -> CHSELR|= ADC_CHSELR_CHSEL0;   // select channel 6
	ADC1 -> CR|= ADC_CR_ADEN;	     // Active ADC to be ready

	// wait for ADRDY flag to go high
	while(((ADC1-> ISR) &  ADC_ISR_ADRDY) == 0 );
}

void init_GPIO(void){
	//ENABLE CLOCK FOR BUTTON, SET BUTTON ANALOGUE MODE
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA -> MODER |= GPIO_MODER_MODER0; // configure PA0 to input mode
	GPIOA ->MODER |=  GPIO_MODER_MODER13_1;
	GPIOA ->MODER |=  GPIO_MODER_MODER14_1;
	//ENABLE CLOCK FOR LED, SET LED MODE
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER9_0;
	GPIOC -> ODR= 0x00; // Turn LEDs OFF
}

























