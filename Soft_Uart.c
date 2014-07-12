#include "SoftUart.h"



u8  xdata TBUF,RBUF;
u8  xdata TDAT,RDAT;
u8  xdata TCNT,RCNT;	//���ͺͽ��ռ�� ������(3�����ʼ��)
u8  xdata TBIT,RBIT;	//���ͺͽ��յ����ݼ�����
u8  xdata t, r;
u8  xdata buf[16];

bit  TING,RING;	//���ڷ��ͻ����һ���ֽ�
bit  REND;	 	//������ı�־λ

//-----------------------------------------
//UARTģ��ĳ�ʼ����	initial UART module variable
void SOFT_UART_INIT(void)
{
		InternalRAM_enable();
//	ExternalRAM_enable();

		Timer0_1T();
		Timer0_AsTimer();
		Timer0_16bitAutoReload();
		Timer0_Load(Timer0_Reload);
		Timer0_InterruptEnable();
		Timer0_Run();
			
	
      TING = 0;
      RING = 0;
      REND = 0;
      TCNT = 0;
      RCNT = 0;
}

//-----------------------------------------
//��ʱ��0�жϳ���for UART �Բ�����3�����ٶȲ����ж� ��ʼλ		Timer interrupt routine for UART
#ifdef USE_TIMER0
void timer0_int (void) interrupt TIMER0_VECTOR
{
		if (RING)
	{
		if (--RCNT == 0)				  //���������Զ�ʱ����1/3������
		{
			RCNT = 3;                   //���ý��ռ�����  ���������Զ�ʱ����1/3������	reset send baudrate counter
			if (--RBIT == 0)			  //������һ֡����
			{
				RBUF = RDAT;            //�洢���ݵ�������	save the data to RBUF
				RING = 0;               //ֹͣ����			stop receive
				REND = 1;               //������ɱ�־����	set receive completed flag
			}
			else
			{
				RDAT >>= 1;			  //�ѽ��յĵ�b���� �ݴ浽 RDAT(���ջ���)
				if (RXB) RDAT |= 0x80;  //shift RX data to RX buffer
			}
		}
	}

	else if (!RXB)		//�ж��ǲ��ǿ�ʼλ RXB=0;
	{
		RING = 1;       //����������ÿ�ʼ���ձ�־λ 	set start receive flag
		RCNT = 4;       //��ʼ�����ղ����ʼ�����       	initial receive baudrate counter
		RBIT = RxBitLenth;       //��ʼ�����յ�����λ��(8������λ+1��ֹͣλ)    initial receive bit number (8 data bits + 1 stop bit)
	}

	if (TING)			//���Ϳ�ʼ��־λ   judge whether sending
	{
		if (--TCNT == 0)			//���������Զ�ʱ����1/3������
		{
			TCNT = 3;				//���÷��ͼ�����   reset send baudrate counter
			if (TBIT == 0)			//���ͼ�����Ϊ0 �������ֽڷ��ͻ�û��ʼ
			{
				TXB = 0;			//���Ϳ�ʼλ     					send start bit
				TDAT = TBUF;		//�ѻ�������ݷŵ����͵�buff		load data from TBUF to TDAT
				TBIT = TxBitLenth;	//��������λ�� (8����λ+1ֹͣλ)	initial send bit number (8 data bits + 1 stop bit)
			}
			else					//���ͼ�����Ϊ��0 ���ڷ�������
			{
				if (--TBIT == 0)	//���ͼ�������Ϊ0 �������ֽڷ��ͽ���
				{
					TXB = 1;		//��ֹͣλ����
					TING = 0;		//����ֹͣλ    			stop send
				}
				else
				{
					TDAT >>= 1;		//�����λ�͵� CY(�洦��־λ) shift data to CY
					TXB = CY;		//���͵�b����				write CY to TX port
				}
			}
		}
	}
	
}
#endif