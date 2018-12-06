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
		//��Ҫ��������Ķ���
		Codec* codec = new RequestCodec(m_request);
		return codec;
	}
	else
	{
		//��Ҫ��������Ķ���
		Codec* codec = new RequestCodec();
		return codec;

	}

}

//	bool m_flag = false;
//	RequestMsg * m_request;

