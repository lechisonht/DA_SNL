#pragma once
#include <iostream>
#include <string>

using namespace std;

//Hàm a lũy thừa n trả về số nguyên hệ 10 kiểu string (a = 2, 0 < n < 127) (hàm viết để sử dụng chuyển đổi hệ 10 nên chỉ đúng với cơ số 2)
string power(int a, int n);

//Hàm cộng hai chuỗi string hệ 10
string sum(string Num1, string Num2);

//Hàm trừ hai chuỗi string hệ 10
string subtract(string Num1, string Num2);

//Hàm nhân hai chuỗi string hệ 10
string mult(string Num1, string Num2);

//Hàm chia một chuỗi số thập phân cho 2
string stringDecDiv2(string dec);

//Chuyển string số hệ 10 thành kiểu Int
int stringDecToInt(string num);