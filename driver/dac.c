#include "dac.h"
#include "gpio.h"
#include "rcc.h"

void dac1_set_data(u16 data)
{
	DAC->DHR12R1=data;
	DAC->SWTRIGR|=0x01;
}

void dac2_set_data(u16 data)
{
	DAC->DHR12R2=data;
	DAC->SWTRIGR|=0x02;
}


void dac_ch1_init(void)
{
 	unsigned int tmpreg1=0,tmpreg2=0;

 	RCC->APB2ENR |= 1<<2;
	RCC->APB1ENR |= RCC_APB1Periph_DAC;
 	GPIOA->CRL &= 0XFF00FFFF; 
	GPIOA->CRL |= 0X00440000;

	tmpreg1 = DAC->CR; 
	tmpreg1 &= ~(CR_CLEAR_Mask<<DAC_Channel_1); 
	tmpreg2 = (DAC_Trigger_Software|DAC_WaveGeneration_None|DAC_LFSRUnmask_Bits8_0|DAC_OutputBuffer_Enable); 
	tmpreg1 |= tmpreg2<<DAC_Channel_1;
	DAC->CR = tmpreg1;
	DAC->CR |= CR_EN_Set<<DAC_Channel_1;
	dac1_set_data(0x000);

	tmpreg1 = DAC->CR;
	tmpreg1 &= ~(CR_CLEAR_Mask<<DAC_Channel_2);
	tmpreg2 = (DAC_Trigger_Software|DAC_WaveGeneration_None|DAC_LFSRUnmask_Bits8_0|DAC_OutputBuffer_Enable); 
	tmpreg1 |= tmpreg2<<DAC_Channel_2;
	DAC->CR = tmpreg1;
	DAC->CR |= CR_EN_Set<<DAC_Channel_2;
	dac2_set_data(0x000);
}

