#include "QInt.h"


QInt::QInt()
{
	arrayBits.resize(4);
	for (int i = 0; i < 4; i++)
	{
		this->arrayBits[i] = 0;
	}
}

QInt::QInt(const QInt& n)
{
	arrayBits.resize(4);
	for (int i = 0; i < 4; i++)
	{
		this->arrayBits[i] = n.arrayBits[i];
	}
}

QInt::QInt(const string& str)
{
	arrayBits.resize(4);
	for (int i = 0; i < str.size();i++)
	{
		if (str[i] == '1')
		{
			this->arrayBits[3 - (str.size() - 1 - i) / 32] =
				this->arrayBits[3 - (str.size() - 1 - i) / 32] | (1 << (((str.size() - 1 % 32) - i % 32 + 32) % 32));
		}
	}
}

QInt::~QInt()
{

}

vector<unsigned int> QInt::getData() const
{
	return this->arrayBits;
}

//phan Cuong
//thay đổi khi có phép dịch
void rShift(QInt& A, QInt& Q, unsigned int& Q_0, unsigned int& Q_minus1)
{
	Q = Q.rArithmeticShift();
	Q = Q.modifyMSB(A.getLSB());

	A = A.rArithmeticShift();
	A = A.modifyMSB(Q_0);

	Q_minus1 = Q_0;
	Q_0 = Q.getLSB();
}

QInt QInt::twoComplement(QInt Input)
{
	QInt QInt_1;
	QInt_1.arrayBits[3] = 1;
	for (int i = 0;i < 4;i++)
		Input.arrayBits[i] = ~Input.arrayBits[i];
	Input = Input + QInt_1;
	return Input;
}

unsigned int QInt::getMSB()
{
	return (this->arrayBits[0] >> 31) & 1;
}

unsigned int QInt::getLSB()
{
	return (this->arrayBits[3] & 1);
}

QInt QInt::modifyMSB(unsigned int ModBit)
{
	this->arrayBits[0] = this->arrayBits[0] << 1;
	this->arrayBits[0] = this->arrayBits[0] >> 1;
	this->arrayBits[0] = this->arrayBits[0] ^ (ModBit << 31);
	return *this;
}

QInt QInt::modifyLSB(unsigned int ModBit)
{
	this->arrayBits[3] = this->arrayBits[3] >> 1;
	this->arrayBits[3] = this->arrayBits[3] << 1;
	this->arrayBits[3] = this->arrayBits[3] ^ ModBit;
	return *this;
}

QInt& QInt::operator=(const QInt& Other)
{
	for (int i = 3; i >= 0;i--)
		this->arrayBits[i] = Other.arrayBits[i];
	return *this;
}

QInt QInt::operator+(const QInt& Other)
{
	QInt sum;
	int carry = 0; //khởi tạo số thừa
	for (int i = 3; i >= 0;i--)
	{
		for (int j = 0;j < 32;j++) //thao tác các bit từ phải sang trái
		{
			int curBit_A = (this->arrayBits[i] >> j) & 1;
			int curBit_Other = (Other.arrayBits[i] >> j) & 1;
			//cộng trên từng bit (xử dụng phép xor) và số dư (nếu có) rồi dịch về vị trí của bit.
			sum.arrayBits[i] = sum.arrayBits[i] ^ (((curBit_A ^ curBit_Other) ^ carry) << j);
			//tạo lại số dư (kẻ bảng chân trị sẽ thấy chưa làm = pp bit được :(  )
			if (curBit_A == 1 && curBit_Other == 1)
				carry = 1;
			else
				if ((curBit_A == 1 || curBit_Other == 1) && carry == 1)
					carry = 1;
				else
					carry = 0;
		}
	}
	return sum;
}

QInt QInt::operator-(const QInt& Other)
{
	QInt diff;
	int soDu = 0;
	QInt bu2 = twoComplement(Other);
	diff = *this + bu2;
	return diff;
}

QInt QInt::operator*(const QInt& Other)
{
	//Phép nhân theo thuật toán Booth
	QInt M = *this;
	QInt Q = Other;
	unsigned int Q_minus1 = 0;
	unsigned int Q_0 = Q.getLSB();
	QInt accumulator;
	for (int i = 0;i < 128;i++)
	{
		if (Q_0 == 0 && Q_minus1 == 1)
			accumulator = accumulator + M;
		else
			if (Q_0 == 1 && Q_minus1 == 0)
				accumulator = accumulator - M;
		rShift(accumulator, Q, Q_0, Q_minus1);
	}
	return Q;
}

QInt QInt::operator/(const QInt& Divisor)
{
	//Booth's Restoring Division
	QInt A;
	QInt Q = *this;
	QInt M = Divisor;
	int Q_0;
	//chuyển về số dương để thực hiện giải thuật.
	int bitCase = 0; //0: 2 số dương, 1: 1 số âm, 2: 2 số âm
	if (Q.getMSB() == 1)
	{
		Q = twoComplement(Q);
		bitCase++;
	}
	if (M.getMSB() == 1)
	{
		M = M.twoComplement(M);
		bitCase++;
	}

	for (int i = 0; i < 128;i++)
	{
		//left shift
		A.lLogicalShift();
		A.modifyLSB(Q.getMSB());
		Q.lLogicalShift();

		A = A - M;
		if (A.getMSB() == 1) //restore
		{
			Q = Q.modifyLSB(0);
			A = A + M;
		}
		else //not restore
			Q = Q.modifyLSB(1);
	}

	if (bitCase == 1)
		Q = twoComplement(Q);
	return Q;
}

QInt QInt::operator&(const QInt& Other)
{
	QInt result;
	for (int i = 3; i >= 0;i--)
		result.arrayBits[i] = this->arrayBits[i] & Other.arrayBits[i];
	return result;
}

QInt QInt::operator|(const QInt& Other)
{

	QInt result;
	for (int i = 3; i >= 0;i--)
		result.arrayBits[i] = this->arrayBits[i] | Other.arrayBits[i];
	return result;
}

QInt QInt::operator^(const QInt& Other)
{
	QInt result;
	for (int i = 3; i >= 0;i--)
		result.arrayBits[i] = this->arrayBits[i] ^ Other.arrayBits[i];
	return result;
}

QInt QInt::operator~()
{
	for (int i = 3; i >= 0;i--)
		this->arrayBits[i] = ~this->arrayBits[i];
	return *this;
}

QInt QInt::operator<<(int n)
{
	if (n < 0)
	{
		QInt zero;
		return zero;
	}
	if (n % 128 == 0)
	{
		return *this;
	}
	if (n > 128)
		n = n - (n / 128) * 128;
	if (n < 32)
	{
		unsigned int carryFlags = this->arrayBits[3] >> (32 - n);
		for (int i = 3;i >= 0; i--)
		{
			unsigned int resBits = this->arrayBits[i] >> (32 - n);
			this->arrayBits[i] = this->arrayBits[i] << n;
			if (i < 3)
			{
				this->arrayBits[i] = this->arrayBits[i] | carryFlags;
				carryFlags = resBits;
			}
		}
	}
	else
	{
		if (n == 32)
		{
			for (int i = 0; i < 3;i++)
				this->arrayBits[i] = this->arrayBits[i + 1];
			this->arrayBits[3] = 0;
		}
		else
		{
			QInt shiftedInt;
			int offBitsArrCount = n / 32;
			//dịch n bit thì có 128 - n bit cần giữ từ phải -> trái
			int leftBits = 128 - n;
			int j = 3;
			for (int i = 3 - offBitsArrCount; i >= 0; i--) //xét từ mảng còn bit dịch qua đến mảng 0.
			{
				if (leftBits > 32)
				{
					unsigned int resBits = this->arrayBits[j];
					leftBits = leftBits - 32;

					unsigned int unsavedBits = resBits >> (32 - (n % 32)); //lưu bit tràn qua mảng tiếp đó nữa (vì dịch hơn 32 bit).
					shiftedInt.arrayBits[i] = shiftedInt.arrayBits[i] | (resBits << (n % 32));
					if (i > 0) //lưu bit tràn vào mảng sau đó
						shiftedInt.arrayBits[i - 1] = unsavedBits;
				}
				else
				{
					unsigned int resBits;
					resBits = this->arrayBits[j] << (32 - leftBits); //tắt các bit không lưu
					shiftedInt.arrayBits[i] = shiftedInt.arrayBits[i] | resBits;
				}
				j--;
			}
			*this = shiftedInt;
		}
	}
	return *this;
}

QInt QInt::operator>>(int n)
{
	if (n < 0)
	{
		QInt zero;
		return zero;
	}
	if (n % 128 == 0)
	{
		return *this;
	}
	if (n > 128)
		n = n - (n / 128) * 128;
	if (n < 32)
	{
		unsigned int carryFlags = this->arrayBits[0] << (32 - n);
		for (int i = 0;i < 4; i++)
		{
			unsigned int resBits = this->arrayBits[i] << (32 - n);
			this->arrayBits[i] = this->arrayBits[i] >> n;
			if (i > 0)
			{
				this->arrayBits[i] = this->arrayBits[i] | carryFlags;
				carryFlags = resBits;
			}
		}
	}
	else
	{
		if (n == 32)
		{
			for (int i = 3; i > 0;i--)
				this->arrayBits[i] = this->arrayBits[i - 1];
			this->arrayBits[0] = 0;
		}
		else
		{
			if (n >= 128)
			{
				QInt zero;
				*this = zero;
			}
			else
			{
				QInt shiftedInt;
				int offBitsArrCount = n / 32;
				int leftBits = 128 - n;
				int j = 0;
				for (int i = offBitsArrCount; i < 4; i++) //xét từ mảng còn bit dịch qua đến mảng 3.
				{
					if (leftBits > 32)
					{
						unsigned int resBits = this->arrayBits[j];
						leftBits = leftBits - 32;
						unsigned int unsavedBits = resBits << (32 - (n % 32));
						shiftedInt.arrayBits[i] = shiftedInt.arrayBits[i] | (resBits >> (n % 32));
						if (i < 3) //lưu bit tràn vào mảng sau đó
							shiftedInt.arrayBits[i + 1] = unsavedBits;
					}
					else
					{
						unsigned int resBits;
						resBits = this->arrayBits[j] >> (32 - leftBits);
						shiftedInt.arrayBits[i] = shiftedInt.arrayBits[i] | resBits;
					}
					j++;
				}
				*this = shiftedInt;
			}
		}
	}
	return *this;
}

QInt QInt::rotateLeft()
{
	unsigned int carryFlag = this->arrayBits[0] >> 31;
	*this = *this << 1;
	this->arrayBits[3] = this->arrayBits[3] | carryFlag;
	return *this;
}

QInt QInt::rotateRight()
{
	unsigned int carryFlag = this->arrayBits[3] & 1;
	*this = *this >> 1;
	this->arrayBits[0] = this->arrayBits[0] ^ (carryFlag << 31);
	return *this;
}

void QInt::setStr2QInt(string str)
{
	for (int i = 0; i < str.size();i++)
	{
		if (str[i] == '1')
		{
			this->arrayBits[3 - (str.size() - 1 - i) / 32] =
				this->arrayBits[3 - (str.size() - 1 - i) / 32] | (1 << (((str.size() - 1 % 32) - i % 32 + 32) % 32));
		}
	}
}

QInt QInt::rArithmeticShift()
{
	int carryFlag = this->arrayBits[0] & 1;
	int signBit = this->arrayBits[0] >> 31;
	this->arrayBits[0] = this->arrayBits[0] >> 1;
	this->arrayBits[0] = this->arrayBits[0] ^ (signBit << 31);
	for (int i = 1; i < 4;i++)
	{
		int resBit = this->arrayBits[i] & 1;
		this->arrayBits[i] = this->arrayBits[i] >> 1;
		//lưu lại bit mất vào mảng sau
		this->arrayBits[i] = this->arrayBits[i] | (carryFlag << 31);
		carryFlag = resBit;
	}
	return *this;
}

QInt QInt::lLogicalShift()
{
	int carryFlag = (this->arrayBits[3] >> 31);
	for (int i = 3; i >= 0;i--)
	{
		int resBit = this->arrayBits[i] >> 31;
		this->arrayBits[i] = this->arrayBits[i] << 1;
		if (i < 3)
		{
			this->arrayBits[i] = this->arrayBits[i] | carryFlag;
			carryFlag = resBit;
		}
	}
	return *this;
}

ostream& operator<<(ostream& Output, QInt& Display)
{
	for (int i = 0; i <= 3; i++)
	{
		Output << i << "-";
		for (int j = 31; j >= 0;j--)
		{
			Output << ((Display.arrayBits[i] >> j) & 1);
		}
		Output << " ";
	}
	Output << endl;
	return Output;
}




