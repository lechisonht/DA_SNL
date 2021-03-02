#include <iostream>
#include <fstream>

#include "QInt.h"

using namespace std;

//Hàm đọc file
vector<string> readFile(string path);

//Hàm xử lý tính toán cho từng dòng và trả về string kết quả
string calculatorOneLine(string line);

//Hàm xử lý tính toán toàn bộ dữ liệu đọc được trả về vector string kết quả
vector<string> calculatorAllFile(vector<string> data);

//Hàm ghi kết quả tính toán ra file
bool writeFile(vector<string> data, string path);

int main(int argc, char* argv[])
{
	if (argc != 3)
		return -1;
	string pathIn = argv[1];
	string pathOut = argv[2];

	vector<string> data = readFile(pathIn);
	if (data.size() == 0)
	{
		cout << "Error read file input." << endl;
		return 0;
	}
	data = calculatorAllFile(data);

	if (!writeFile(data, pathOut))
	{
		cout << "Error write file output." << endl;
		return -1;
	}
	else
		cout << "Finish!!" << endl;

	return 0;
}

//Hàm đọc file
vector<string> readFile(string path)
{
	fstream in;
	in.open(path, ios::in);
	if (in.fail())
		return vector<string>();

	vector<string> file;

	while (!in.eof())
	{
		string line;
		getline(in, line);
		if (line.size() != 0)
		{
			while (line[line.size() - 1] == ' ')
				line.pop_back();
		}
		if (line.size() > 0)
			file.push_back(line);
	}

	in.close();
	return file;
}

//Hàm xử lý tính toán cho từng dòng và trả về string kết quả
string calculatorOneLine(string line)
{
	vector<string> data;
	string temp;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ')
			temp.push_back(line[i]);
		else
		{
			data.push_back(temp);
			temp.clear();
		}
		if (i == line.size() - 1)
			data.push_back(temp);
	}
	
	if (data.size() == 3)
	{
		QInt number;
		string tp1 = data[0];
		string tp2 = data[1];
		string num = data[2];

		if (tp1 == "10")
			number.setTypeDec(num);
		else if (tp1 == "2")
			number.setTypeBin(num);
		else if (tp1 == "16")
			number.setTypeHex(num);

		if (tp2 == "10")
		{
			string tam = number.getTypeDec();
			while (tam[0] == '0' && tam.size() > 1)
			{
				tam.erase(tam.begin());
			}
			return tam;
		}
		else if (tp2 == "2")
		{
			string tam = number.getTypeBin();
			while (tam[0] == '0' && tam.size() > 1)
			{
				tam.erase(tam.begin());
			}
			return tam;
		}
		else if (tp2 == "16")
		{
			string tam = number.getTypeHex();
			while (tam[0] == '0' && tam.size() > 1)
			{
				tam.erase(tam.begin());
			}
			return tam;
		}
		else if (tp2 == "rol" || tp2 == "ROL")
		{
			number = number.rol();
			if (tp1 == "10")
			{
				string tam = number.getTypeDec();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
			else if (tp1 == "2")
			{
				string tam = number.getTypeBin();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
			else if (tp1 == "16")
			{
				string tam = number.getTypeHex();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
		}
		else if (tp2 == "ror" || tp2 == "ROR")
		{
			number = number.ror();
			if (tp1 == "10")
			{
				string tam = number.getTypeDec();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
			else if (tp1 == "2")
			{
				string tam = number.getTypeBin();
				while (tam[0] == '0')
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
			else if (tp1 == "16")
			{
				string tam = number.getTypeHex();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
		}
		else if (tp2 == "~")
		{
			number = ~number;
			if (tp1 == "10")
			{
				string tam = number.getTypeDec();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
			else if (tp1 == "2")
			{
				string tam = number.getTypeBin();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
			else if (tp1 == "16")
			{
				string tam = number.getTypeHex();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
		}
	}
	else
	{
		if (data.size() == 4)
		{
			QInt a;
			QInt b;
			QInt kq;

			string tp1 = data[0];
			string num1 = data[1];
			string tp2 = data[2];
			string num2 = data[3];

			//nạp dữ liệu vào QInt
			if (tp1 == "10")
			{
				a.setTypeDec(num1);
				if (tp2 != ">>" && tp2 != "<<")
					b.setTypeDec(num2);
			}
			else if (tp1 == "2")
			{
				a.setTypeBin(num1);
				if (tp2 != ">>" && tp2 != "<<")
					b.setTypeBin(num2);
			}
			else if (tp1 == "16")
			{
				a.setTypeHex(num1);
				if (tp2 != ">>" && tp2 != "<<")
					b.setTypeHex(num2);
			}

			//Thực hiện phép tính
			if (tp2 == "+")
			{
				kq = a + b;
			}
			else if (tp2 == "-")
			{
				kq = a - b;
			}
			else if (tp2 == "*")
			{
				kq = a * b;
			}
			else if (tp2 == "/")
			{
				if (b.getTypeDec() == "0")
					return "Math ERROR";

				kq = a / b;
			}
			else if (tp2 == "&")
			{
				kq = a & b;
			}
			else if (tp2 == "|")
			{
				kq = a | b;
			}
			else if (tp2 == "^")
			{
				kq = a ^ b;
			}
			else if (tp2 == ">>")
			{
				int k = stringDecToInt(num2);
				kq = a >> k;
			}
			else if (tp2 == "<<")
			{
				int k = stringDecToInt(num2);
				kq = a << k;
			}
			else return "null";

			//return ket qua
			if (tp1 == "10")
			{
				string tam = kq.getTypeDec();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
			else if (tp1 == "2")
			{
				string tam = kq.getTypeBin();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
			else if (tp1 == "16")
			{
				string tam = kq.getTypeHex();
				while (tam[0] == '0' && tam.size() > 1)
				{
					tam.erase(tam.begin());
				}
				return tam;
			}
		}
	}
	return "null";
}

//Hàm xử lý tính toán toàn bộ dữ liệu đọc được trả về vector string kết quả
vector<string> calculatorAllFile(vector<string> data)
{
	vector<string> kq;
	for (int i = 0; i < data.size(); i++)
	{
		kq.push_back(calculatorOneLine(data[i]));
	}
	return kq;
}

//Hàm ghi kết quả tính toán ra file
bool writeFile(vector<string> data, string path)
{
	ofstream out;
	out.open(path);
	if (out.fail())
		return false;

	for (int i = 0; i < data.size() - 1; i++)
	{
		out << data[i] << endl;
	}
	out << data[data.size() - 1];
	out.close();
	return true;
}