#include"RequestFactory.h"


RequestFactory::RequestFactory()
{
	m_flag = false;
}
RequestFactory::RequestFactory(RequestMsg* msg)
{
	m_flag = true;
	m_request = msg;
}
RequestFactory::~RequestFactory()
{

}

Codec* RequestFactory::createCodec()
{
	if (m_flag == true)
	{
		//需要编码操作的对象
		Codec* codec = new RequestCodec(m_request);
		return codec;
	}
	else
	{
		//需要解码操作的对象
		Codec* codec = new RequestCodec();
		return codec;

	}

}

//	bool m_flag = false;
//	RequestMsg * m_request;

