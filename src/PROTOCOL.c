#include "PROTOCOL.h"


//	xdata u8 Hcom_sendmacid[11]={0x00,0x08,MacAdd[0],MacAdd[1],MacAdd[2],MacAdd[3],MacAdd[4],MacAdd[5],DevID[0],DevID[1],0xFF};
	location u8 Hcom_sendmacid[11]={0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF};
	location u8 Hcom_send_req_domain[3]={0x01,0x03,0x04};  //У�����Ѿ�ȷ��
	location u8 Hcom_send_req_handshak[3]={0x03,0x03,0x06};//У�����Ѿ�ȷ��
	location u8 Hcom_send_req_datthre[3]={0x05,0x03,0x08};//У�����Ѿ�ȷ��
	location u8 Hcom_send_datcurr[7]={0x08,0x07,0x00,0x00,0x00,0x00,0x00};
	


