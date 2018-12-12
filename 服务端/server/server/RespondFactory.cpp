#include"RespondFactory.h"

//对数据进行解码的初始化调用
RespondFactory::RespondFactory()
{
	m_flag = false;

}
//对数据进行编码的初始化调用
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
		//编码
		Codec* codec = new RespondCodec(m_respond);
		return codec;
	}
	else
	{
		//解码
		Codec* codec = new RespondCodec();
		return codec;

	}
}


//bool m_flag;
//RespondMsg * m_respond;


