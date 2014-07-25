#ifndef __SOFTUART_H
#define __SOFTUART_H	 

#include "config.h"

#define D_RxBitLenth	9		//9: 8 + 1 stop
#define D_TxBitLenth	9		//9: 1 stop bit


sbit RXB = P3^0;                //define UART TX/RX port
sbit TXB = P3^1;


extern u8  xdata TBUF,RBUF;
extern u8  xdata TDAT,RDAT;
extern u8  xdata TCNT,RCNT;	//���ͺͽ��ռ�� ������(3�����ʼ��)
extern u8  xdata TBIT,RBIT;	//���ͺͽ��յ����ݼ�����
extern u8  xdata t, r;
extern u8  xdata buf[16];



extern bit  TING,RING;	//���ڷ��ͻ����һ���ֽ�
extern bit  REND;	 	//������ı�־λ

#define	RxBitLenth	9	//8������λ+1��ֹͣλ
#define	TxBitLenth	9	//8������λ+1��ֹͣλ




//-----------------------------------------
//UARTģ��ĳ�ʼ����	initial UART module variable
void SOFT_UART_INIT(void);


#endif