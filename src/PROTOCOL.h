#ifndef __PROTOCOL_H
#define __PROTOCOL_H	 

#define location xdata
typedef struct{
	u8 Pro2;
	u8 Pro1;
	u8 PortH;
	u8 PortL;
	u8 SeAdd[64];
} Socket;

extern 	location u8 Hcom_sendmacid[11];
extern 	location u8 Hcom_send_req_domain[3];  //校验码已经确认
extern 	location u8 Hcom_send_req_handshak[3];//校验码已经确认
extern 	location u8 Hcom_send_req_datthre[3];//校验码已经确认
extern 	location u8 Hcom_send_datcurr[7];

#endif