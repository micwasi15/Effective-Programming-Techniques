#pragma once
#include <sstream>

const int i_initTableLen = 1;
const int i_numberSys = 10;

class CNumber
{
private:
	int* piTable;
	int iLength;
	bool bIsNegative;

	void vClearTable();
	void vRepairTable();
	void vRepairTabFragment(int iBegIdx, int iEndIdx);
	bool bSetLenAndClear(int iNewLen);
	bool bCopyToSmallerTable(int iNewLen);
	int iNumberOfDigits(int iValue);

	bool bAreNumsBigger(CNumber& pcSmaller, int iShift);
	void vAdd(CNumber& pcFirVal, CNumber& pcSecVal);
	void vSubstract(CNumber& pcFirVal, CNumber& pcSecVal);

public:
	CNumber();
	CNumber(int iValue);
	CNumber(const CNumber& pcOther);
	~CNumber();

	void operator=(int iValue);
	void operator=(const CNumber& pcNewVal);
	CNumber operator+(CNumber& pcNewVal);
	CNumber operator-(CNumber& pcNewVal);
	CNumber operator*(CNumber& pcNewVal);
	CNumber operator/(CNumber& pcNewVal);
	CNumber operator+(int iNewVal);
	CNumber operator*(int iNewVal);
	CNumber operator-(int iNewVal);
	CNumber operator/(int iNewVal);
	CNumber cMod(CNumber& pcNewVal, CNumber** pcDiv);

	std::string sToStr();
};

