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
		//ÐèÒª±àÂë²Ù×÷µÄ¶ÔÏó
		Codec* codec = new RespondCodec(m_respond);
		return codec;
	}
	else
	{
		//ÐèÒª½âÂë²Ù×÷µÄ¶ÔÏó
		Codec* codec = new RespondCodec();
		return codec;

	}
}


//bool m_flag;
//RespondMsg * m_respond;


