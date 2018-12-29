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
//	char			serverID[12];	// 服务器端编号
//	char			dbUse[24]; 		// 数据库用户名
//	char			dbPasswd[24]; 	// 数据库密码
//	char			dbSID[24]; 		// 数据库sid(192.168.10.145:1521/orcl)
//
//	unsigned short 	sPort;			// 服务器绑定的端口
//	int				maxnode;		// 共享内存最大网点数 客户端默认1个
//	int 			shmkey;			// 共享内存keyid 创建共享内存时使用	 
//};

ServerOperation::ServerOperation(const ServerInfo * info)
{
	//对m_info进行赋值
	memcpy(&m_info, info, sizeof(ServerInfo));
	//创建共享内存对像（需要释放）
	m_shm = new SecKeyShm(info->shmkey, info->maxnode);
	//连接oracle数据库
	bool bl = m_occi.connectDB(m_info.dbUse, m_info.dbPasswd, m_info.dbSID);
	if (!bl)
	{
		cout << "数据库 Oracle 连接失败..." << endl;
	}
}
ServerOperation::~ServerOperation()
{

}
//服务器开始工作
void ServerOperation::startWork()
{
	//开启监听
	m_server.setListen(m_info.sPort);
	while (1)
	{
		//获得用于客户端通信的类
		m_client = m_server.acceptConn();
		//创建子线程
		pthread_ threadID;
		pthread_create(&threadID, NULL, working, this);
		//子线程设置分离属性
		pthread_detach(threadID);
		//将客户端通信的类和客户端id一起存储到map中
		m_listSocket.insert(make_pair(threadID, m_client));
	}
}
int ServerOperation::secKeyAgree(RequestMsg* reqmsg, char** outData, int& outLen)
{
	RespondMsg resMsg;
	//生成随机字符串r2
	getRandString(sizeof(resMsg.r2), resMsg.r2);
	//将随机字符串r2和r1进行拼接， 然后生成秘钥
	char key[1024] = { 0 };
	unsigned char mdSha[SHA_DIGEST_LENGTH];
	sprintf(key, "%s%s", reqmsg->r1, resMsg.r2);
	SHA1((unsigned char*)key, strlen(key), (unsigned char*)mdSha);
	for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
	{
		sprintf(&key[i * 2], "%02x", mdSha[i]);
	}
	cout << "服务器端生成的秘钥: " << key << endl;
	//获取秘钥ID(从数据库中获取)
	resMsg.seckeyid = m_occi.getKeyID();	
	resMsg.rv = 0;	// 0: 成功, -1: 失败
	strcpy(resMsg.clientId, reqmsg->clientId);
	strcpy(resMsg.serverId, m_info.serverID);
	//将要发送给客户端的应答结构体进行编码
	//发送数据给客户端，传出参数赋值
	CodecFactory* factory = new RespondFactory(&resMsg);
	Codec* codec = factory->createCodec();
	codec->msgEncode(outData, outLen);
	//写入秘钥信息到共享内存
	NodeSHMInfo shmInfo;
	shmInfo.status = 1;
	shmInfo.seckeyID = resMsg.seckeyid;	// 从数据中读出的
	strcpy(shmInfo.clientID, reqmsg->clientId);
	strcpy(shmInfo.seckey, key);
	strcpy(shmInfo.serverID, m_info.serverID);
	m_shm->shmWrite(&shmInfo);
	//关闭连接

	return 0;
}
// 友元函数, 可以在该友元函数中通过对应的类对象调用期私有成员函数或者私有变量
// 子线程 - 进行业务流程处理
void * working(void * arg)
{
	//接受数据
	ServerOperation * op = (ServerOperation *)arg;
	//获取子线程id
	pthread_t thread = pthread_self();
	//通过子线程id获取通信类
	TcpSocket * client = op->m_listSocket[thread];
	//接受数据
	char * recvData = NULL;
	int recvLen = -1;
	client->recvMsg(&recvData, recvLen);
	//解码数据
	CodecFactory* factory = new RequestFactory();
	Codec* codec = factory->createCodec();
	RequestMsg * reqMsg = (RequestMsg*)codec->msgDecode(recvData, recvLen);
	//判断clientID是否合法
	
	//生成新的消息验证码key
	char key[1024] = { 0 };
	unsigned int mdLen = -1;
	unsigned char mdHmac[SHA256_DIGEST_LENGTH];
	sprintf(key, "@%s+%s@", op->m_info.serverID, reqMsg->clientId);
	cout << "原始数据: " << reqMsg->r1 << endl;
	cout << "key: " << key << endl;
	HMAC(EVP_sha256(), key, strlen(key),
		(unsigned char*)reqMsg->r1, strlen(reqMsg->r1), mdHmac, &mdLen);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
	{
		sprintf(&key[i * 2], "%02x", mdHmac[i]);
	}
	//服务器生成的消息认证码key和客户端的进行对比
	if (strcmp(key, reqMsg->authCode) != 0)
	{
		cout << "消息认证码不匹配..." << endl;
		return NULL;
	}
	//判断客户端的请求服务
	int len = -1;
	char* outData = NULL;
	switch (reqMsg->cmdType)
	{
	case RequestCodec::NewOrUpdate:
		// 秘钥协商函数
		op->secKeyAgree(reqMsg, &outData, len);
		break;
	case RequestCodec::Check:
		//秘钥检验函数
		op->secKeyCheck();
		break;
	case RequestCodec::Revoke:
		//秘钥注销函数
		op->secKeyRevoke();
		break;
	case RequestCodec::View:
		//秘钥查看函数
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
//	//服务器开始工作
//	void startWork();
//	// 秘钥协商
//	int secKeyAgree();
//	// 秘钥校验
//	int secKeyCheck();
//	// 秘钥注销
//	int secKeyRevoke();
//	// 秘钥查看
//	int secKeyView();
//
//private:
//	void getRandString(int len, char* randBuf);
//
//	ServerInfo m_info;
//	SecKeyShm* m_shm;
//};