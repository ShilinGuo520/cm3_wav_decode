#include "types.h"


extern int sprintf(char *buf, const char *fmt, ...);
extern int printf(const char *fmt, ...);

extern int strnlen(const char *s, int count);
extern int strlen(const char *s);

extern int strncmp (const char *str1,const char *str2, int n);
extern int strcmp (const char *str1, const char *str2);

extern char *strncpy(char *dst, const char *src, int n);
extern char *strcpy(char *dst, const char *src);

extern char* strcat(char* dst , const char* src);

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


