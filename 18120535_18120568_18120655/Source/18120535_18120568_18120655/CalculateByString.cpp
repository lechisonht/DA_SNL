#include "CalculateByString.h"

//Hàm a lũy thừa n trả về số nguyên hệ 10 kiểu string (a = 2, 0 < n < 127) (hàm viết để sử dụng chuyển đổi hệ 10 nên chỉ đúng với cơ số 2)
string power(int a, int n)
{
	string kq = "1";
	int pow = n;

	//tràn số
	if (n > 126)
	{
		pow = 126;
	}

	for (int i = 1; i <= pow; i++)
	{
		kq = mult(kq, "2");
	}

	return kq;
}

//Hàm cộng hai chuỗi string hệ 10
string sum(string Num1, string Num2)
{
	if (Num1[0] == '-' && Num2[0] != '-')
	{
		Num1.erase(Num1.begin());
		Num1 = subtract(Num2, Num1);
	}
	else
	{
		if (Num2[0] == '-' && Num1[0] != '-')
		{
			Num2.erase(Num2.begin());
			Num1 = subtract(Num1, Num2);
		}
		else
		{
			int Temp = 0;
			bool Negative = false;

			if (Num1[0] == '-' && Num2[0] == '-')
			{
				Negative = true;
			}
			if (Num1.size() > Num2.size())
			{
				while (Num1.size() != Num2.size())
				{
					Num2.insert(Num2.begin(), '0');
				}
			}
			else
			{
				while (Num1.size() != Num2.size())
				{
					Num1.insert(Num1.begin(), '0');
				}
			}


			for (int i = Num1.size() - 1; i > -1; i--)
			{
				Temp = Temp + Num1[i] + Num2[i] - 2 * '0';
				Num1[i] = (Temp % 10) + '0';
				Temp = Temp / 10;
			}


			if (Temp != 0)
			{
				Num1.insert(Num1.begin(), Temp + '0');
				Temp = 0;
			}
		}
		return Num1;
	}
}

//Hàm trừ hai chuỗi string hệ 10
string subtract(string Num1, string Num2)
{
	int Temp = 0;

	//kiểm tra số âm
	bool Negative = false;


	if (Num1.size() > Num2.size())
	{
		while (Num1.size() != Num2.size())
		{
			Num2.insert(Num2.begin(), '0');
		}
	}
	else
	{
		while (Num1.size() != Num2.size())
		{
			Num1.insert(Num1.begin(), '0');
		}
	}


	if (strcmp(Num1.c_str(), Num2.c_str()) < 0)
	{
		string TempStr = Num1;
		Num1 = Num2;
		Num2 = TempStr;
		Negative = true;
	}

	//Thực hiện phép trừ.
	for (int i = Num1.size() - 1; i > -1; i--)
	{
		if ((Num1[i] - Temp) < Num2[i])
		{
			Num1[i] = (10 + Num1[i] - Num2[i] - Temp) + '0';
			Temp = 1;
		}
		else
		{
			Num1[i] = Num1[i] - Num2[i] - Temp + '0';
			Temp = 0;
		}
	}


	while (Num1[0] == '0')
	{
		Num1.erase(Num1.begin());
	}

	if (Negative == true)
	{
		Num1.insert(Num1.begin(), '-');
	}
	return Num1;
}

//Hàm nhân hai chuỗi string hệ 10
string mult(string Num1, string Num2)
{
	string Result = "0";
	string TempStr;
	int Temp = 0;

	//Kiểm tra số âm
	bool Negative = false;

	if (Num1[0] == '-')
	{
		if (Num2[0] != '-')
		{
			Negative = true;
		}
		Num1.erase(Num1.begin());
	}
	if (Num2[0] == '-')
	{
		if (Num1[0] != '-')
		{
			Negative = true;
		}
		Num2.erase(Num2.begin());
	}

	for (int i = 0; i < Num2.size(); i++)
	{
		for (int j = Num1.size() - 1; j > -1; j--)
		{
			Temp = Temp + (Num1[j] - '0') * (Num2[Num2.size() - i - 1] - '0');
			TempStr.push_back((Temp % 10) + '0');
			Temp = Temp / 10;
		}
		if (Temp != 0) //Nếu vẫn còn Temp.
		{
			TempStr.push_back(Temp + '0');
			Temp = 0;
		}

		//Ðảo chuỗi.
		reverse(TempStr.begin(), TempStr.end());

		//Thêm các số 0 cần thiết vào sau.
		for (int j = 0; j < i; j++)
		{
			TempStr.push_back('0');
		}

		//Cộng Result và Temp.
		Result = sum(Result, TempStr);
		TempStr.clear(); //Clear chuỗi tạm để dùng cho các bước sau.
	}

	if (Negative == true)
	{
		Result.insert(Result.begin(), '-');
	}

	return Result;
}

//Hàm chia một chuỗi số thập phân cho 2
string stringDecDiv2(string dec)
{
	string kq;
	int temp = 0;

	//loop
	for (int i = 0; i < dec.size(); i++)
	{
		temp = temp * 10 + (dec[i] - '0');
		if (i > 0 || (i == 0 && temp >= 2))
			kq.push_back((temp / 2) + '0');
		temp %= 2;
	}

	return kq;
}

int stringDecToInt(string num)
{
	int kq = 0;
	for (int i = 0; i < num.size(); i++)
	{
		char k = num[i] - '0';
		kq += k * pow(10, num.size() - i - 1);
	}
	return kq;
}
