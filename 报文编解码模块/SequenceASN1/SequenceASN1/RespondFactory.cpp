#include"RespondFactory.h"


RespondFactory::RespondFactory()
{
	m_flag = false;

}
RespondFactory::RespondFactory(RespondMsg *msg)
{
	m_flag = true;
	m_respond = msg;
}
RespondFactory::~RespondFactory()
{

}

Codec* RespondFactory::createCodec()
{
	if (m_flag == true)
	{
		//需要编码操作的对象
		Codec* codec = new RespondCodec(m_respond);
		return codec;
	}
	else
	{
		//需要解码操作的对象
		Codec* codec = new RespondCodec();
		return codec;

	}
}


//bool m_flag;
//RespondMsg * m_respond;


