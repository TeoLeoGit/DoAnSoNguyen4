#include <fstream>
#include "Convert.h"

int main(int argc, char* argv[])
{
	int counter;
	//chỉ có file exe
	if (argc == 1)
		cout << "\nNo Extra Command Line Argument Passed Other Than Program Name";
	//chỉ có 2 file
	if (argc == 2)
		cout << "\nOnly exercute file and input file/output file";
	//có file exe, input, output
	if (argc == 3)
	{
		cout << "\nNumber Of Arguments Passed: %d" << argc;
		cout << "\n----Following Are The Command Line Arguments Passed----" << endl;
		for (counter = 0;counter < argc;counter++)
			cout << "argument[" << counter << "]:   " << argv[counter];
		//phần đọc input file và ghi output file, argv[1] = input.txt, argv[2] = output.txt

		fstream InputFile(argv[1], ios::in);
		ofstream OutputFile(argv[2], ios::out);
		if (!InputFile)
		{
			cout << "Khong tim thay file Input." << endl;
			return 0;
		}
		if (!OutputFile)
		{
			cout << "Khong mo duoc file Output." << endl;
			return 0;
		}
		
		//Xử lý dữ liệu
		string InputBase, Str1, Str2, Result;
		char Ch;
		while(getline(InputFile, InputBase, ' '))
		{
			getline(InputFile, Str1, ' ');
			getline(InputFile, Str2, '\n');
			size_t pos = Str2.find(" ");
			string OperateTask = Str2.substr(0, pos);//tìm kiếm toán hoạng trong string Str2
			//xét phần tử getline được ở lần getline thứ 3 trước để giải quyết trg hợp là phép toán thường
			if (OperateTask == "+")
			{
				QInt BinResult(Str1);
				string Str3 = Str2.substr(pos + 1);//số hạng phía sau toán hạng
				QInt Numb2;
				if (InputBase == "10")
				{
					BinResult = Convert::StrDectoQInt(Str1);
					Numb2 = Convert::StrDectoQInt(Str3);
					BinResult = BinResult + Numb2;
					Result = Convert::QInttoDecStr(BinResult);
				}
				else
					if (InputBase == "16")
					{
						BinResult = Convert::StrHextoQInt(Str1);
						Numb2 = Convert::StrHextoQInt(Str3);
						BinResult = BinResult + Numb2;
						Result = Convert::QInttoBinStr(BinResult);
						Result = Convert::StrBintoHex(Result);
					}
				goto finishedStr1;
			}
			if (OperateTask == "-")
			{
				QInt BinResult(Str1);
				string Str3 = Str2.substr(pos + 1);
				QInt Numb2;
				if (InputBase == "10")
				{
					BinResult = Convert::StrDectoQInt(Str1);
					Numb2 = Convert::StrDectoQInt(Str3);
					BinResult = BinResult - Numb2;
					Result = Convert::QInttoDecStr(BinResult);
				}
				else
					if (InputBase == "16")
					{
						BinResult = Convert::StrHextoQInt(Str1);
						Numb2 = Convert::StrHextoQInt(Str3);
						BinResult = BinResult - Numb2;
						Result = Convert::QInttoBinStr(BinResult);
						Result = Convert::StrBintoHex(Result);
					}
				goto finishedStr1;
			}
			if (OperateTask == "*")
			{
				QInt BinResult(Str1);
				string Str3 = Str2.substr(pos + 1);
				QInt Numb2;
				if (InputBase == "10")
				{
					BinResult = Convert::StrDectoQInt(Str1);
					Numb2 = Convert::StrDectoQInt(Str3);
					BinResult = BinResult * Numb2;
					Result = Convert::QInttoDecStr(BinResult);
				}
				else
					if (InputBase == "16")
					{
						BinResult = Convert::StrHextoQInt(Str1);
						Numb2 = Convert::StrHextoQInt(Str3);
						BinResult = BinResult * Numb2;
						Result = Convert::QInttoBinStr(BinResult);
						Result = Convert::StrBintoHex(Result);
					}
				goto finishedStr1;
			}
			if (OperateTask == "/")
			{
				QInt BinResult(Str1);
				string Str3 = Str2.substr(pos + 1);
				QInt Numb2;
				if (InputBase == "10")
				{
					BinResult = Convert::StrDectoQInt(Str1);
					Numb2 = Convert::StrDectoQInt(Str3);
					BinResult = BinResult / Numb2;
					Result = Convert::QInttoDecStr(BinResult);
				}
				else
					if (InputBase == "16")
					{
						BinResult = Convert::StrHextoQInt(Str1);
						Numb2 = Convert::StrHextoQInt(Str3);
						BinResult = BinResult / Numb2;
						Result = Convert::QInttoBinStr(BinResult);
						Result = Convert::StrBintoHex(Result);
					}
				goto finishedStr1;
			}
			if (OperateTask == "^")
			{
				QInt BinResult(Str1);
				string Str3 = Str2.substr(pos + 1);
				QInt Numb2;
				if (InputBase == "10")
				{
					BinResult = Convert::StrDectoQInt(Str1);
					Numb2 = Convert::StrDectoQInt(Str3);
					BinResult = BinResult ^ Numb2;
					Result = Convert::QInttoDecStr(BinResult);
				}
				else
					if (InputBase == "16")
					{
						BinResult = Convert::StrHextoQInt(Str1);
						Numb2 = Convert::StrHextoQInt(Str3);
						BinResult = BinResult ^ Numb2;
						Result = Convert::QInttoBinStr(BinResult);
						Result = Convert::StrBintoHex(Result);
					}
				goto finishedStr1;
			}
			if (OperateTask == "|")
			{
				QInt BinResult(Str1);
				string Str3 = Str2.substr(pos + 1);
				QInt Numb2;
				if (InputBase == "10")
				{
					BinResult = Convert::StrDectoQInt(Str1);
					Numb2 = Convert::StrDectoQInt(Str3);
					BinResult = BinResult | Numb2;
					Result = Convert::QInttoDecStr(BinResult);
				}
				else
					if (InputBase == "16")
					{
						BinResult = Convert::StrHextoQInt(Str1);
						Numb2 = Convert::StrHextoQInt(Str3);
						BinResult = BinResult | Numb2;
						Result = Convert::QInttoBinStr(BinResult);
						Result = Convert::StrBintoHex(Result);
					}
				goto finishedStr1;
			}
			if (OperateTask == "&")
			{
				QInt BinResult(Str1);
				string Str3 = Str2.substr(pos + 1);
				QInt Numb2;
				if (InputBase == "10")
				{
					BinResult = Convert::StrDectoQInt(Str1);
					Numb2 = Convert::StrDectoQInt(Str3);
					BinResult = BinResult & Numb2;
					Result = Convert::QInttoDecStr(BinResult);
				}
				else
					if (InputBase == "16")
					{
						BinResult = Convert::StrHextoQInt(Str1);
						Numb2 = Convert::StrHextoQInt(Str3);
						BinResult = BinResult & Numb2;
						Result = Convert::QInttoBinStr(BinResult);
						Result = Convert::StrBintoHex(Result);
					}
				goto finishedStr1;
			}
			if (OperateTask == ">>")
			{
				QInt BinResult(Str1);
				string Str3 = Str2.substr(pos + 1);
				int Numb2 = 0;
				if (InputBase == "10")
				{
					BinResult = Convert::StrDectoQInt(Str1);
					Numb2 = stoi(Str3);
					BinResult = BinResult >> Numb2;
					Result = Convert::QInttoDecStr(BinResult);
				}
				else
					if (InputBase == "16")
					{
						BinResult = Convert::StrHextoQInt(Str1);
						Numb2 = stoi(Str3);
						BinResult = BinResult >> Numb2;
						Result = Convert::QInttoBinStr(BinResult);
						Result = Convert::StrBintoHex(Result);
					}
					else
					{
						Numb2 = stoi(Str3);
						BinResult = BinResult >> Numb2;
						Result = Convert::QInttoBinStr(BinResult);
					}
				goto finishedStr1;
			}
			if (OperateTask == "<<")
			{
				QInt BinResult(Str1);
				string Str3 = Str2.substr(pos + 1);
				int Numb2 = 0;
				if (InputBase == "10")
				{
					BinResult = Convert::StrDectoQInt(Str1);
					Numb2 = stoi(Str3);
					BinResult = BinResult << Numb2;
					Result = Convert::QInttoDecStr(BinResult);
				}
				else
					if (InputBase == "16")
					{
						BinResult = Convert::StrHextoQInt(Str1);
						Numb2 = stoi(Str3);
						BinResult = BinResult << Numb2;
						Result = Convert::QInttoBinStr(BinResult);
						Result = Convert::StrBintoHex(Result);
					}
					else
					{
						Numb2 = stoi(Str3);
						BinResult = BinResult << Numb2;
						Result = Convert::QInttoBinStr(BinResult);
					}
				goto finishedStr1;
			}

			//Xét getline ở lần getline thứ 2
			if (Str1 == "16")
			{
				if (InputBase == "16")
					Result = Str2;
				else
				{
					if (InputBase == "10")
					{
						string BinStr = Convert::StrDectoBin(Str2);
						Result = Convert::StrBintoHex(BinStr);
					}
					else
						Result = Convert::StrBintoHex(Str2);
				}
				
				goto finishedStr1;
			}
			if (Str1 == "10")
			{
				if (InputBase == "10")
					Result = Str2;
				else
				{
					if (InputBase == "16")
					{
						QInt BinBase = Convert::StrHextoQInt(Str2);
						Result = Convert::QInttoDecStr(BinBase);
					}
					else
					{
						QInt BinBase(Str2);
						Result = Convert::QInttoDecStr(BinBase);
					}
				}
				goto finishedStr1;
			}
			if (Str1 == "2")
			{
				if (InputBase == "2")
				{
					QInt BinBase(Str2);
					Result = Convert::QInttoBinStr(BinBase); //trong file input có th dư số 0 ở bên trái nên chép lại sai
				}
				else
				{
					if (InputBase == "16")
					{
						Result = Convert::StrHextoBin(Str2);
					}
					else
					{
						Result = Convert::StrDectoBin(Str2);
					}
				}
				goto finishedStr1;
			}
			if (Str1 == "rol")
			{
				if (InputBase == "2")
				{
					QInt Task(Str2);
					Task = Task.rotateLeft();
					Result = Convert::QInttoBinStr(Task);
				}
				else
					if (InputBase == "10")
					{
						QInt Task = Convert::StrDectoQInt(Str2);
						Task = Task.rotateLeft();
						Result = Convert::QInttoDecStr(Task);
					}
					else
					{
						QInt Task = Convert::StrHextoQInt(Str2);
						Task = Task.rotateLeft();
						Result = Convert::QInttoBinStr(Task);
						Result = Convert::StrBintoHex(Result);
					}
				goto finishedStr1;
			}
			if (Str1 == "ror")
			{
				if (InputBase == "2")
				{
					QInt Task(Str2);
					Task = Task.rotateRight();
					Result = Convert::QInttoBinStr(Task);
				}
				else
					if (InputBase == "10")
					{
						QInt Task = Convert::StrDectoQInt(Str2);
						Task = Task.rotateRight();
						Result = Convert::QInttoDecStr(Task);
					}
					else
					{
						QInt Task = Convert::StrHextoQInt(Str2);
						Task = Task.rotateRight();
						Result = Convert::QInttoBinStr(Task);
						Result = Convert::StrBintoHex(Result);
					}
				goto finishedStr1;
			}
			if (Str1 == "~")
			{
				if (InputBase == "2")
				{
					QInt Task(Str2);
					Task = ~Task;
					Result = Convert::QInttoBinStr(Task);
				}
				else
					if (InputBase == "10")
					{
						QInt Task = Convert::StrDectoQInt(Str2);
						Task = ~Task;
						Result = Convert::QInttoDecStr(Task);
					}
					else
					{
						QInt Task = Convert::StrHextoQInt(Str2);
						Task = ~Task;
						Result = Convert::QInttoBinStr(Task);
						Result = Convert::StrBintoHex(Result);
					}
				goto finishedStr1;
			}

		finishedStr1: //trả kết quả vào file output
			OutputFile << Result << endl;
		}
		InputFile.close();
		OutputFile.close();
	}
	system("pause");
	return 0;
}

