#include"ServerOperation.h"
#include<iostream>
#include <pthread.h>
#include <string.h>
#include "RequestFactory.h"
#include "RespondFactory.h"
#include <openssl/hmac.h>
#include <openssl/sha.h>
using namespace std;

//class ServerInfo
//{
//public:
//	char			serverID[12];	// �������˱��
//	char			dbUse[24]; 		// ���ݿ��û���
//	char			dbPasswd[24]; 	// ���ݿ�����
//	char			dbSID[24]; 		// ���ݿ�sid(192.168.10.145:1521/orcl)
//
//	unsigned short 	sPort;			// �������󶨵Ķ˿�
//	int				maxnode;		// �����ڴ���������� �ͻ���Ĭ��1��
//	int 			shmkey;			// �����ڴ�keyid ���������ڴ�ʱʹ��	 
//};

ServerOperation::ServerOperation(const ServerInfo * info)
{
	//��m_info���и�ֵ
	memcpy(&m_info, info, sizeof(ServerInfo));
	//���������ڴ������Ҫ�ͷţ�
	m_shm = new SecKeyShm(info->shmkey, info->maxnode);
	//����oracle���ݿ�
	bool bl = m_occi.connectDB(m_info.dbUse, m_info.dbPasswd, m_info.dbSID);
	if (!bl)
	{
		cout << "���ݿ� Oracle ����ʧ��..." << endl;
	}
}
ServerOperation::~ServerOperation()
{

}
//��������ʼ����
void ServerOperation::startWork()
{
	//��������
	m_server.setListen(m_info.sPort);
	while (1)
	{
		//������ڿͻ���ͨ�ŵ���
		m_client = m_server.acceptConn();
		//�������߳�
		pthread_ threadID;
		pthread_create(&threadID, NULL, working, this);
		//���߳����÷�������
		pthread_detach(threadID);
		//���ͻ���ͨ�ŵ���Ϳͻ���idһ��洢��map��
		m_listSocket.insert(make_pair(threadID, m_client));
	}
}
int ServerOperation::secKeyAgree()
{
	//��֤��Ϣ��֤�� �ж���Ϣ�Ƿ񱻴۸�

	//��������ַ���r2

	//������ַ���r2��r1����ƴ�ӣ� Ȼ��������Կ

	//��ȡ��ԿID(�����ݿ��л�ȡ)

	//��Ҫ���͸��ͻ��˵�Ӧ��ṹ����б���

	//�������ݸ��ͻ���

	//д����Կ��Ϣ�������ڴ�

	//�ر�����

}
// ��Ԫ����, �����ڸ���Ԫ������ͨ����Ӧ������������˽�г�Ա��������˽�б���
// ���߳� - ����ҵ�����̴���
void * working(void * arg)
{
	//��������
	ServerOperation * op = (ServerOperation *)arg;
	//��ȡ���߳�id
	pthread_t thread = pthread_self();
	//ͨ�����߳�id��ȡͨ����
	TcpSocket * client = op->m_listSocket[thread];
	//��������
	char * recvData = NULL;
	int recvLen = -1;
	client->recvMsg(&recvData, recvLen);
	//��������
	CodecFactory* factory = new RequestFactory();
	Codec* codec = factory->createCodec();
	RequestMsg * reqMsg = (RequestMsg*)codec->msgDecode(recvData, recvLen);
	//�ж�clientID�Ƿ�Ϸ�,�����µ���Ϣ��֤��key
	char key[1024] = { 0 };
	unsigned int mdLen = -1;
	unsigned char mdHmac[SHA256_DIGEST_LENGTH];
	sprintf(key, "@%s+%s@", op->m_info.serverID, reqMsg->clientId);
	cout << "ԭʼ����: " << reqMsg->r1 << endl;
	cout << "key: " << key << endl;
	HMAC(EVP_sha256(), key, strlen(key),
		(unsigned char*)reqMsg->r1, strlen(reqMsg->r1), mdHmac, &mdLen);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
	{
		sprintf(&key[i * 2], "%02x", mdHmac[i]);
	}
	//���������ɵ���Ϣ��֤��key�Ϳͻ��˵Ľ��жԱ�
	if (strcmp(key, reqMsg->authCode) != 0)
	{
		cout << "��Ϣ��֤�벻ƥ��..." << endl;
		return NULL;
	}
	//�жϿͻ��˵��������
	int len = -1;
	char* outData = NULL;
	switch (reqMsg->cmdType)
	{
	case RequestCodec::NewOrUpdate:
		// ��ԿЭ�̺���
		op->secKeyAgree(reqMsg, &outData, len);
		break;
	case RequestCodec::Check:
		//��Կ���麯��
		op->secKeyCheck();
		break;
	case RequestCodec::Revoke:
		//��Կע������
		op->secKeyRevoke();
		break;
	case RequestCodec::View:
		//��Կ�鿴����
		op->secKeyView();
		break;
	default:
		break;
	}

}


//class ServerOperation
//{
//public:
//	ServerOperation(ServerInfo info);
//	~ServerOperation();
//	//��������ʼ����
//	void startWork();
//	// ��ԿЭ��
//	int secKeyAgree();
//	// ��ԿУ��
//	int secKeyCheck();
//	// ��Կע��
//	int secKeyRevoke();
//	// ��Կ�鿴
//	int secKeyView();
//
//private:
//	void getRandString(int len, char* randBuf);
//
//	ServerInfo m_info;
//	SecKeyShm* m_shm;
//};