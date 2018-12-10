#include<iostream>
#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include"ClientOperation.h"
using namespace std;

// class ClientInfo
// {
// public:
	// char clinetID[12];			// 客户端ID
	// char serverID[12];			// 服务器ID
	// //char authCode[65];			// 消息认证码
	// char serverIP[32];			// 服务器IP
	// unsigned short serverPort;	// 服务器端口
	// int maxNode;				// 共享内存节点个数
	// int shmKey;					// 共享内存的Key
// };


int userInit()
{
	printf("\n  /*************************************************************/");
	printf("\n  /*************************************************************/");
	printf("\n  /*     1.密钥协商                                            */");
	printf("\n  /*     2.密钥校验                                          */");
	printf("\n  /*     3.密钥注销                                            */");
	printf("\n  /*     4.密钥查看                                           */");
	printf("\n  /*     0.退出系统                                        */");
	printf("\n  /*************************************************************/");
	printf("\n  /*************************************************************/");
	printf("\n\n  选择:");
	int num = -1;
	cin >> num;
	return num;
}


int main()
{
	ClientInfo info;
	memset(&info, 0x00, sizeof(info));
	strcpy(info.clinetID, "001");
	strcpy(info.serverID, "bbq");
	strcpy(info.serverIP, "106.12.201.149");
	info.serverPort = 9999;
	info.maxNode = 1;
	info.shmKey = 0x1234;

	//
	ClientOperation client(&info);

	while (1)
	{
		int num = userInit();
		switch (num)
		{
		case 0:
			break;
		case 1:
			client.secKeyAgree();
			break;
		case 2:
			client.secKeyCheck();
			break;
		case 3:
			client.secKeyRevoke();
			break;
		case 4:
			client.secKeyView();
			break;
		default:
			break;
		}

	}
	cout << "客户端已关闭------------------"<< endl;
	return 0;
}
