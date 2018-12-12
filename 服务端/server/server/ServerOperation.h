#pragma once
#include"SecKeyShm.h"
#include "TcpServer.h"
#include <map>
class ServerInfo
{
public:
	char			serverID[12];	// �������˱��
	char			dbUse[24]; 		// ���ݿ��û���
	char			dbPasswd[24]; 	// ���ݿ�����
	char			dbSID[24]; 		// ���ݿ�sid

	unsigned short 	sPort;			// �������󶨵Ķ˿�
	int				maxnode;		// �����ڴ���������� �ͻ���Ĭ��1��
	int 			shmkey;			// �����ڴ�keyid ���������ڴ�ʱʹ��	 
};

class ServerOperation
{
public:
	ServerOperation(const ServerInfo * info);
	~ServerOperation();
	//��������ʼ����
	void startWork();
	// ��ԿЭ��
	int secKeyAgree(RequestMsg* reqmsg, char** outData, int& outLen);
	// ��ԿУ��
	int secKeyCheck();
	// ��Կע��
	int secKeyRevoke();
	// ��Կ�鿴
	int secKeyView();
	friend void * working(void * arg);
private:
	void getRandString(int len, char* randBuf);

	ServerInfo m_info;
	SecKeyShm* m_shm;
	TcpServer m_server;
	TcpSocket* m_client;
	std::map<pthread_t, TcpSocket*> m_listSocket;
	OCCIOP m_occi;
};

void * working(void * arg);