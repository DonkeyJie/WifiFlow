#ifndef		__COMMAND_H
#define		__COMMAND_H
#include	"config.h"

#define CMD_TYPE idata

typedef struct{
	u8 command[2];
	u8 length[2];
	u8 result[2];
	u8 checksum[2];
} Comm;

//extern CMD_TYPE Comm getver;
//extern CMD_TYPE Comm getconfig; 
//extern CMD_TYPE Comm setconfig;

//extern CMD_TYPE Comm getdns;
//extern CMD_TYPE Comm setdns;

//extern CMD_TYPE Comm getextrassid;
//extern CMD_TYPE Comm setextrassid;

//extern CMD_TYPE Comm getextrasocket;
//extern CMD_TYPE Comm setextrasocket;

//extern CMD_TYPE Comm getkeepalive;
//extern CMD_TYPE Comm setkeepalive;

//extern CMD_TYPE Comm getpsmode;
//extern CMD_TYPE Comm setpsmode;

//extern CMD_TYPE Comm getdualup;
//extern CMD_TYPE Comm setdualup;

//extern CMD_TYPE Comm getuartmode;
//extern CMD_TYPE Comm setuartmode;

//extern CMD_TYPE Comm getname;
//extern CMD_TYPE Comm setname;

//extern CMD_TYPE Comm getmacaddr;

////Dynamic Command
//extern CMD_TYPE Comm reset;

extern CMD_TYPE  Comm  start;

//extern CMD_TYPE Comm getstatus;

//extern CMD_TYPE Comm getip;

extern CMD_TYPE  Comm opensocket;

extern CMD_TYPE Comm closesocket;

//extern CMD_TYPE Comm wifistop;

//extern CMD_TYPE Comm wificonnect;

//extern CMD_TYPE Comm scanap;
extern CMD_TYPE Comm senddata;


#endif