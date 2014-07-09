#include "rey_config.h"


//global value
unsigned int systick=0;
void main(void)
{
	int i;
	rey_usart_config();
  rey_timer_config();
	
	Initialize_LCD();
	ClearLine(1);
	ClearLine(2);
	
	EA = 1;
	PutString(1,1,"--INFO1:123456--");
	PutString(2,1,"--INFO2:654321--");
    while(1)
    {
			
//        if(systick == 1000)
//        {
//            systick = 0;
//            P26=!P26;
//        }
			delay_ms(1);
		if(COM1.RX_TimeOut > 0)		//超时计数
		{
			if(--COM1.RX_TimeOut == 0)
			{
				if(COM1.RX_Cnt > 0)
				{
					for(i=0; i<COM1.RX_Cnt; i++)	TX1_write2buff(RX1_Buffer[i]);	//收到的数据原样返回
				}
				COM1.RX_Cnt = 0;
			}
		}
	}
				
}



/********************* Timer0中断函数************************/
#ifdef USE_TIMER0
void timer0_int (void) interrupt TIMER0_VECTOR
{
    systick++;
}
#endif

/********************* Timer1中断函数************************/
#ifdef USE_TIMER1
void timer1_int (void) interrupt TIMER1_VECTOR
{

}
#endif
