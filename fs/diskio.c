#include "mmc_sd.h"
#include "diskio.h"
#include "gpio.h"
#include "glib.h"
#include "mem.h"


#define SD_CARD	 0  //SD卡,卷标为0



DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{	
	u8 res=0;	    
	switch(drv)
	{
		case SD_CARD://SD卡
			res = SD_Initialize();//SD_Initialize() 
		 	if(res)//STM32 SPI的bug,在sd卡操作失败的时候如果不执行下面的语句,可能导致SPI读写异常
			{
				SD_SPI_SpeedLow();
				SD_SPI_ReadWriteByte(0xff);//提供额外的8个时钟
				SD_SPI_SpeedHigh();
			}
  			break;
		default:
			res=1; 
	}		 
	if(res)return  STA_NOINIT;
	else return 0; //初始化成功
}   
//获得磁盘状态
DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{		   
    return 0;
}
 //读扇区
 //drv:磁盘编号0~9
 //*buff:数据接收缓冲首地址
 //sector:扇区地址
 //count:需要读取的扇区数
DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	u8 res=0; 
    if (!count)return RES_PARERR;//count不能等于0，否则返回参数错误		 	 
	switch(drv)
	{
		case SD_CARD://SD卡
			res=SD_ReadDisk(buff,sector,count);	 
		 	if(res)//STM32 SPI的bug,在sd卡操作失败的时候如果不执行下面的语句,可能导致SPI读写异常
			{
				SD_SPI_SpeedLow();
				SD_SPI_ReadWriteByte(0xff);//提供额外的8个时钟
				SD_SPI_SpeedHigh();
			}
			break;
		default:
			res=1; 
	}
   //处理返回值，将SPI_SD_driver.c的返回值转成ff.c的返回值
    if(res==0x00)return RES_OK;	 
    else return RES_ERROR;	   
}  
#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	        /* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	u8 res=0;  
    if (!count)return RES_PARERR;//count不能等于0，否则返回参数错误		 	 
	switch(drv)
	{
		case SD_CARD://SD卡
			res=SD_WriteDisk((u8*)buff,sector,count);
			break;
		default:
			res=1; 
	}
    if(res == 0x00)return RES_OK;	 
    else return RES_ERROR;		 
}
#endif /* _READONLY */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{	
	DRESULT res;						  			     
	if(drv==SD_CARD)
	{
	    switch(ctrl)
	    {
		    case CTRL_SYNC:
				SD_CS=0;
		        if(SD_WaitReady()==0)res = RES_OK; 
		        else res = RES_ERROR;	  
				SD_CS=1;
		        break;	 
		    case GET_SECTOR_SIZE:
		        *(WORD*)buff = 512;
		        res = RES_OK;
		        break;	 
		    case GET_BLOCK_SIZE:
		        *(WORD*)buff = 8;
		        res = RES_OK;
		        break;	 
		    case GET_SECTOR_COUNT:
		        *(DWORD*)buff = SD_GetSectorCount();
		        res = RES_OK;
		        break;
		    default:
		        res = RES_PARERR;
		        break;
	    }
	} else res=RES_ERROR;//其他的不支持
    return res;
}
   
DWORD get_fattime (void)
{				 
	return 0;
}
			 
void *ff_memalloc (UINT size)			
{
	return (void*)malloc(size);
}

void ff_memfree (void* mf)		 
{
	free(mf);
}












