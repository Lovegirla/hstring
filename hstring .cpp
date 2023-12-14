#include <iostream>
using namespace std;
#define cap 1024//容量1024
class hstring
{
	char* buf;
	unsigned short value_len;
	unsigned short left_len;//buf中剩余容量
	unsigned short X;//容量倍数，以2倍方式扩充
	unsigned short length(const char* str)
	{
		unsigned short len{};
		while (str[len++]);
		return len;
	}
public:

	hstring() {
		X = 1;
		buf = new char[X* cap];
		left_len = X * cap;
	}
	/*
		常规构造函数 ↓
	*/
	hstring(const char* value):hstring() {

		value_len = length(value);
		if (value_len>left_len)
		{
			X = X * 2;
			buf = new char[X * cap];
			left_len = X * cap;
		}
		memcpy(buf,value,value_len);
		left_len -= value_len;
	}
	/*
		拷贝构造函数 ↓
	*/
	hstring(const hstring& Other) :hstring(Other.Get())
	{
	}
	/*
		获得当前的缓冲区的值 ↓
	*/
	char* Get()  const
	{
		return buf;
	}
	/*
		设置当前的缓冲区的值 ↓
	*/
	char* Set(const char* value) 
	{
		value_len = length(value);
		memcpy(buf,value,value_len);
		left_len -= value_len;
	}
	hstring operator+(const char* pOther)
	{
		unsigned cur_len = length(buf);
		value_len = length(pOther);
		if (value_len<left_len)
		{
			memcpy(buf + cur_len - 1, pOther, value_len);
		}
		else {
			X = X * 2;
			char* temp = new char[X * cap];
			memcpy(temp,buf,length(buf));
			free(buf);
			buf = temp;
			left_len = X * cap - left_len;
		}
		left_len -= value_len;
		return buf;
	}
	hstring operator-(const char* pOther)
	{
		unsigned short pos = 0; 

		for (unsigned short i = 0; i < value_len; ++i) {
			if (memcmp(buf + i, pOther, strlen(pOther)) == 0) {
				i += length(pOther) - 2;
			}
			else {
				buf[pos++] = buf[i]; 
			}
		}
		buf[pos] = '\0';
		value_len = pos;

		return buf;
	}
	hstring operator=(hstring hOther)
	{
		value_len = length(hOther.Get());
		if (value_len<left_len)
		{
			memcpy(buf, hOther.Get(), value_len);
		}
		else {
			X = X * 2;
			char* temp = new char[X * cap];
			memcpy(temp, buf, length(buf));
			free(buf);
			buf = temp;
			left_len = X * cap - left_len;
		}
		left_len -= value_len;
		return buf;
	}
	hstring operator=(const char* pOther)
	{
		value_len = length(pOther);
		if (value_len<left_len)
		{
			memcpy(buf, pOther, value_len);
		}
		else
		{
			X = X * 2;
			char* temp = new char[X * cap];
			memcpy(temp, buf, length(buf));
			free(buf);
			buf = temp;
			left_len = X * cap - left_len;
		}
		left_len -= value_len;
		return buf;
	}
	//实现int转hstring
	hstring operator=(int iOther)
	{
		int temp = iOther;
		value_len = 0;
		while (temp)
		{
			temp /= 10;
			value_len++;
		}
		if (value_len>left_len)
		{
			X = X * 2;
			char* temp = new char[X * cap];
			memcpy(temp, buf, length(buf));
			free(buf);
			buf = temp;
			left_len = X * cap -left_len;
		}
		char tempBuf[cap];
		memset(tempBuf, '0', cap);
		tempBuf[value_len] = '\0';

		int index = value_len - 1;
		do {
			tempBuf[index--] = '0'+iOther % 10;
			iOther /= 10;
		} while (iOther != 0);

		memcpy(buf, tempBuf, value_len+1);
		return buf;
	}
	// 查找子字符串的位置
	int find(const char* pOther) const {
		for (unsigned short i = 0; i <= value_len - strlen(pOther); ++i) {
			if (memcmp(buf + i, pOther, strlen(pOther)) == 0) {
				return i;
			}
		}
		return -1; 
	}
	//替换字符串
	hstring replace(unsigned short pos, const char* newData) {
		if (pos < value_len) {
			unsigned short newDataLen = length(newData)-1;
			unsigned short remainingLen = value_len - pos - 1;
			memmove(buf + pos + newDataLen, buf + pos + 1, remainingLen);
			memcpy(buf + pos, newData, newDataLen);
			value_len = value_len + newDataLen - 1;
		}

		return buf;
	}
	~hstring()
	{
		delete[] buf;
	}
};
//unit test
//int main() {
//	hstring my_string{"hello"};
//	hstring str{ my_string };
//	str = (str + "123");
//	str = "1234567f";
//	str = str - "34";
//	int flag = str.find("59");
//	str.replace(2,"88");
//	cout << str.Get()<< endl;
//}