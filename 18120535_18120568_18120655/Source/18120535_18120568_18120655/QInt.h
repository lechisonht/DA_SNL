#ifndef _QInt_h
#define _QInt_h

#pragma once
#include<iostream>
#include<string>
#include<vector>

#include "SupportArrayBits.h"
#include "CalculateByString.h"

using namespace std;

class QInt
{
private:
	unsigned int arrayBits[4];
public:
	//constructor
	QInt();
	QInt(unsigned int arrayBits[4]);
	QInt(const QInt& num);
	QInt(vector<unsigned int> a);
	QInt(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

	//Trả về kích thước của kiểu QInt (128 bits)
	int size_of();

	//Chuyển chuỗi bits string thành 128 bits và lưu vào QInt
	void importToBitsString(string s);

	//Chuyển 128 bits trong QInt thành chuỗi string 128 kí tự bits
	string toStringBits();

	//destructor
	~QInt();

	//======Operator
	//Phép gán bằng
	QInt& operator=(const QInt& q);

	//Phép cộng 2 số QInt
	QInt operator+(QInt q);

	//Tạo số đối của số kiểu QInt
	QInt soDoi();

	//Phép trừ 2 sô kiểu QInt
	QInt operator-(QInt q);

	//Phép nhân 2 số kiểu QInt
	QInt operator*(QInt Q);

	//Phép chia 2 số kiểu QInt
	QInt operator/(QInt num);

	//Phép dịch phải
	QInt operator>>(int k);

	//Phép dịch trái
	QInt operator<<(int k);

	//Phép and
	QInt operator& (QInt a);

	//Phép or
	QInt operator| (QInt a);

	//Phép xor
	QInt operator^ (QInt a);

	//Phép not
	QInt operator~ ();

	//Phép xoay trái
	QInt rol();

	//Phéo xoay phải
	QInt ror();

	//======Truyền dữ liệu vào
	//Truyền vào string hệ 2 chuyển thành 128 bits lưu vào QInt
	void setTypeBin(string bin);

	//Truyền vào string hệ 10 chuyển thành 128 bits lưu vào QInt
	void setTypeDec(string dec);

	//Truyền vào string hệ 16 chuyển thành 128 bits lưu vào QInt
	void setTypeHex(string hex);

	//======Xuất dữ liệu ra ở dạng string
	//Xuất dữ liệu ra string ở dạng hệ 2
	string getTypeBin();

	//Xuất dữ liệu ra string ở dạng hệ 10
	string getTypeDec();

	//Xuất dữ liệu ra string ở dạng hệ 16
	string getTypeHex();
};

#endif // !_QInt_h