#include "common.h"
#include "types.h"
#include "leds.h"
#include "uart.h"
#include "clk.h"
#include "glib.h"
#include "flash.h"
#include "timer.h"
#include "ff.h"
#include "mmc_sd.h"
#include "dac.h"
#include "nvic.h"
#include "wav_play.h"


void __MSR_MSP(u32 TopOfMainStack);

void info(void)
{
	printf("\n\rBuild Info:\n\rDate:%s\n\rTime:%s", __DATE__, __TIME__);
	printf("\n\rApp Start Add:%x", APP_START_ADD);
	printf("\n\rFlash Size:%d", FLASH_SIZE);
	printf("\n\rRam Size:%d\n\r", RAM_SIZE);
}	

FATFS fs[2];

int main()
{
	u32 total,free;
	u8 t=0;		   	   
	u8 res;
	DIR mp3dir;	 		//
	FILINFO mp3fileinfo;//
	u8 *fn;   			//
	u8 pname[50];

	nvic_vtor_remapping(APP_START_ADD - 0x08000000);
	sys_clk_init(9);
	uart_init(72, 115200); 	// 115200
	led_init();
    dac_ch1_init();
	info();

    printf("wav test\r\n");
	while(SD_Initialize()) {
		printf("SD Card Error!\r\n");
		LED0=!LED0;
	}

	f_mount(0, &fs[0]);

	while(exf_getfree("0",&total,&free)) {
		printf("Fatfs Error!\r\n");	  
		LED0=!LED0;
	}												 

	printf("FATFS OK!\r\n");	
	printf("SD Total Size: %d MB\r\n", (total>>10));	 
	printf("SD  Free Size: %d MB\r\n", (free>>10)); 	

	wav_play_song("0:/MUSIC/rongyao.wav");

	res = f_opendir(&mp3dir,"0:/MUSIC"); 

	while(1) {
        LED1=!LED1;
	}

	return 0;
}



