
/*************	����˵��	**************

���ļ�ΪSTC15xxxϵ�еĶ�ʱ����ʼ�����жϳ���,�û�����������ļ����޸��Լ���Ҫ���жϳ���.


******************************************/



#include	"timer.h"

/********************* Timer0�жϺ���*******д��Soft_UART��,��Ϊ����********/
#if 0
void timer0_int (void) interrupt TIMER0_VECTOR
{

}
#endif

/********************* Timer1�жϺ���*******д��main��***********/
#if 0
void timer1_int (void) interrupt TIMER1_VECTOR
{

}
#endif

/********************* Timer2�жϺ���************************/
#ifdef USE_TIMER2
void timer2_int (void) interrupt TIMER2_VECTOR
{
	P10 = ~P10;
}
#endif

//========================================================================
// ����: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����: TIMx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
//========================================================================
u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer2)	return 1;	//�ղ���

    #ifdef USE_TIMER0
	if(TIM == Timer0)
	{
		TR0 = 0;		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//�����ж�
		else									ET0 = 0;	//��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//�����ȼ��ж�
		else									PT0 = 0;	//�����ȼ��ж�
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//����������Ƶ
		else										TMOD &= ~0x04;	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//���ʱ��
		else							INT_CLKO &= ~0x01;	//�����ʱ��
		
        if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)
        {
            TL0 = (u8)(65535-MAIN_Fosc/TIMx->TIM_Value);
            TH0 = (u8)((65535-MAIN_Fosc/TIMx->TIM_Value) >> 8);
        }

        if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)
        {
            TL0 = (u8)(65535-MAIN_Fosc/12/TIMx->TIM_Value);
            TH0 = (u8)((65535-MAIN_Fosc/12/TIMx->TIM_Value) >> 8);
        }

		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}
    #endif

    #ifdef USE_TIMER1
	if(TIM == Timer1)
	{
		TR1 = 0;		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//�����ж�
		else									ET1 = 0;	//��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//�����ȼ��ж�
		else									PT1 = 0;	//�����ȼ��ж�
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//����������Ƶ
		else										TMOD &= ~0x40;	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//���ʱ��
		else							INT_CLKO &= ~0x02;	//�����ʱ��
		
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)
        {
            TL1 = (u8)(65535-MAIN_Fosc/TIMx->TIM_Value);
            TH1 = (u8)((65535-MAIN_Fosc/TIMx->TIM_Value) >> 8);
        }

        if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)
        {
            TL1 = (u8)(65535-FOSC/12/TIMx->TIM_Value);
            TH1 = (u8)((65535-FOSC/12/TIMx->TIM_Value) >> 8);
        }
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}
    #endif

    #ifdef USE_TIMER2
	if(TIM == Timer2)		//Timer2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		AUXR &= ~(1<<4);	//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//�����ж�
		else										IE2  &= ~(1<<2);	//��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//����������Ƶ
		else										AUXR &= ~(1<<3);	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//���ʱ��
		else							INT_CLKO &= ~0x04;	//�����ʱ��

		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)
        {
            TL2 = (u8)(65535-FOSC/TIMx->TIM_Value);
            TH2 = (u8)((65535-FOSC/TIMx->TIM_Value) >> 8);
        }

        if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)
        {
            TL2 = (u8)(65535-FOSC/12/TIMx->TIM_Value);
            TH2 = (u8)((65535-FOSC/12/TIMx->TIM_Value) >> 8);
        }
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//��ʼ����
		return	0;		//�ɹ�
	}
    #endif
	return 2;	//����
}
