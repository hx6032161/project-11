#include<iostream>
#include"ClientOperation.h"
using namespace std;

//class ClientInfo
//{
//public:
//	char clinetID[12];			// �ͻ���ID
//	char serverID[12];			// ������ID
//	//char authCode[65];			// ��Ϣ��֤��
//	char serverIP[32];			// ������IP
//	unsigned short serverPort;	// �������˿�
//	int maxNode;				// �����ڴ�ڵ����
//	int shmKey;					// �����ڴ��Key
//};


int userInit()
{
	cout << "#########################" << endl;
	cout << "#########################" << endl;
	cout << "#########################" << endl;
	cout << "#	   1����ԿЭ��		 #" << endl;
	cout << "#	   2����ԿУ��		 #" << endl;
	cout << "#	   3����Կ����		 #" << endl;
	cout << "#	   4����Կ��ѯ		 #" << endl;
	cout << "#########################" << endl;
	cout << "#########################" << endl;
	cout << "#########################" << endl;
	cout << "�����룺";
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

	//�����ͻ�����
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