#pragma once
#ifndef Support_Array_Bits_h
#define Support_Array_Bits_h

#include<iostream>
#include<string>
#include<vector>

#include "QInt.h"
using namespace std;

//Chuyển hệ 2 về 10(không dấu)
unsigned int binSrting_To_decInt(string s);

//Chuyển unssigned int thành string
string decInt_To_BinString(unsigned int n);

//Hàm thêm cho đủ 32 kí tự trong chuỗi bit
string add_Full_32Bit(string bin);

//Hàm chuyển đổi từ string 32 bit sang số nguyên
unsigned int stringToInt(string a);

//Hàm chuyển string 128bit thành mảng int 4 phần tử
vector<unsigned int> stringToArrInt(string a);

#endif // !Support_Array_Bits_h