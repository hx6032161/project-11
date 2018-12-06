#include "RespondCodec.h"

//struct  RespondMsg
//{
//	int	rv;		// 返回值
//	char	clientId[12];	// 客户端编号
//	char	serverId[12];	// 服务器编号
//	char	r2[64];		// 服务器端随机数
//	int		seckeyid;	// 对称密钥编号    keysn
//	RespondMsg() {}
//	RespondMsg(char* clientID, char* serverID, char* r2, int rv, int seckeyID)
//	{
//		this->rv = rv;
//		this->seckeyid = seckeyid;
//		strcpy(this->clientId, clientID);
//		strcpy(this->serverId, serverID);
//		strcpy(this->r2, r2);
//	}
//};

RespondCodec::RespondCodec()
{

}
RespondCodec::RespondCodec(RespondMsg *msg)
{
	memcpy(&m_msg, msg, sizeof(RespondMsg));
}
RespondCodec::~RespondCodec()
{

}

int RespondCodec::msgEncode(char ** outData, int &len)
{
	writeHeadNode(m_msg.rv);
	writeNextNode(m_msg.clientId, strlen(m_msg.clientId) + 1);
	writeNextNode(m_msg.serverId, strlen(m_msg.serverId) + 1);
	writeNextNode(m_msg.r2, strlen(m_msg.r2) + 1);
	writeNextNode(m_msg.seckeyid);
	packSequence(outData, len);
	return 0;
}

void* RespondCodec::msgDecode(char *inData, int inLen)
{
	//反序列化
	unpackSequence(inData, inLen);
	readHeadNode(m_msg.rv);
	readNextNode(m_msg.clientId);
	readNextNode(m_msg.serverId);
	readNextNode(m_msg.r2);
	readNextNode(m_msg.seckeyid); 
	return &m_msg;
}

