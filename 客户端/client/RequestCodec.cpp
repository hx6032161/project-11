#include "RequestCodec.h"

RequestCodec::RequestCodec() : Codec()
{
}

RequestCodec::RequestCodec(RequestMsg * msg)
{
	// ¸³Öµ²Ù×÷
	memcpy(&m_msg, msg, sizeof(RequestMsg));
}

RequestCodec::~RequestCodec()
{
}

/*
	struct RequestMsg
	{
		//1 ÃÜÔ¿Ð­ÉÌ  	//2 ÃÜÔ¿Ð£Ñé; 	// 3 ÃÜÔ¿×¢Ïú
		int		cmdType;		// ±¨ÎÄÀàÐÍ
		char	clientId[12];	// ¿Í»§¶Ë±àºÅ
		char	authCode[65];	// ÈÏÖ¤Âë
		char	serverId[12];	// ·þÎñÆ÷¶Ë±àºÅ 
		char	r1[64];			// ¿Í»§¶ËËæ»úÊý
	};
*/
int RequestCodec::msgEncode(char ** outData, int & len)
{
	writeHeadNode(m_msg.cmdType);
	writeNextNode(m_msg.clientId, strlen(m_msg.clientId) + 1);
	writeNextNode(m_msg.authCode, strlen(m_msg.authCode) + 1);
	writeNextNode(m_msg.serverId, strlen(m_msg.serverId) + 1);
	writeNextNode(m_msg.r1, strlen(m_msg.r1) + 1);
	packSequence(outData, len);

	return 0;
}

void * RequestCodec::msgDecode(char * inData, int inLen)
{
	unpackSequence(inData, inLen);
	readHeadNode(m_msg.cmdType);
	readNextNode(m_msg.clientId);
	readNextNode(m_msg.authCode);
	readNextNode(m_msg.serverId);
	readNextNode(m_msg.r1);

	return &m_msg;
}
