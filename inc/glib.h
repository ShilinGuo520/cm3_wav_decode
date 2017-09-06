#include "types.h"


extern void memcpy(unsigned char *dec, unsigned char *src, int size);
extern void memset(unsigned char *src, unsigned char val, int size);

extern int sprintf(char *buf, const char *fmt, ...);
extern int printf(const char *fmt, ...);

extern int strnlen(const char *s, int count);
extern int strlen(const char *s);

extern int strncmp (const char *str1,const char *str2, int n);
extern int strcmp (const char *str1, const char *str2);

extern void * malloc(int size);
extern int free(void *mem);


/*
 * Set basepri to portMAX_SYSCALL_INTERRUPT_PRIORITY without effecting other
 * registers.  r0 is clobbered.
 */ 
#define portSET_INTERRUPT_MASK()						\
	__asm volatile								\
	(									\
		"cpsid	i					\n"	\
	)
	
/*
 * Set basepri back to 0 without effective other registers.
 * r0 is clobbered.
 */
#define portCLEAR_INTERRUPT_MASK()						\
	__asm volatile								\
	(									\
		"cpsie	i					\n"	\
	)

#define portDISABLE_INTERRUPTS()	portSET_INTERRUPT_MASK()
#define portENABLE_INTERRUPTS()		portCLEAR_INTERRUPT_MASK()


