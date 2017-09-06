#include "wav_play.h"
#include "timer.h"
#include "glib.h"
#include "ff.h"
#include "leds.h"

WAV_file wav1;
u8 wav_buf[1024];
u16 DApc;
u8 CHanalnum;
u8 Bitnum;
u8 DACdone;
u8 volume;

FIL *CurFile;

u8 char_upper(u8 c)
{
	if(c<'A')return c;
	if(c>='a')return c-0x20;
	else return c;
}

u8 exf_getfree(u8 *drv,u32 *total,u32 *free)
{
	FATFS *fs1;
	u8 res;
    u32 fre_clust=0, fre_sect=0, tot_sect=0;

    res =(u32)f_getfree((const TCHAR*)drv, (DWORD*)&fre_clust, &fs1);
    if (res == 0) {											   
	    tot_sect=(fs1->n_fatent-2)*fs1->csize;	
	    fre_sect=fre_clust*fs1->csize;			
#if _MAX_SS!=512				  	
		tot_sect*=fs1->ssize/512;
		fre_sect*=fs1->ssize/512;
#endif	  
		*total=tot_sect>>1;
		*free=fre_sect>>1;
 	}
	return res;
}


u8 Check_Ifo(u8* pbuf1,u8* pbuf2)
{
	u8 i;
	for(i=0;i<4;i++)if(pbuf1[i]!=pbuf2[i])return 1;
	return 0;
}

u32 Get_num(u8* pbuf,u8 len)
{
    u32 num;
	if(len==2)num=(pbuf[1]<<8)|pbuf[0];
	else if(len==4)num=(pbuf[3]<<24)|(pbuf[2]<<16)|(pbuf[1]<<8)|pbuf[0];
	return num;
}

u8 WAV_Init(u8* pbuf)
{
	if(Check_Ifo(pbuf, "RIFF"))
		return 1;
	
	wav1.wavlen = Get_num(pbuf+4, 4);
	
	if (Check_Ifo(pbuf+8, "WAVE"))
		return 2;
	if (Check_Ifo(pbuf+12, "fmt "))
		return 3;
	wav1.formart = Get_num(pbuf+20, 2);
	wav1.CHnum = Get_num(pbuf+22, 2);
	CHanalnum = wav1.CHnum;
	wav1.SampleRate = Get_num(pbuf+24, 4);
	wav1.speed = Get_num(pbuf+28, 4);
	wav1.ajust = Get_num(pbuf+32, 2);
	wav1.SampleBits = Get_num(pbuf+34, 2);
	Bitnum = wav1.SampleBits;

	if (Check_Ifo(pbuf+36, "data"))
		return 4;
	wav1.DATAlen = Get_num(pbuf+40,4);

	if(wav1.wavlen < 0x100000) {
		printf("wav length: %d Kb\r\n", ((wav1.wavlen)>>10));
	} else {
		printf("wav length: %d Mb\r\n", ((wav1.wavlen)>>20));
	}
	
	if(wav1.formart == 1)
		printf("WAV PCM\r\n");
	if(wav1.CHnum == 1)
		printf("single\r\n");
	else 
		printf("stereo\r\n");
	
	printf("%d KHz\r\n",(wav1.SampleRate)/1000);
	printf("%d bps\r\n",(wav1.speed)/1000);
	printf("%d \r\n", wav1.SampleBits);

	return 0;
}

u8 Playwav(FIL *wav_file)
{
	u8 res;
	u16 i,times;
	
	volume = 4;
	f_lseek(wav_file, 0);
	f_read(wav_file, wav_buf, 512, (UINT*)&br);
	f_read(wav_file, wav_buf+512, 512, (UINT*)&br);
	
	res = WAV_Init(wav_buf);
	if (res != 0) {
		printf("format illegal res:%d!\r\n", WAV_Init(wav_buf));
		return 1;
	} else {
		printf("decode.......\r\n");
	}

	DACdone=0;
	DApc=44;

	timerx_init(1000000/wav1.SampleRate,72);//1MHz

	times = (wav1.DATAlen>>10)-1;
	printf("times:%d\r\n",times);
	for(i=0; i<times; i++) {
		while(!DACdone)
			printf("DACdone:%d\r\n", DACdone);
		
		DACdone=0;
		
		f_read(wav_file,wav_buf, 512, (UINT*)&br);

		while(!DACdone)
			printf("DACdone:%d\r\n", DACdone);
		
		DACdone=0;
		
		f_read(wav_file,wav_buf+512, 512, (UINT*)&br);
		LED0=!LED0;
	}
	return 0;
}



u8 wav_play_song(u8 *pname)
{
 	FIL wav_file;
	u8 res;	  

	res=f_open(&wav_file,(const TCHAR*)pname,FA_READ); 
	if (res == 0) { 
		printf("********** open suscce *********** \r\n");
		//read_header_info(fmp3);
		Playwav(&wav_file);
		f_close(&wav_file);
		printf("**************close**************** \r\n\r\n\r\n\r\n\r\n\r\n");
	}
	
	return res;  	  	  	 		  	    
}


