#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class QInt
{
	vector <unsigned int> arrayBits;

public:

	QInt();
	QInt(const QInt& n);
	QInt(const string& str);
	~QInt();
	vector<unsigned int> getData()const;
	void setStr2QInt(string Input);

	//cac phep toan
	QInt twoComplement(QInt);
	unsigned int getMSB();
	unsigned int getLSB();
	QInt modifyMSB(unsigned int);
	QInt modifyLSB(unsigned int);
	friend ostream& operator << (ostream& Output, QInt&);
	QInt& operator = (const QInt&);
	//Cau d
	QInt operator +(const QInt&);
	QInt operator -(const QInt&);
	QInt operator *(const QInt&);
	QInt operator /(const QInt&);
	//Cau e
	QInt rArithmeticShift();
	QInt lLogicalShift();
	QInt operator &(const QInt&);
	QInt operator |(const QInt&);
	QInt operator ^(const QInt&);
	QInt operator ~();
	//Cau f
	QInt operator <<(int n);
	QInt operator >>(int n);
	//Cau e
	QInt rotateLeft();
	QInt rotateRight();	
};

void rShift(QInt& A, QInt& Q, unsigned int& Q_0, unsigned int& Q_minus1);