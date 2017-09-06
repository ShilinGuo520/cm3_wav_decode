#include "types.h"
#include "common.h"

#define CR_CLEAR_Mask              			((unsigned int)0x00000FFE)
#define CR_EN_Set                  			((unsigned int)0x00000001)

#define DAC_Trigger_Software               	((u32)0x0000003C)
#define DAC_WaveGeneration_None            	((u32)0x00000000)
#define DAC_LFSRUnmask_Bits8_0             	((u32)0x00000800)
#define DAC_OutputBuffer_Enable            	((u32)0x00000000)

#define DAC_Channel_1                      	((u32)0x00000000)
#define DAC_Channel_2                      	((u32)0x00000010)

#define RCC_APB1Periph_DAC    				((u32)0x20000000)

typedef struct
{
volatile u32 CR;
volatile u32 SWTRIGR;
volatile u32 DHR12R1;
volatile u32 DHR12L1;
volatile u32 DHR8R1;
volatile u32 DHR12R2;
volatile u32 DHR12L2;
volatile u32 DHR8R2;
volatile u32 DHR12RD;
volatile u32 DHR12LD;
volatile u32 DHR8RD;
volatile u32 DOR1;
volatile u32 DOR2;
} DAC_TypeDef;

#define DAC_BASE              (APB1PERIPH_BASE + 0x7400)
#define DAC                 ((DAC_TypeDef *) DAC_BASE)

void dac_ch1_init(void);
void dac1_set_data(u16 data);
void dac2_set_data(u16 data);




