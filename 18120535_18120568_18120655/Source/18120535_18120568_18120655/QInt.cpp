#include "QInt.h"

using namespace std;


//constructor
QInt::QInt()
{
	arrayBits[0] = 0;
	arrayBits[1] = 0;
	arrayBits[2] = 0;
	arrayBits[3] = 0;
}

QInt::QInt(unsigned int arrayBits[4])
{
	this->arrayBits[0] = arrayBits[0];
	this->arrayBits[1] = arrayBits[1];
	this->arrayBits[2] = arrayBits[2];
	this->arrayBits[3] = arrayBits[3];
}

QInt::QInt(const QInt& num)
{
	this->arrayBits[0] = num.arrayBits[0];
	this->arrayBits[1] = num.arrayBits[1];
	this->arrayBits[2] = num.arrayBits[2];
	this->arrayBits[3] = num.arrayBits[3];
}

QInt::QInt(vector<unsigned int> a)
{
	for (int i = 0; i < 4; i++)
		this->arrayBits[i] = a[i];
}

QInt::QInt(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
	arrayBits[0] = a;
	arrayBits[1] = b;
	arrayBits[2] = c;
	arrayBits[3] = d;
}

//Trả về kích thước của kiểu QInt (128 bits)
int QInt::size_of()
{
	return 128;
}

//Chuyển chuỗi bits string thành 128 bits và lưu vào QInt
void QInt::importToBitsString(string s)
{
	if (s.size() < 128)
	{
		string temp;
		temp.assign(128 - s.size(), '0');
		s = temp + s;
	}
	else
		if (s.size() > 128)
			s = s.substr(s.size() - 128, 128);

	string s0 = s.substr(0, 32);
	string s1 = s.substr(32, 32);
	string s2 = s.substr(64, 32);
	string s3 = s.substr(96, 32);
	this->arrayBits[0] = binSrting_To_decInt(s0);
	this->arrayBits[1] = binSrting_To_decInt(s1);
	this->arrayBits[2] = binSrting_To_decInt(s2);
	this->arrayBits[3] = binSrting_To_decInt(s3);
}

//Chuyển 128 bits trong QInt thành chuỗi string 128 kí tự bits
string QInt::toStringBits()
{
	string kq;

	kq += add_Full_32Bit(decInt_To_BinString(this->arrayBits[0]));
	kq += add_Full_32Bit(decInt_To_BinString(this->arrayBits[1]));
	kq += add_Full_32Bit(decInt_To_BinString(this->arrayBits[2]));
	kq += add_Full_32Bit(decInt_To_BinString(this->arrayBits[3]));

	return kq;
}

//destructor
QInt::~QInt()
{
}

//Phép gán bằng
QInt& QInt::operator=(const QInt& q)
{
	if (this == &q) //kiểm tra có cùng đối tượng không
		return *this;
	this->arrayBits[0] = q.arrayBits[0];
	this->arrayBits[1] = q.arrayBits[1];
	this->arrayBits[2] = q.arrayBits[2];
	this->arrayBits[3] = q.arrayBits[3];
	return *this;
}

//Phép cộng 2 số QInt
QInt QInt::operator+(QInt q)
{
	string n1 = this->toStringBits();//số thư 1 
	string n2 = q.toStringBits();//số thứ 2
	string sum; sum.empty();//Tổng nhị phân
	int d = 0;
	for (int i = 127; i > -1; i--)
	{
		int t = 0;//tổng các cặp bit
		string temp; temp.empty();//Biến lưu kí tự tổng 
		int a = stoi(n1.substr(i, 1));
		int b = stoi(n2.substr(i, 1));
		t = d + a + b;
		if (t == 3) { temp += "1"; d = 1; }
		else if (t == 2) { temp += "0"; d = 1; }
		else if (t == 1) { temp += "1"; d = 0; }
		else if (t == 0) { temp += "0"; d = 0; }
		sum = temp + sum;
	}
	string s0 = sum.substr(0, 32), s1 = sum.substr(32, 32), s2 = sum.substr(64, 32), s3 = sum.substr(96, 32); //chia thành 4 phần
	QInt sumQInt;//Tổng QInt
	sumQInt.arrayBits[0] = binSrting_To_decInt(s0);
	sumQInt.arrayBits[1] = binSrting_To_decInt(s1);
	sumQInt.arrayBits[2] = binSrting_To_decInt(s2);
	sumQInt.arrayBits[3] = binSrting_To_decInt(s3);
	return sumQInt;
}

//Tạo số đối của số kiểu QInt
QInt QInt::soDoi()
{
	string s = this->toStringBits();
	string temp;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '0')
			temp += "1";
		else if (s[i] == '1')
			temp += "0";
	}
	QInt soDB;
	soDB.importToBitsString(temp);
	QInt so(0, 0, 0, 1);//Số 1
	QInt SoDoi = soDB + so;//Số đối 
	return SoDoi;
}

//Phép trừ 2 sô kiểu QInt
QInt QInt::operator-(QInt q)
{
	QInt sd = q.soDoi();
	QInt hieu = *this + sd;
	return hieu;
}

//Phép nhân 2 số kiểu QInt
QInt QInt::operator*(QInt Q)
{
	QInt A(0, 0, 0, 0);
	char Q1 = '0';
	int k = Q.size_of();

	while (k > 0)
	{
		unsigned int q0 = Q.arrayBits[3] & 1;

		if (q0 == 1 && Q1 == '0')
			A = A - *this;
		else
			if (q0 == 0 && Q1 == '1')
				A = A + *this;

		unsigned int a0 = A.arrayBits[3] & 1;

		A = A >> 1;
		Q = Q >> 1;

		string arrBitsQ = Q.toStringBits();

		if (a0)
			arrBitsQ[0] = '1';
		else
			arrBitsQ[0] = '0';

		Q.importToBitsString(arrBitsQ);

		if (q0)
			Q1 = '1';
		else
			Q1 = '0';

		k--;
	}

	string kq = A.toStringBits() + Q.toStringBits();

	QInt tich;
	tich.importToBitsString(kq);
	return tich;
}

//Phép chia 2 số kiểu QInt
QInt QInt::operator/(QInt M)
{
	QInt A(0, 0, 0, 0);
	QInt Q(*this);
	bool dauAm;
	if ((M.arrayBits[0] >> 31 & 1) != (Q.arrayBits[0] >> 31 & 1))
		dauAm = true;
	else
		dauAm = false;

	if (M.arrayBits[0] >> 31 & 1)
		M = M.soDoi();

	if (Q.arrayBits[0] >> 31 & 1)
	{
		Q = Q.soDoi();
	}

	int k = Q.size_of();
	while (k > 0)
	{
		bool Qn = Q.arrayBits[0] >> 31 & 1;
		A = A << 1;
		Q = Q << 1;

		string arrBitsA = A.toStringBits();
		if (Qn)
			arrBitsA[A.size_of() - 1] = '1';
		else
			arrBitsA[A.size_of() - 1] = '0';

		A.importToBitsString(arrBitsA);

		A = A - M;
		if (A.arrayBits[0] >> 31 & 1)
		{
			A = A + M;
		}
		else
		{
			string arrBitsQ = Q.toStringBits();
			arrBitsQ[Q.size_of() - 1] = '1';
			Q.importToBitsString(arrBitsQ);
		}

		k--;
	}

	if (dauAm)
		Q = Q.soDoi();

	return Q;
}

//Phép dịch phải
QInt QInt::operator>>(int k)
{
	QInt kq;
	string s = this->toStringBits();
	string temp;
	if (k > 128)
	{
		temp.assign(128, s[0]);
		kq.importToBitsString(temp);
		return kq;
	}

	temp.assign(k, s[0]);
	temp += s.substr(0, 128 - k);//thêm phần bit sau khi dịch phải cho đủ 128 bit
	kq.importToBitsString(temp);
	return kq;
}

//Phép dịch trái
QInt QInt::operator<<(int k)
{
	if (k > 128)
	{
		return QInt(0, 0, 0, 0);
	}
	QInt kq;
	string s = this->toStringBits();
	s = s.substr(k);//cắt và gán trở lại bit từ k đến 128 tức là xóa k bit đầu
	for (int i = 0; i < k; i++)//thêm cho đủ 128 bit
		s += '0';
	kq.importToBitsString(s);
	return kq;
}

//Setting Function operator &
QInt QInt::operator& (QInt a)
{
	//Biến arr dùng để copy chuỗi 128 bit
	string arr1, arr2;
	arr1 = this->toStringBits();
	arr2 = a.toStringBits();

	string temp;

	for (int i = 0; i < 128; i++)
	{
		if (arr1[i] == '1' && arr1[i] == arr2[i])
			temp.push_back('1');
		else temp.push_back('0');
	}

	vector<unsigned int> kq1 = stringToArrInt(temp);

	QInt kq(kq1);

	return kq;
}

//Setting Function operator |
QInt QInt::operator|(QInt a)
{
	//Biến arr dùng để copy chuỗi 128 bit
	string arr1, arr2;
	arr1 = this->toStringBits();
	arr2 = a.toStringBits();

	string temp;

	for (int i = 0; i < 128; i++)
	{
		if (arr1[i] == '1' || arr2[i] == '1')
			temp.push_back('1');
		else temp.push_back('0');
	}

	vector<unsigned int> kq1 = stringToArrInt(temp);

	QInt kq(kq1);

	return kq;
}

//Setting Function operator ^
QInt QInt::operator^(QInt a)
{
	//Biến arr dùng để copy chuỗi 128 bit
	string arr1, arr2;
	arr1 = this->toStringBits();
	arr2 = a.toStringBits();

	string temp;

	for (int i = 0; i < 128; i++)
	{
		if (arr1[i] != arr2[i])
			temp.push_back('1');
		else temp.push_back('0');
	}

	vector<unsigned int> kq1 = stringToArrInt(temp);

	QInt kq(kq1);

	return kq;
}

//Setting Function operator ~
QInt QInt::operator~()
{
	//Biến arr dùng để copy chuỗi 128 bit
	string arr;
	arr = this->toStringBits();

	string temp;

	for (int i = 0; i < 128; i++)
	{
		if (arr[i] == '1')
			temp.push_back('0');
		else temp.push_back('1');
	}

	vector<unsigned int> kq1 = stringToArrInt(temp);

	QInt kq(kq1);

	return kq;
}

//Setting Function rol (rotate left)
QInt QInt::rol()
{
	//Biến arr dùng để copy chuỗi 128 bit
	string arr;
	arr = this->toStringBits();

	string temp;

	for (int i = 1; i < 128; i++)
	{
		temp.push_back(arr[i]);
	}

	temp.push_back(arr[0]);

	vector<unsigned int> kq1 = stringToArrInt(temp);

	QInt kq(kq1);

	return kq;
}

//Setting Function ror (rotate right)
QInt QInt::ror()
{
	//Biến arr dùng để copy chuỗi 128 bit
	string arr;
	arr = this->toStringBits();

	string temp;

	temp.push_back(arr[127]);

	for (int i = 0; i < 127; i++)
	{
		temp.push_back(arr[i]);
	}

	vector<unsigned int> kq1 = stringToArrInt(temp);

	QInt kq(kq1);

	return kq;
}

//======Truyền dữ liệu vào
//Truyền vào string hệ 2 chuyển thành 128 bits lưu vào QInt
void QInt::setTypeBin(string bin)
{
	this->importToBitsString(bin);
}

//Truyền vào string hệ 10 chuyển thành 128 bits lưu vào QInt
void QInt::setTypeDec(string dec)
{
	string bin;
	bool ktSoAm = false;

	if (dec[0] == '-')
	{
		dec.erase(dec.begin());
		ktSoAm = true;
	}

	while (dec != "")
	{
		bin.push_back(((dec[dec.size() - 1] - '0') % 2) + '0');
		dec = stringDecDiv2(dec);
	}

	reverse(bin.begin(), bin.end());

	if (ktSoAm)
	{
		this->importToBitsString(bin);
		*this = this->soDoi();
		return;
	}

	this->importToBitsString(bin);
}

//Truyền vào string hệ 16 chuyển thành 128 bits lưu vào QInt
void QInt::setTypeHex(string hex)
{
	string temp; temp.empty();
	for (int i = 0; i < hex.size(); i++)
	{
		char t = hex[i];
		if (hex[i] == '0') 
			temp += "0000";
		else if (hex[i] == '1') temp += "0001";
		else if (hex[i] == '2') temp += "0010";
		else if (hex[i] == '3') temp += "0011";
		else if (hex[i] == '4') temp += "0100";
		else if (hex[i] == '5') temp += "0101";
		else if (hex[i] == '6') temp += "0110";
		else if (hex[i] == '7') temp += "0111";
		else if (hex[i] == '8') temp += "1000";
		else if (hex[i] == '9') temp += "1001";
		else if (hex[i] == 'A') temp += "1010";
		else if (hex[i] == 'B') temp += "1011";
		else if (hex[i] == 'C') temp += "1100";
		else if (hex[i] == 'D') temp += "1101";
		else if (hex[i] == 'E') temp += "1110";
		else if (hex[i] == 'F') temp += "1111";
	}
	this->importToBitsString(temp);
}

//======Xuất dữ liệu ra ở dạng string
//Xuất dữ liệu ra string ở dạng hệ 2
string QInt::getTypeBin()
{
	return this->toStringBits();
}

//Xuất dữ liệu ra string ở dạng hệ 10
string QInt::getTypeDec()
{
	//Lấy dữ liệu ra
	string bin = this->toStringBits();
	if (bin == "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")
		return "-170141183460469231731687303715884105728";
	string dec = "0";
	bool negative = false;

	if (bin[0] == '1')
	{
		negative = true;

		//số âm thì lấy dấu trừ và dùng số đối của nó
		QInt temp;
		temp.importToBitsString(bin);
		temp = temp.soDoi();
		bin = temp.toStringBits();
		bin.erase(bin.begin());
	}
	else
		bin.erase(bin.begin());
	for (int i = 0; i < bin.size(); i++)
	{
		if (bin[i] == '1')
			dec = sum(dec, power(2, bin.size() - 1 - i));
	}

	if (negative)
	{
		dec.insert(dec.begin(), '-');
	}

	return dec;
}

//Xuất dữ liệu ra string ở dạng hệ 16
string QInt::getTypeHex()
{
	string s = this->toStringBits();
	string temp; //lưu chuỗi 16
	for (int i = 0; i < s.size(); i += 4)
	{
		string t = s.substr(i, 4);
		if (t == "0000") temp += "0";
		else if (t == "0001") temp += "1";
		else if (t == "0010") temp += "2";
		else if (t == "0011") temp += "3";
		else if (t == "0100") temp += "4";
		else if (t == "0101") temp += "5";
		else if (t == "0110") temp += "6";
		else if (t == "0111") temp += "7";
		else if (t == "1000") temp += "8";
		else if (t == "1001") temp += "9";
		else if (t == "1010") temp += "A";
		else if (t == "1011") temp += "B";
		else if (t == "1100") temp += "C";
		else if (t == "1101") temp += "D";
		else if (t == "1110") temp += "E";
		else if (t == "1111") temp += "F";
	}
	return temp;
}

