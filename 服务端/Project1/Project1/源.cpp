//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//using namespace std;
//
//
//
//class MyString
//{
//public:
//	friend ostream & operator<<(ostream &out, MyString &obj);
//	friend istream & operator>>(istream &in, MyString &obj);
//public:
//	MyString();
//	MyString(const char *str);
//	MyString(const MyString &str);
//	~MyString();
//	MyString& operator=(const MyString &str);
//	MyString& operator=(const char* str);
//	//+
//	MyString operator+(const MyString &str);
//	MyString operator+(const char* str);
//	
//	MyString operator>>(const char* str);
//
//private:
//	char *m_str;
//	int m_size;
//	int m_capacity;
//};
//
////默认构造
//MyString::MyString()
//{
//	m_str = new char[10];
//	memset(m_str, 0, 10);
//	m_size = 0;
//	m_capacity = 10;
//}
////有参构造
//MyString::MyString(const char *str)
//{
//	m_size = strlen(str);
//	m_str = new char[m_size + 1];
//	strcpy(m_str, str);
//	m_capacity = m_size;
//}
////拷贝构造
//MyString::MyString(const MyString &str)
//{
//	this->m_size = str.m_size;
//	this->m_str = new char[this->m_size + 1];
//	strcpy(this->m_str, str.m_str);
//	m_capacity = m_size;
//}
////析构
//MyString::~MyString()
//{
//	if (NULL != m_str)
//	{
//		delete[]m_str;
//		m_str = NULL;
//	}
//}
//
////=号重载
//MyString& MyString::operator=(const MyString &str)
//{
//	if (NULL != this->m_str)
//	{
//		delete[]m_str;
//	}
//	this->m_size = str.m_size;
//	this->m_str = new char[this->m_size + 1];
//	strcpy(this->m_str, str.m_str);
//
//	m_capacity = m_size;
//	return *this;
//}
//MyString& MyString::operator=(const char* str)
//{
//	if (NULL != this->m_str)
//	{
//		delete[]m_str;
//	}
//	this->m_size = strlen(str);
//	this->m_str = new char[this->m_size + 1];
//	strcpy(this->m_str, str);
//
//	m_capacity = m_size;
//	return *this;
//}
////加号重载
//MyString MyString::operator+(const MyString &str)
//{
//	char temp[1024] = {0};
//	sprintf(temp, "%s%s", this->m_str, str.m_str);
//	MyString strnew(temp);
//	return strnew;
//}
//
//MyString MyString::operator+(const char * str)
//{
//	char temp[1024] = { 0 };
//	sprintf(temp, "%s%s", this->m_str, str);
//	MyString strnew(temp);
//	return strnew;
//}
//
//ostream & operator<<(ostream &out, MyString &obj)
//{
//	out << obj.m_str;
//	return out;
//}
//
//istream & operator>>(istream &in, MyString &obj)
//{
//	in >> obj.m_str;
//	return in;
//}
//
//int main()
//{
//	MyString a;
//	MyString d("abc");
//	MyString e("def");
//
//	char b[10];
//
//	a = d + e;
//	MyString strnew = d + e;
//	//cout << "123456" << endl;
//	//MyString
//	cout << a << endl;
//	cin >> a;
//	cout << a << endl;
//	system("pause");
//	return 0;
//}