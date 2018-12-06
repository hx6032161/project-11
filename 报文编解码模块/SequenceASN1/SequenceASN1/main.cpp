#include <iostream>
#include "RequestCodec.h"
#include "RespondCodec.h"
#include "CodecFactory.h"
#include "RequestFactory.h"
#include "RespondFactory.h"
using namespace std;

int main()
{
	// 编码
	RequestMsg req;
	req.cmdType = 0;
	strcpy(req.clientId, "000");
	strcpy(req.authCode, "000");
	strcpy(req.serverId, "000");
	strcpy(req.r1, "000");

	//Codec* codec = new RequestCodec(&req);
	CodecFactory * f = new RequestFactory(&req);
	Codec * codec = f->createCodec();
	// 调用编码函数
	char* outData;
	int len;
	codec->msgEncode(&outData, len);

 	// ========================
	// 解码
	f = new RequestFactory();
	codec = f->createCodec();
	RequestMsg * tmp = (RequestMsg *)codec->msgDecode(outData, len);
	//codec = new RequestCodec();
	//RequestMsg* tmp = (RequestMsg*)codec->msgDecode(outData, len);
	cout << "cmdtype: " << tmp->cmdType << endl;
	cout << "serverID: " << tmp->serverId << endl;
	cout << "clientID: " << tmp->clientId << endl;
	cout << "r1: " << tmp->r1 << endl;

	cout << "----------------------------------" << endl;

	RespondMsg res("111", "111", "111", 111, 111);

	//父类指针指向子类对象
	//codec = new RespondCodec(&res);
	f = new RespondFactory(&res);
	codec = f->createCodec();
	//调用编码函数
	char* outData2;
	int len2;
	codec->msgEncode(&outData2, len2);

	//解码
	f = new RespondFactory();
	codec = f->createCodec();
	RespondMsg * res2 = (RespondMsg *)codec->msgDecode(outData2, len2);
	//codec = new RespondCodec();
	//RespondMsg * res2 = (RespondMsg *)codec->msgDecode(outData2, len2);
	cout << "rv: " << res2->rv << endl;
	cout << "clientId: " << res2->clientId << endl;
	cout << "serverId: " << res2->serverId << endl;
	cout << "r2: " << res2->r2 << endl;
	cout << "seckeyid: " << res2->seckeyid << endl;

	system("pause");
	return 0;
}