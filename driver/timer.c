/*****************************************
file name:timer.c
date:2017-04-19
*****************************************/
#include "glib.h"
#include "rcc.h"
#include "timer.h"
#include "dac.h"
#include "nvic.h"

extern u8 DACdone;
extern u8 CHanalnum;
extern u8 Bitnum;
extern u8 wav_buf[1024];
extern u16 DApc;
extern u8 volume;

void TIM3_IRQHandler(void)
{ 		    		  			    
	u16 temp;
	
	if (TIM3->SR & 0X0001) {
		if(CHanalnum == 1) {
			if (Bitnum == 8) {
				DAC->DHR12R1 = wav_buf[DApc]*10/volume;
				DAC->DHR12R2 = wav_buf[DApc]*10/volume;
				DAC->SWTRIGR |= 0x03;
				DApc++;
			} else if (Bitnum == 16) {
				temp = (((u8)(wav_buf[DApc+1]-0x80)<<4) | (wav_buf[DApc] >> 4))*10/volume;
				DAC->DHR12L1 = temp;
				DAC->DHR12L2 = temp;
				DAC->SWTRIGR |= 0x03;
				DApc += 2;				
			}
		}
		else if (CHanalnum == 2) {
			if (Bitnum == 8) {
				DAC->DHR12R1 = wav_buf[DApc]*10/volume;
				DApc++;
				DAC->DHR12R2 = wav_buf[DApc]*10/volume;
				DApc++;
				DAC->SWTRIGR |= 0x03;
			} else if (Bitnum == 16) {
				DAC->DHR12L1 = (((u8)(wav_buf[DApc+1]-0x80)<<4)|(wav_buf[DApc]>>4))*10/volume;
				DApc += 2;
				DAC->DHR12L2 = (((u8)(wav_buf[DApc+1]-0x80)<<4)|(wav_buf[DApc]>>4))*10/volume;
				DApc += 2;
				DAC->SWTRIGR |= 0x03;			
			}
		}
		
		if(DApc==512) {
			DACdone=1;
		}

		if(DApc==1024) {
			DApc=0;
			DACdone=1;
		}
	}				   
	TIM3->SR &= ~(1<<0);
}

void timerx_init(u16 arr,u16 psc)
{
    u32 rwmVal;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable timer3 clock */
    RCC->APB1ENR |= 1 << 1;
    /* Set arr */
    TIM3->ARR = arr;
    TIM3->PSC = psc;

    TIM3->DIER |= 1 << 0;
    TIM3->CR1 |= 0x01;

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = TRUE;
    nvicInit(&NVIC_InitStructure);
}

