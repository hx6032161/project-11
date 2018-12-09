#include<iostream>
#include"ClientOperation.h"
using namespace std;

//class ClientInfo
//{
//public:
//	char clinetID[12];			// 客户端ID
//	char serverID[12];			// 服务器ID
//	//char authCode[65];			// 消息认证码
//	char serverIP[32];			// 服务器IP
//	unsigned short serverPort;	// 服务器端口
//	int maxNode;				// 共享内存节点个数
//	int shmKey;					// 共享内存的Key
//};


int userInit()
{
	cout << "#########################" << endl;
	cout << "#########################" << endl;
	cout << "#########################" << endl;
	cout << "#	   1、秘钥协商		 #" << endl;
	cout << "#	   2、秘钥校验		 #" << endl;
	cout << "#	   3、秘钥更新		 #" << endl;
	cout << "#	   4、秘钥查询		 #" << endl;
	cout << "#########################" << endl;
	cout << "#########################" << endl;
	cout << "#########################" << endl;
	cout << "请输入：";
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

	//创建客户端类
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
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}

	}

}