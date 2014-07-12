#ifndef		__COMMAND_H
#define		__COMMAND_H
#include	"config.h"

#define CMD_TYPE idata

#define ComanndLenth8  (8)
#define ComanndLenth7  (7)
#define ComanndLenth10 (10)
#define ComanndLenth20 (20)


extern u8 CMD_TYPE getver[10];
extern u8  CMD_TYPE getconfig[10]; 
extern u8  CMD_TYPE setconfig[8];

extern u8  CMD_TYPE getdns[10];
extern u8  CMD_TYPE setdns[8];

extern u8  CMD_TYPE getextrassid[10];
extern u8  CMD_TYPE setextrassid[8];

extern u8  CMD_TYPE getextrasocket[10];
extern u8  CMD_TYPE setextrasocket[8];

extern u8  CMD_TYPE getkeepalive[10];
extern u8  CMD_TYPE setkeepalive[8];

extern u8  CMD_TYPE getpsmode[10];
extern u8  CMD_TYPE setpsmode[20];

extern u8  CMD_TYPE getdualup[10];
extern u8  CMD_TYPE setdualup[8];

extern u8  CMD_TYPE getuartmode[10];
extern u8  CMD_TYPE setuartmode[8];

extern u8  CMD_TYPE getname[10];
extern u8  CMD_TYPE setname[7];

extern u8  CMD_TYPE getmacaddr[10];

////Dynamic Command
//extern u8  CMD_TYPE reset[10];

//extern u8  CMD_TYPE start[10];

//extern u8  CMD_TYPE getstatus[10];

//extern u8  CMD_TYPE getip[10];

//extern u8  CMD_TYPE opensocket[8];

//extern u8  CMD_TYPE closesocket[10];

//extern u8  CMD_TYPE wifistop[10];

//extern u8  CMD_TYPE wificonnect[10];

//extern u8  CMD_TYPE scanap[10];


#endif