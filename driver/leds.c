/*********************************
 * leds driver
 *********************************/

#include "leds.h"
#include "config.h"

void led_init(void)
{
	RCC->APB2ENR|=1<<3;    
	RCC->APB2ENR|=1<<6;
		 
	GPIOB->CRL&=0XFF0FFFFF; 
	GPIOB->CRL|=0X00300000;//PB.5  
	GPIOB->ODR|=1<<5;	   //PB.5
											  
	GPIOE->CRL&=0XFF0FFFFF;
	GPIOE->CRL|=0X00300000;//PE.5
	GPIOE->ODR|=1<<5;	   //PE.5
}
