#include "types.h"
#include "integer.h"


u8 wav_play_song(u8 *pname);
u8 exf_getfree(u8 *drv,u32 *total,u32 *free);

UINT br,bw;		

typedef struct 
{
	u8 chRIFF[4];
	u32 wavlen;
	u8 chWAV[4];
	u8 chFMT[4];
	u16 formart;
	u16 CHnum;
	u32 SampleRate;
	u32 speed;
	u16 ajust;
	u16 SampleBits;
	u8 chDATA[4];
	u32 DATAlen;
}WAV_file;


