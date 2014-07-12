#include "rey_config.h"

void SendCommand(u8 *puts, u8 length);
//global value
unsigned int systick=0;
void main(void)
{
//	int i;
	rey_usart_config();
  rey_timer_config();
	SOFT_UART_INIT();
	
	Initialize_LCD();
	ClearLine(1);
	ClearLine(2);
	
	EA = 1;
	PutString(1,1,"--INFO1:123456--");
	PutString(2,1,"--INFO2:654321--");
	
	SendCommand(getver,ComanndLenth10);
	SendCommand(getname,ComanndLenth10);
	SendCommand(getuartmode,ComanndLenth10);
	SendCommand(getdualup,ComanndLenth10);	
	SendCommand(getmacaddr,ComanndLenth10);	
    while(1)
    {
			if (REND)				//如果接收完,把接收到的值存入接收buff
		{
			REND = 0;
			buf[r++ & 0x0f] = RBUF;
		}

		if(!TING)		//发送空闲
		{
			if (t != r)	//有要发送的数据
			{
				TBUF = buf[t++ & 0x0f];
				TING = 1;
			}
		}
	}

				
}
void SendCommand(u8 *puts,u8 length)
{
			unsigned int i;
	    for (i=0; i< length;	i++)  
				{
					TX1_write2buff(*puts); 	//遇到停止符0结束
					puts++;
				}
			while(COM1.TX_Cnt != 0){;}
}


/********************* Timer0中断函数************************/
//#ifdef USE_TIMER0
//void timer0_int (void) interrupt TIMER0_VECTOR
//{
//    systick++;
//}
//#endif

/********************* Timer1中断函数************************/
#ifdef USE_TIMER1
void timer1_int (void) interrupt TIMER1_VECTOR
{

}
#endif
