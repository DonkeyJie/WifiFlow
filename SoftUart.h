#ifndef __SOFTUART_H
#define __SOFTUART_H	 

#include "config.h"

#define D_RxBitLenth	9		//9: 8 + 1 stop
#define D_TxBitLenth	9		//9: 1 stop bit


sbit RXB = P3^0;                //define UART TX/RX port
sbit TXB = P3^1;


extern u8  xdata TBUF,RBUF;
extern u8  xdata TDAT,RDAT;
extern u8  xdata TCNT,RCNT;	//发送和接收检测 计数器(3倍速率检测)
extern u8  xdata TBIT,RBIT;	//发送和接收的数据计数器
extern u8  xdata t, r;
extern u8  xdata buf[16];



extern bit  TING,RING;	//正在发送或接收一个字节
extern bit  REND;	 	//接收完的标志位

#define	RxBitLenth	9	//8个数据位+1个停止位
#define	TxBitLenth	9	//8个数据位+1个停止位




//-----------------------------------------
//UART模块的初始变量	initial UART module variable
void SOFT_UART_INIT(void);


#endif