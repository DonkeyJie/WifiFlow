#include "rey_config.h"
//#define test_suart2huart
//#define test_checksum
//#define test_HighLevelProt
#define test_Hlevel


//global value
	u8  idata HandShakeT=10;
	u8  idata MacAdd[6];
	u8  idata DevID[2];
	u8  idata Domain[40];
	u8  idata Port[4];
	u8  idata DatThre[4];
	u8  idata DatCurr[4];

	idata	Socket exSo1={0x00,0x01,0x1F,0xF5,"192.168.23.1"};
	//  u8  idata Rec[10];

	xdata u8 state=0;
	
	unsigned char i=0; //接收索引



	void SendCommand(Comm puts,Socket *p);
	void SendDat(Comm puts,u8 *p,u8 length);
	u16 calc_sum(void *dat,u32 len);
//	u16 ReceiveData(u8 *p,u8 l);
//	u8 Hcalc_sum(void *dat,u32 len);

void main(void)
{

	unsigned char j=HandShakeT; //计数
	unsigned char n=0; //计数
	u8 length=0;    //数据长度
	u16 checks=0;  //校验和
	u8 che[6]={0x61,0x62,0x63,0x64,0x65,0x66};  //待发送测试数据  "abcdef"

	u16 x=0;
	rey_usart_config();
  rey_timer_config();
	SOFT_UART_INIT();
	
	Initialize_LCD();
	ClearLine(1);
	ClearLine(2);
	
	P13 = 0;   //make the mxchip wifi module into the EMSP CMD mode

	
	EA = 1;
	PutString(1,1,"--INFO1:123456--");
	PutString(2,1,"--INFO2:654321--");
	
	for(n =0;i<10;i++)         //延迟一定时间 以让wifi模块完成启动
	{
		delay_ms(3000000000);
	}
  SendDat(start,0,0);        //开启网络
	delay_ms(10000);
	
	x=calc_sum(che,4);         //计算数据部分的校验和
    while(1)
    {
// use to test soft uart send data to hard uart.  (not working!)			(内部短接硬件串口的发送和接收无效，外部跳帽短接可以收发)
#ifdef test_suart2huart
		if (REND)				         //如果接收完,把接收到的值存入接收buff
		{
			REND = 0;
			TX1_write2buff(RBUF);
		}

		if(!TING)		             //发送空闲
		{		
#ifdef test_checksum
			TBUF = (x>>8) & 0xff;  //the first byte is not i want,but i did't know where it come from. 
			                       //it has no relationship with the data we sent,but it's the same as the address of main function. and it always the same..(0x82)
      TING =1;
			delay_ms(100);         //need delay,or it may not send the next data; don't know why..
      TBUF = x &0xff ;
      TING =1;
#endif
			while(COM1.RX_Cnt != i)	//有要发送的数据
			{
				TBUF = RX1_Buffer[i++ &0x3f];
				TING = 1;

			}
			COM1.RX_Cnt = 0;
			i = 0;
		}
#endif
// use to test soft uart (sRX2sTX, already working!)
#ifdef test_suart2suart
		if(REND)
		{
			REND = 0;
			buf[r++ & 0x0f] =RBUF;
		}
		if(!TING)
		{
			if(r != t)
			{
				TBUF = buf[t++ &0x0f];
				TING = 1;
			}
		}
#endif
// use to test hard uart (hRX2hTX,  already working!)
#ifdef test_huart2huart
		if(COM1.RX_TimeOut != 0)
		{
			if(--COM1.RX_TimeOut == 0)
			{
				if(COM1.RX_Cnt != 0)
				{
					for(i=0;i<=COM1.RX_Cnt;i++) {TX1_write2buff(RX1_Buffer[i]);  delay_ms(5);}//需要加延迟，不延迟容易会出现丢包或者中间出现空格以导致字符串发送不完
				}
				COM1.RX_Cnt = 0;
			}
		}
#endif
// use to test opensocket and closesocket command(open socket and send string("abcdef"), and then, close socket)		
#ifdef test_Hlevel
		SendCommand(opensocket,&exSo1);     //establish socket
		delay_ms(255);
		SendDat(senddata,"abcdef",6);
		delay_ms(255);
		SendDat(closesocket,0,0);          //close socket
		delay_100ms(HandShakeT);           // hand shake cycle
#endif
// use to test portocol(without dealing check wrong,just send proper data and command)	
#ifdef test_HighLevelProt
		SendCommand(opensocket,&exSo1);     //建立socket链接
		delay_ms(5);
		
		length = 10 + 11;                   //修改命令长度
		senddata.length[0]=length;
		senddata.length[1]=length>>8;
		checks=calc_sum(&senddata,6);
		senddata.checksum[1]=checks;
		senddata.checksum[0]=checks>>8;
		Hcom_sendmacid[10]= Hcalc_sum(Hcom_sendmacid,10);
		SendDat(senddata,Hcom_sendmacid,11);   //发送mac和设备id
		delay_ms(5);
		
		if(state==0)
		{
			length = 10 + 3;
			senddata.length[0]=length;
			senddata.length[1]=length>>8;
			checks=calc_sum(&senddata,6);
			senddata.checksum[1]=checks;
			senddata.checksum[0]=checks>>8;
			SendDat(senddata,Hcom_send_req_domain,3);   //请求域名“http://www.baidu.com:1234”   暂且用ip来代替
			delay_ms(5);
			
			SendDat(senddata,Hcom_send_req_handshak,3);  //请求读取握手周期
			delay_ms(5);
			SendDat(senddata,Hcom_send_req_datthre,3);   //请求读取用户负荷值
			delay_ms(5);
			state=1;
			
		}
		else
		{
			length = 10 + 7;
			senddata.length[0]=length;                     //因为数据部分的长度改变，所以必须修改命令的长度字节
			senddata.length[1]=length>>8;
			checks=calc_sum(&senddata,6);                   
			senddata.checksum[1]=checks;
			senddata.checksum[0]=checks>>8;                //每次数据部分长度改变，都必须修改校验码{L层}
			Hcom_send_datcurr[6]=Hcalc_sum(Hcom_send_datcurr,6);   //计算H层校验码
			SendDat(senddata,Hcom_send_datcurr,7);
			delay_ms(5);
			
		}
		SendDat(closesocket,0,0);  //关闭socket链接
		delay_100ms(HandShakeT);  //周期性启动socket链接服务器
			

#endif

// use to test receive data
//#ifdef HleveRectest
//		SendCommand(opensocket,&exSo1);     //建立socket链接
//		delay_ms(255);
//		if(COM1.RX_Cnt != i)
//		{
//			ReceiveData(Rec,length);
//			PutString(1,1,Rec);
//		}
//		SendDat(closesocket,0,0); //关闭socket链接
//		delay_100ms(HandShakeT);  //周期性启动socket链接服务器
//#endif

		}



}

//use to send command(there just opensocket to establish socket)
void SendCommand(Comm puts,Socket *p)
{

	    u16 checks=0;
			u8 i=0;
////	    u8 *ptemp = p;
//			u16 len=0;
			TX1_write2buff(puts.command[0]);
			delay_ms(5);
			TX1_write2buff(puts.command[1]);
			delay_ms(5);
			TX1_write2buff(puts.length[0]);
			delay_ms(5);
			TX1_write2buff(puts.length[1]);
			delay_ms(5);
			TX1_write2buff(puts.result[0]);
			delay_ms(5);
			TX1_write2buff(puts.result[1]);
			delay_ms(5);
			TX1_write2buff(puts.checksum[0]);
			delay_ms(5);
			TX1_write2buff(puts.checksum[1]);
			delay_ms(5);
			checks = calc_sum(p,68);
			TX1_write2buff(p->Pro2);
			delay_ms(5);
			TX1_write2buff(p->Pro1);
			delay_ms(5);
			TX1_write2buff(p->PortH);
			delay_ms(5);
			TX1_write2buff(p->PortL);
			delay_ms(5);
			while((i)<64) 
			{
				TX1_write2buff(p->SeAdd[i++]);
				delay_ms(5);
			}
	    TX1_write2buff( ( checks >> 8 ) & 0xff );
			delay_ms(5);
			TX1_write2buff( checks & 0xff );
			while(COM1.TX_Cnt != 0){;}
}	

//use to send data(include command without data and command with upper protocol)	
void SendDat(Comm puts,u8 *p,u8 length)
{
	u8 i=0;
	u16 checks;
			TX1_write2buff(puts.command[0]);
			delay_ms(5);
			TX1_write2buff(puts.command[1]);
			delay_ms(5);
			TX1_write2buff(puts.length[0]);
			delay_ms(5);
			TX1_write2buff(puts.length[1]);
			delay_ms(5);
			TX1_write2buff(puts.result[0]);
			delay_ms(5);
			TX1_write2buff(puts.result[1]);
			delay_ms(5);
			TX1_write2buff(puts.checksum[0]);
			delay_ms(5);
			TX1_write2buff(puts.checksum[1]);
			delay_ms(5);
	checks = calc_sum(p,length);
	while((i)<length)
	{
		TX1_write2buff(*(p++));
		i++;
	}
     	TX1_write2buff( ( checks >> 8 ) & 0xff );
			delay_ms(5);
			TX1_write2buff( checks & 0xff );
	while(COM1.TX_Cnt != 0){;}
}
// use to calculate check sum(16bit )
u16 calc_sum(void *dat,u32 len)
{
	u32 cksum=0;
  u16 *p =dat;
	while(len >1)
	{
		cksum += *p++;
		len-=2;
	}
	if(len)
	{
		cksum+=*(u8 *)p;
	}
	cksum = (cksum >>16) +(cksum &0xffff);
	cksum += (cksum >>16);
	return ~cksum;
}


// use to calculate check sum (8bit)
//u8 Hcalc_sum(void *dat,u32 len)
//{
//	u8 cksum=0;
//  u8 *p =dat;
//	while(len >0)
//	{
//		cksum += *p++;
//		len--;
//	}
//	return cksum;
//}


//u16 ReceiveData(u8 *p,u8 l)
//{
//		Comm puts;
//		u16 len=0;
//	  u8 *ptemp = p;
//		u16 checkreturn;
//			puts.command[0] = RX1_Buffer[i++];
//			puts.command[1] = RX1_Buffer[i++];
//			puts.length[0] = RX1_Buffer[i++];
//			puts.length[1] = RX1_Buffer[i++];
//			puts.result[0] = RX1_Buffer[i++];
//			puts.result[1] = RX1_Buffer[i++];
//			puts.checksum[0] = RX1_Buffer[i++];
//			puts.checksum[1] = RX1_Buffer[i++];

//		if(puts.command[0]==0x07)                    //只对接收数据命令进行处理，其他的命令不进行处理
//		{
//			len =puts.length[1] << 8 + puts.length[0];
//			while(len - 2 > i && i > 7)    //边界还需仔细处理一下
//			{
//				*(ptemp++) = RX1_Buffer[i++];
//			}
//			checkreturn = (RX1_Buffer[i++]<<8)+RX1_Buffer[i];
//		}
//		l=len-10;
//		COM1.RX_Cnt = 0;
//		i = 0;
//		return  checkreturn;
//}

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
