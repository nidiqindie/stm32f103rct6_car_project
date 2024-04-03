#ifndef __BEEP_H
#define	__BEEP_H


#include "stm32f10x.h"

//重定义PA15->BEEP
#define BEEP_GPIO_PORT    	GPIOC			              
#define BEEP_GPIO_CLK 	    RCC_APB2Periph_GPIOC		
#define BEEP_GPIO_PIN		GPIO_Pin_13			      


#define ON  1
#define OFF 0


#define BEEP(a)	if (a)	\
					GPIO_SetBits(BEEP_GPIO_PORT,BEEP_GPIO_PIN);\
					else		\
					GPIO_ResetBits(BEEP_GPIO_PORT,BEEP_GPIO_PIN)

void BEEP_GPIO_Config(void);
					
#endif /* __BEEP_H */
