#include "spi.h"
#include "rcc.h"
#include "gpio.h"

void SPI2_Init(void)
{	 
	RCC->APB2ENR |= 1 << 3; 
	RCC->APB1ENR |= 1 << 14;   	
	GPIOB->CRH &= 0X000FFFFF; 
	GPIOB->CRH |= 0XBBB00000;	
	GPIOB->ODR |= 0X7 << 13;   	
	SPI2->CR1 |= 0 << 10;		
	SPI2->CR1 |= 1 << 9; 		
	SPI2->CR1 |= 1 << 8;  

	SPI2->CR1 |= 1 << 2; 		
	SPI2->CR1 |= 0<< 11;		
	SPI2->CR1 |= 1 << 1; 		
	SPI2->CR1 |= 1 << 0; 		

	SPI2->CR1 |= 3 << 3; 		
	SPI2->CR1 |= 0 << 7; 		
	SPI2->CR1 |= 1 << 6; 		
	SPI2_ReadWriteByte(0xff);
}

void SPI2_SetSpeed(u8 SpeedSet)
{
	SpeedSet &= 0X07;	
	SPI2->CR1 &= 0XFFC7; 

	SPI2->CR1 |= SpeedSet << 3;	
	SPI2->CR1 |= 1 << 6; 
}

u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u16 retry = 0;				 

	while ((SPI2->SR & 1 << 1) == 0) {
		retry++;
		if(retry>=0XFFFE)return 0; 
	}			  

	SPI2->DR=TxData;
	retry=0;

	while ((SPI2->SR&1<<0) == 0) {
		retry++;
		if(retry>=0XFFFE)return 0;
	}	  						    

	return SPI2->DR;

}
