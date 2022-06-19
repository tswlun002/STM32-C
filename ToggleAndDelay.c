

//********************************************************************
//*                    EEE2046F C template                           *
//*==================================================================*
//* WRITTEN BY:    TSWLUN002	                 		             *
//* DATE CREATED:                                                    *
//* MODIFIED:                                                        *
//*==================================================================*
//* PROGRAMMED IN:            *
//* DEV. BOARD:    STM32F0 Discovery Board                      *
//* TARGET:	   STMicroelectronics STM32F051                   *
//*==================================================================*
//* DESCRIPTION:                                                     *
//*                                                                  *
//********************************************************************
// INCLUDE FILES
//====================================================================
#include <stdio.h>
#include "stm32f0xx.h"

//====================================================================
// SYMBOLIC CONSTANTS
//====================================================================

#define  DELAY1  732433       // define constant ‘DELAY1’ used to create a delay of approximately 1s
#define DELAY3 366
#define  DELAY2  65535
#define  sw1 (GPIOA->IDR)
//====================================================================
// GLOBAL VARIABLES
//====================================================================

//====================================================================
// FUNCTION DECLARATIONS
//====================================================================
void initGPIO(void); // initialize the GPIO pins connected to the pushbutton and LED

void delay(void); // create an approximate 1 second delay

void blinky(void); //turn ON LED 3, LED 4 OFF and turn OFF LED 3, LED 4 ON

void run(void);
void delay1(void);
//====================================================================
// MAIN FUNCTION
//====================================================================
void main (void)
{
    initGPIO();   //INVOKE function so that it enable registers and initialize aGPIO
    run();
}

//====================================================================
// FUNCTION DEFINITIONS
void initGPIO(void){

	//ENABLE USER BUTTON
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN; // enable clock to GPIOA
	GPIOA-> MODER &= ~GPIO_MODER_MODER0;  // configure PA0 to input mode

	//Enable resistors
	GPIOA ->PUPDR |= GPIO_PUPDR_PUPDR0_0;   // pull up for PAO
	//GPIOA ->PUPDR |= GPIO_PUPDR_PUPDR0_1;  // pull down for PAO


	//ENABLE LEDS
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; //enable clock for GPIOB
	GPIOC->MODER |= GPIO_MODER_MODER8_0; //SET OUTPUT MODE PIN 8
	GPIOC->MODER |= GPIO_MODER_MODER9_0; // SET OUTPUT MODE PIN 9


}

void run(void){


	int turnedOn =0;
	while(1){
		volatile uint16_t data;
		uint32_t bitmask  = GPIO_IDR_0;
		data  = GPIOA->IDR;

		while(data){
			GPIOC ->ODR |= GPIO_ODR_8;
			data= GPIOA->IDR;
			delay();
			if((data &1) ==0)
		 		break;
		 };

		if(turnedOn ==0){
			GPIOC->ODR &= ~GPIO_ODR_8;
			GPIOC ->ODR |= GPIO_ODR_9;
			turnedOn=1;
		}
		else if (turnedOn ==1){
			GPIOC->ODR &= ~GPIO_ODR_8;
			GPIOC ->ODR &= ~GPIO_ODR_9;
			turnedOn=0;

		}
		while((sw1 &bitmask));
		delay();
	}
}

void delay1(void) {
	volatile int i, x;
	for(i=0 ;i<DELAY3; i++);
	for(x=0; x<DELAY2; x++);

}
// Delay function definition one second
void delay(void) {

	volatile int i, x;
	for(i=0 ;i<DELAY1; i++);
	for(x=0; x<DELAY2; x++);

}


//********************************************************************
// END OF PROGRAM
//********************************************************************
