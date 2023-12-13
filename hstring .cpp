#include <iostream>
#include <stdio.h>
using namespace std;

class hstring
{
	char* buf;
	unsigned short value_len;
	unsigned short length(const char* str)
	{
		unsigned short len{};
		while (str[len++]);
		return len;
	}
public:

	hstring() {
		buf = new char[1024];
	}
	/*
		���湹�캯�� ��
	*/
	hstring(const char* value) {
		buf = new char[1024];
		value_len = length(value);
		memcpy(buf,value,value_len);
	}
	/*
		�������캯�� ��
	*/
	hstring(const hstring& Other) :hstring(Other.Get())
	{
	}
	/*
		��õ�ǰ�Ļ�������ֵ ��
	*/
	char* Get()  const
	{
		return buf;
	}
	/*
		���õ�ǰ�Ļ�������ֵ ��
	*/
	char* Set(const char* value) 
	{
		value_len = length(value);
		memcpy(buf,value,value_len);
	}
	hstring operator+(const char* pOther)
	{
		memcpy(buf,pOther,sizeof(pOther));
		return buf;
	}
	hstring operator=(const char* pOther)
	{
		memcpy(buf, pOther, sizeof(pOther));
		return buf;
	}

	~hstring()
	{
		delete[] buf;
	}
};
//unit test
int main() {
	hstring my_string{"hello"};
	hstring str{ my_string };
	cout << (char*)str.Get() << endl;
}