#include "SupportArrayBits.h"

//Chuyển hệ 2 về 10(không dấu)
unsigned int binSrting_To_decInt(string s)
{
	unsigned int ust = 0;
	for (int i = 0; i < 32; i++)
	{
		if (s[i] == '1')
			ust += pow(2, 31 - i);
	}
	return ust;
}

//Chuyển unssigned int thành string
string decInt_To_BinString(unsigned int n)
{
	if (n == 0)
		return n + "";

	if (n % 2 == 0)
		return decInt_To_BinString(n / 2) + "0";
	else
		return decInt_To_BinString(n / 2) + "1";
}

//Hàm thêm cho đủ 32 kí tự trong chuỗi bit
string add_Full_32Bit(string bin)
{
	int max = 32 - bin.length();
	for (int i = 0; i < max; i++)
		bin = "0" + bin;
	return bin;
}

//Hàm chuyển đổi từ string 32 bit sang số nguyên
unsigned int stringToInt(string a)
{
	unsigned int kq = 0;
	for (int i = 0; i < 32; i++)
	{
		if (a[i] == '1')
			kq += pow(2, 31 - i);
		else
			continue;
	}

	return kq;
}

//Hàm chuyển string 128bit thành mảng int 4 phần tử
vector<unsigned int> stringToArrInt(string a)
{
	string temp1, temp2, temp3, temp4;

	for (int i = 0; i < 32; i++)
	{
		temp1 += a[i];
		temp2 += a[i + 32];
		temp3 += a[i + 64];
		temp4 += a[i + 96];
	}

	vector<unsigned int> kq;

	kq.push_back(stringToInt(temp1));
	kq.push_back(stringToInt(temp2));
	kq.push_back(stringToInt(temp3));
	kq.push_back(stringToInt(temp4));

	return kq;
}