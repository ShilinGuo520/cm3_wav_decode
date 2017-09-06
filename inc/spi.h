#ifndef __SPI_H
#define __SPI_H
	
#include "types.h"

#define SPI_SPEED_2   		0
#define SPI_SPEED_4   		1
#define SPI_SPEED_8   		2
#define SPI_SPEED_16  		3
#define SPI_SPEED_32 		4
#define SPI_SPEED_64 		5
#define SPI_SPEED_128 		6
#define SPI_SPEED_256 		7

typedef unsigned short     int uint16_t;


typedef struct
{
volatile uint16_t CR1;
uint16_t  RESERVED0;
volatile uint16_t CR2;
uint16_t  RESERVED1;
volatile uint16_t SR;
uint16_t  RESERVED2;
volatile uint16_t DR;
uint16_t  RESERVED3;
volatile uint16_t CRCPR;
uint16_t  RESERVED4;
volatile uint16_t RXCRCR;
uint16_t  RESERVED5;
volatile uint16_t TXCRCR;
uint16_t  RESERVED6;
volatile uint16_t I2SCFGR;
uint16_t  RESERVED7;
volatile uint16_t I2SPR;
uint16_t  RESERVED8;  
} SPI_TypeDef;


#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00)


#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define SPI3                ((SPI_TypeDef *) SPI3_BASE)	

					  	    													  
void SPI2_Init(void);			 
void SPI2_SetSpeed(u8 SpeedSet); 
u8 SPI2_ReadWriteByte(u8 TxData);
		 
#endif

