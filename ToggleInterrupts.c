#include "stm32f0xx.h"

#define toggle (TIM14 -> SR & TIM_SR_UIF)
/*#define  DELAY1  732433       // define constant ‘DELAY1’ used to create a delay of approximately 1s
#define DELAY3 366
#define  DELAY2  65535*/


void init_LED(void);
void init_TIM14(void);

void TIM14_IRQHandler(void);

void main(void) {
	init_LED();
	init_TIM14();
}

void init_TIM14 (void)  {
	RCC -> APB1ENR |= RCC_APB1ENR_TIM14EN;          // enable the clock
	TIM14 -> PSC = 732;                            //  If CLK = 48MHz, then Tov = 1s
	TIM14 -> ARR = 65484;                          //  If CLK = 48MHz, then Tov = 1s
	TIM14->DIER |= TIM_DIER_UIE;                   //enable interrupt event TIM14
	NVIC_EnableIRQ(TIM14_IRQn);                   //unmask the TIM14 in NVIC
	TIM14 -> CR1 |= TIM_CR1_CEN;                 //  start counter for Timer 14
}
void init_LED (void)  {
	RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;         // enable the clock for GPIOC
	//GPIOC -> MODER |= GPIO_MODER_MODER8_0;;   //configure PC9 output mode
	GPIOC -> MODER |= GPIO_MODER_MODER9_0;;    //configure PC9 output mode
	GPIOC-> ODR &= ~(GPIO_ODR_9) ; 
}
void TIM14_IRQHandler(void)
{
     GPIOC -> ODR = ~(GPIOC->ODR);           // toggle PC9
     TIM14 -> SR &= ~TIM_SR_UIF;                // clears the status bit to allow a next event to be captured

}
