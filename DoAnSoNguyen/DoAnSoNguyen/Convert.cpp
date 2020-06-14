#include "Convert.h"


Convert* Convert::obj = NULL;

Convert::Convert()
{
}

Convert::~Convert()
{
	if (this->obj)
		delete this->obj;
}

Convert* Convert::getObj()
{
	if (obj == NULL)
	{
		obj = new Convert;
	}
	return obj;
}

string Convert::Div2(string SrcStr)
{
	string res;
	int temp = 0;
	for (int i = 0; i < SrcStr.size(); i++)
	{
		temp = 10 * temp + (SrcStr[i] - '0');
		if ((i == 0 && temp >= 2) || i > 0) // phần tử đầu chuỗi phải lớn hơn 2 mới thực hiện thêm vào chuỗi kết quả
		{
			res.push_back(temp / 2 + '0');
		}
		temp = temp % 2;
	}
	return res;
}

string Convert::AddString(string StrA, string StrB)
{
	bool IsNegative = false; // Lưu giá trị âm hay dương của kết quả
	int temp = 0; // biến nhớ trong phép cộng
	if (StrA[0] == '-' && StrB[0] != '-') // Nếu chuỗi a âm và b dương thì lấy b trừ a
	{
		SubString(StrB, StrA);
	}
	else if (StrB[0] == '-' && StrA[0] != '-') // Nếu chuỗi b âm và a dương thì lấy a trừ b
	{
		SubString(StrA, StrB);
	}
	else // nếu 2 chuỗi cùng dấu
	{
		if (StrA[0] == '-' && StrB[0] == '-') // nếu cùng dấu âm thì chuyển về dương rồi cộng và thêm dấu âm vào kết quả cuối
		{
			IsNegative = true;
			StrA.erase(StrA.begin());
			StrB.erase(StrB.begin());
		}
		while (StrA.size() != StrB.size()) // nếu kích thước chuỗi a, b khác nhau  thì thêm các số 0 vào đầu chuỗi cho bằng nhau
		{
			if (StrA.size() > StrB.size())
			{
				StrB.insert(StrB.begin(), '0');
			}
			else StrA.insert(StrA.begin(), '0');
		}
		for (int i = StrA.size() - 1; i >= 0; i--) // 
		{
			temp = temp + (StrA[i] - '0') + (StrB[i] - '0'); // thao tác - '0' 
			StrA[i] = temp % 10 + '0';
			temp = temp / 10;
		}
		if (temp != 0) // Nếu vẫn còn biến nhớ
		{
			StrA.insert(StrA.begin(), temp + '0');
			temp = 0;
		}
		while (StrA[0] == '0') // Xóa các số 0 thừa
		{
			StrA.erase(StrA.begin());
		}
		if (IsNegative == true) // Trả kết quả về số âm
		{
			StrA.insert(StrA.begin(), '-');
		}
	}
	return StrA;
}

string Convert::SubString(string strA, string StrB)
{
	int temp = 0;
	bool IsNegative = false;
	while (strA.size() != StrB.size()) // Nếu kích thước 2 chuỗi khác nhau thì chuyển về bằng nhau
	{
		if (strA.size() > StrB.size())
		{
			StrB.insert(StrB.begin(), '0');
		}
		else
		{
			strA.insert(strA.begin(), '0');
		}
	}
	if (strA < StrB) //nếu chuỗi b lớn hơn thì hoán vị a và b, biến dấu trở lưu giá trị âm
	{
		string str = strA;
		strA = StrB;
		StrB = str;
		IsNegative = true;
	}
	for (int i = strA.size() - 1; i >= 0; i--)
	{
		if ((strA[i] - temp) > StrB[i])
		{
			strA[i] = strA[i] - temp - (StrB[i] - '0');
			temp = 0;
		}
		else
		{
			strA[i] = (10 + strA[i] - temp) - (StrB[i] - '0');
			temp = 1;
		}
	}
	while (strA[0] == '0') // Xóa các số 0 thừa ở đầu chuỗi a
	{
		strA.erase(strA.begin());
	}
	if (IsNegative) //Trả về giá trị âm/ dương thực sự
	{
		strA.insert(strA.begin(), '-');
	}
	return strA;
}

string Convert::MulString(string strA, string StrB)
{
	int temp = 0;
	bool IsNegative = false;
	//Xóa dấu âm nếu tìm thấy dấu âm và đặt biến dấu là âm nếu dấu của 2 số khác nhau
	if (strA[0] == '-')
	{
		strA.erase(strA.begin());
		if (StrB[0] != '-')
			IsNegative = true;
	}
	if (StrB[0] == '-')
	{
		StrB.erase(StrB.begin());
		if (strA[0] != '-')
			IsNegative = true;
	}


	int a = strA.size();
	int b = StrB.size();
	string Str, Res = "0";
	for (int i = b - 1; i >= 0; i--)
	{
		for (int j = a - 1; j >= 0; j--)
		{
			temp = temp + ((strA[j] - '0') * (StrB[b - 1 - i] - '0'));
			Str.push_back(temp % 10 + '0');
			temp = temp / 10;
		}
		if (temp != 0)
		{
			Str.push_back(temp + '0');
		}
		reverse(Str.begin(), Str.end()); //Đảo chuỗi
		for (int j = 0; j < i; j++)
		{
			Str.push_back('0');
		}
		Res = AddString(Res, Str);
		Str.clear(); // làm mới chuỗi tạm
	}
	if (IsNegative)
	{
		Res.insert(Res.begin(), '-');
	}
	return Res;
}

string Convert::Power(int x, int n)
{
	string Result;

	if (x > -1)
	{
		//Nếu a > 1
		if (x > 1)
		{
			int Pow = n;

			if (n > (32 - 1) * 2 / x) //Độ dài của kiểu unsigned int là 32, Tránh trường hợp tràn số.
			{
				Pow = (32 - 1) * 2 / x;
			}

			Result = to_string((unsigned int)pow(x, Pow));


			//Phần có khả năng bị tràn số sẽ được nhân theo nhân chuỗi.
			for (int i = Pow + 1; i <= n; i++)
			{
				Result = MulString(Result, to_string(x));
			}
		}
		else
		{
			Result.push_back(x + '0');
		}
	}
	return Result;
}

QInt Convert::TwoComplement(QInt Q)
{
	return (~Q + QInt("1"));
}

string Convert::StrDectoBin(string strDec)
{
	string Res;
	bool IsNegative = false;
	if (strDec[0] == '-') //Nếu số âm thì xóa dấu âm và lưu biến dấu bằng âm
	{
		strDec.erase(strDec.begin());
		IsNegative = true;
	}
	while (strDec != "") //chia 2 liên tục đến khi chuỗi bằng rỗng
	{
		/* code */
		Res.push_back(((strDec[strDec.size() - 1] - '0') % 2) + '0');
		strDec = Div2(strDec);
	}
	reverse(Res.begin(), Res.end());
	if (IsNegative == true) //Nếu là số âm thì lấy bù 2
	{
		QInt Q(Res);
		Q = TwoComplement(Q);
		Res = QInttoBinStr(Q);
	}
	return Res;
}


QInt Convert::StrDectoQInt(string Dec)
{
	string Bin = StrDectoBin(Dec);
	return QInt(Bin);
}




QInt Convert::StrHextoQInt(string Hex)
{
	string Bin = StrHextoBin(Hex);
	return QInt(Bin);
}

string Convert::StrHextoBin(string strHex)
{
	string Bin;
	int i = 0;
	string add;
	if (strHex.size() <= 32)
	{
		while (i < strHex.size())
		{
			switch (strHex[i])
			{
			case '0':
				add = "0000";
				break;
			case '1':
				add = "0001";
				break;
			case '2':
				add = "0010";
				break;
			case '3':
				add = "0011";
				break;
			case '4':
				add = "0100";
				break;
			case '5':
				add = "0101";
				break;
			case '6':
				add = "0110";
				break;
			case '7':
				add = "0111";
				break;
			case '8':
				add = "1000";
				break;
			case '9':
				add = "1001";
				break;
			case 'A':
				add = "1010";
				break;
			case 'B':
				add = "1011";
				break;
			case 'C':
				add = "1100";
				break;
			case 'D':
				add = "1101";
				break;
			case 'E':
				add = "1110";
				break;
			case 'F':
				add = "1111";
				break;
			default:
				break;
			}
			Bin = Bin + add;
			i++;
		}
		if (Bin.find('1') != string::npos)
		{
			Bin.erase(Bin.begin(), Bin.begin() + Bin.find('1'));
		}
		return Bin;
	}
	else
		return (QInttoBinStr(QInt("0")));
}

string Convert::StrBintoHex(string Str)
{
	string Temp;
	string Result;

	//Thêm các số 0 vào để đủ block 4 bit.
	while (Str.size() % 4 != 0)
	{
		Str.insert(Str.begin(), '0');
	}

	for (int i = 0; i < Str.size(); i++)
	{
		Temp.push_back(Str[i]);
		if (i % 4 == 3)
		{
			if (Temp == "0000") Result.push_back('0');
			else if (Temp == "0001") Result.push_back('1');
			else if (Temp == "0010") Result.push_back('2');
			else if (Temp == "0011") Result.push_back('3');
			else if (Temp == "0100") Result.push_back('4');
			else if (Temp == "0101") Result.push_back('5');
			else if (Temp == "0110") Result.push_back('6');
			else if (Temp == "0111") Result.push_back('7');
			else if (Temp == "1000") Result.push_back('8');
			else if (Temp == "1001") Result.push_back('9');
			else if (Temp == "1010") Result.push_back('A');
			else if (Temp == "1011") Result.push_back('B');
			else if (Temp == "1100") Result.push_back('C');
			else if (Temp == "1101") Result.push_back('D');
			else if (Temp == "1110") Result.push_back('E');
			else if (Temp == "1111") Result.push_back('F');
			Temp.clear();
		}	
	}
	return Result;
}

string Convert::QInttoBinStr(const QInt& Q)
{
	vector<unsigned int> data = Q.getData();
	string BinStr;

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 31; j >= 0; j--)
		{
			BinStr.push_back(((data[i] & (1 << j)) >> j) + '0');
		}
	}
	//xóa những bit 0 thừa phía trước.
	if (BinStr.find('1') != string::npos)
	{
		BinStr.erase(BinStr.begin(), BinStr.begin() + BinStr.find('1'));
	}
	else
	{
		BinStr.resize(1);
	}

	return BinStr;
}

string Convert::QInttoDecStr(const QInt& Q)
{
	string Binary = QInttoBinStr(Q);
	string Decimal = "0";
	for (int i = 0; i < Binary.size(); i++)
	{
		if (Binary[i] != '0')
		{
			if (Binary.size() - i < 128)
			{
				Decimal = AddString(Decimal, Power(2, Binary.size() - i - 1));
			}
			else
			{
				Decimal = SubString(Decimal, Power(2, Binary.size() - i - 1));
			}
		}
	}
	return Decimal;
}