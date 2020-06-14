#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<math.h>
#include"QInt.h"
using namespace std;

class Convert
{
protected:
	static Convert* obj;
	Convert();
	~Convert();
public:

	static Convert* getObj();

	static string Div2(string SrcStr); //
	static string AddString(string StrA, string StrB);
	static string SubString(string strA, string StrB);
	static string MulString(string strA, string StrB);
	static string Power(int x, int n);

	static QInt StrDectoQInt(string Dec);
	static QInt TwoComplement(QInt Q);
	static QInt StrHextoQInt(string Hex);


	static string StrDectoBin(string strDec);
	static string StrHextoBin(string strHex);
	static string StrBintoHex(string strBin);
	static string QInttoBinStr(const QInt& Q);
	static string QInttoDecStr(const QInt& Q);

};

