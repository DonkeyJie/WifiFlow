
#ifndef		__CONFIG_H
#define		__CONFIG_H


/*********************************************************/

#define MAIN_Fosc		22118400L	//������ʱ��
//#define MAIN_Fosc		12000000L	//������ʱ��
//#define MAIN_Fosc		11059200L	//������ʱ��
//#define MAIN_Fosc		 5529600L	//������ʱ��
//#define MAIN_Fosc		24000000L	//������ʱ��


/*********************************************************/

#include	"STC15Fxxxx.H"


/**************************************************************************/

#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)
#define USART_BAUDRATE  (19200ul)

//���ڲ�����
#define BaudRate		19200		//ģ�⴮�ڲ�����
//timer0��װ��
#define Timer0_Reload		(65536 - MAIN_Fosc / BaudRate / 3)
/***********************************************************/


#define USE_USART1

#define USE_TIMER0
#define TIMER0_FREQ     (1000)

#endif
