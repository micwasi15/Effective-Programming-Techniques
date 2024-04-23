#include "CNumber.h"
#include "TableOper.h"

CNumber::CNumber() {
	iLength = i_initTableLen;
	piTable = new int[i_initTableLen];
	bIsNegative = 0;
	vClearTable();
}

CNumber::CNumber(int iValue) {
	*this = iValue;
}

CNumber::CNumber(const CNumber& pcOther) {
	iLength = pcOther.iLength;
	piTable = new int[pcOther.iLength];
	bIsNegative = pcOther.bIsNegative;
	for (int i = 0; i < iLength; i++) {
		piTable[i] = pcOther.piTable[i];
	}
}

CNumber::~CNumber() {
	delete[] piTable;
}

void CNumber::operator=(int iValue) {
	iLength = iNumberOfDigits(iValue);
	bIsNegative = iValue >= 0 ? 0 : 1;
	delete[] piTable;
	piTable = new int[iLength];

	iValue = std::abs(iValue);
	for (int i = 0; i < iLength; i++) {
		piTable[i] = iValue % i_numberSys;
		iValue /= i_numberSys;
	}
}

void CNumber::operator=(const CNumber& pcNewVal) {
	iLength = pcNewVal.iLength;
	bIsNegative = pcNewVal.bIsNegative;
	delete[] piTable;
	piTable = new int[iLength];
	for (int i = 0; i < iLength; i++) {
		piTable[i] = pcNewVal.piTable[i];
	}
}

CNumber CNumber::operator+(CNumber& pcNewVal) {
	if (pcNewVal.iLength == 0 || this->iLength == 0)
		return CNumber();

	CNumber pcRes;
	
	if (bIsNegative && !pcNewVal.bIsNegative) {
		pcRes.vSubstract(pcNewVal, *this);
	}
	else if (!bIsNegative && pcNewVal.bIsNegative) {
		pcRes.vSubstract(*this, pcNewVal);
	}
	else {
		pcRes.vAdd(*this, pcNewVal);
		pcRes.bIsNegative = bIsNegative;
	}

	return pcRes;
}

CNumber CNumber::operator-(CNumber& pcNewVal) {
	if (pcNewVal.iLength == 0 || this->iLength == 0)
		return CNumber();

	CNumber pcRes;

	if (!bIsNegative && !pcNewVal.bIsNegative) {
		pcRes.vSubstract(*this, pcNewVal);
	}
	else if (bIsNegative && pcNewVal.bIsNegative) {
		pcRes.vSubstract(pcNewVal, *this);
	} else {
		pcRes.vAdd(*this, pcNewVal);
		pcRes.bIsNegative = bIsNegative;
	}

	return pcRes;
}

CNumber CNumber::operator*(CNumber& pcNewVal) {
	if (pcNewVal.iLength == 0 || this->iLength == 0)
		return CNumber();

	CNumber pcRes;

	pcRes.bSetLenAndClear(iLength + pcNewVal.iLength);
	for (int i = 0; i < iLength; i++) {
		for (int j = 0; j < pcNewVal.iLength; j++) {
			pcRes.piTable[i + j] += piTable[i] * pcNewVal.piTable[j];
		}
	}
	pcRes.vRepairTable();
	pcRes.bIsNegative = bIsNegative != pcNewVal.bIsNegative;

	return pcRes;
}

CNumber CNumber::operator/(CNumber& pcNewVal) {
	CNumber* pcRes = new CNumber();
	cMod(pcNewVal, &pcRes);
	CNumber CRes = *pcRes;
	delete pcRes;

	return CRes;
}

CNumber CNumber::cMod(CNumber& pcNewVal, CNumber** pcDiv) {
	if ((pcNewVal.iLength == 0 || this->iLength == 0) || (pcNewVal.iLength == 1 && pcNewVal.piTable[0] == 0))
		throw std::invalid_argument("Invalid input");
	if (*pcDiv == NULL)
		*pcDiv = new CNumber();

	CNumber CRes;
	CRes = *this;

	(**pcDiv).bSetLenAndClear(iLength);
	for (int i = iLength - pcNewVal.iLength; i >= 0; i--) {
		while (CRes.bAreNumsBigger(pcNewVal, i)) {
			for (int j = 0; j < pcNewVal.iLength; j++) {
				CRes.piTable[i + j] -= pcNewVal.piTable[j];
			}
			CRes.vRepairTabFragment(i, i + pcNewVal.iLength);
			(**pcDiv).piTable[i]++;
		}
		if (i > 0) {
			CRes.piTable[i + pcNewVal.iLength - 2] +=
				CRes.piTable[i + pcNewVal.iLength - 1] * i_numberSys;
			CRes.piTable[i + pcNewVal.iLength - 1] = 0;
		}
	}
	CRes.vRepairTable();
	(**pcDiv).vRepairTable();
	(**pcDiv).bIsNegative = bIsNegative != pcNewVal.bIsNegative;

	return CRes;
}

CNumber CNumber::operator+(int iNewVal) {
	CNumber CTemp;
	CTemp = iNewVal;
	return (*this) + CTemp;
}

CNumber CNumber::operator-(int iNewVal) {
	CNumber CTemp;
	CTemp = iNewVal;
	return (*this) - CTemp;
}

CNumber CNumber::operator*(int iNewVal) {
	CNumber CTemp;
	CTemp = iNewVal;
	return (*this) * CTemp;
}

CNumber CNumber::operator/(int iNewVal) {
	CNumber CTemp;
	CTemp = iNewVal;
	return (*this) / CTemp;
}

bool CNumber::bAreNumsBigger(CNumber& pcSmaller, int iOff) {
	if (iLength < pcSmaller.iLength) {
		return 0;
	}

	for (int i = pcSmaller.iLength - 1; i >= 0; i--) {
		if (piTable[i + iOff] < pcSmaller.piTable[i]) {
			return 0;
		}
		if (piTable[i + iOff] > pcSmaller.piTable[i]) {
			return 1;
		}
	}

	return 1;
}

void CNumber::vAdd(CNumber& pcFirVal, CNumber& pcSecVal) {
	int iBiggerLen = std::max(pcFirVal.iLength, pcSecVal.iLength);
	int iSmallerLen = std::min(pcFirVal.iLength, pcSecVal.iLength);

	bSetLenAndClear(iBiggerLen + 1);
	for (int i = 0; i < iSmallerLen; i++) {
		piTable[i] = pcFirVal.piTable[i] + pcSecVal.piTable[i];
	}

	CNumber* CTemp = pcFirVal.iLength > pcSecVal.iLength ? &pcFirVal : &pcSecVal;
	vCopyTable(iSmallerLen, iBiggerLen - 1, &(CTemp->piTable), &(piTable));
	vRepairTable();
}

void CNumber::vSubstract(CNumber& pcFirVal, CNumber& pcSecVal) {
	CNumber CTemp;
	CTemp = pcSecVal;

	for (int i = 0; i < CTemp.iLength; i++) {
		CTemp.piTable[i] *= -1;
	}

	vAdd(pcFirVal, CTemp);
}

std::string CNumber::sToStr() {
	std::stringstream ss;

	if (bIsNegative) {
		ss << "-";
	}
	for (int i = iLength - 1; i >= 0; i--) {
		ss << piTable[i];
	}

	return ss.str();
}

void CNumber::vClearTable() {
	for (int i = 0; i < iLength; i++) {
		piTable[i] = 0;
	}
}

void CNumber::vRepairTable() {
	for (int i = 0; i < iLength - 1; i++) {
		if (piTable[i] >= i_numberSys) {
			piTable[i + 1] += piTable[i] / i_numberSys;
			piTable[i] %= i_numberSys;
		}
		else if (piTable[i] < 0) {
			piTable[i] = std::abs(piTable[i]);
			piTable[i + 1] -= (piTable[i] - 1) / i_numberSys + 1;
			piTable[i] = i_numberSys - piTable[i];
		}
	}

	int iLastIdx = iLength - 1;
	while (piTable[iLastIdx] == 0 && iLastIdx > 0) {
		iLastIdx--;
	}

	if (piTable[iLastIdx] < 0) {
		bIsNegative = 1;
		int iFirstNonZeroIdx = 0;
		while (piTable[iFirstNonZeroIdx] == 0 && iFirstNonZeroIdx < iLastIdx) {
			iFirstNonZeroIdx++;
		}

		if (iLastIdx != iFirstNonZeroIdx) {
			piTable[iLastIdx] = std::abs(piTable[iLastIdx]) - 1;
			for (int i = iLastIdx - 1; i > iFirstNonZeroIdx; i--) {
				piTable[i] = i_numberSys - 1 - piTable[i];
			}
			piTable[iFirstNonZeroIdx] = i_numberSys - piTable[iFirstNonZeroIdx];
		}
		else {
			piTable[iLastIdx] = std::abs(piTable[iLastIdx]);
		}
		while (piTable[iLastIdx] == 0 && iLastIdx > 0) {
			iLastIdx--;
		}
	}
	else {
		bIsNegative = 0;
	}
	bCopyToSmallerTable(iLastIdx + 1);
}

void CNumber::vRepairTabFragment(int iBegIdx, int iEndIdx) {
	for (int i = iBegIdx; i < iEndIdx; i++) {
		if (piTable[i] < 0) {
			piTable[i + 1]--;
			piTable[i] += i_numberSys;
		}
	}
}

bool CNumber::bCopyToSmallerTable(int iNewLen) {
	if (iNewLen >= iLength || iNewLen < 1)
		return 0;

	int* piNewTable = new int[iNewLen];

	for (int i = 0; i < iNewLen; i++) {
		piNewTable[i] = piTable[i];
	}
	delete[] piTable;
	piTable = piNewTable;
	iLength = iNewLen;

	return 1;
}

bool CNumber::bSetLenAndClear(int iNewLen) {
	if (iNewLen < 1)
		return 0;

	iLength = iNewLen;
	delete[] piTable;
	piTable = new int[iNewLen];
	vClearTable();

	return 1;
}

int CNumber::iNumberOfDigits(int iValue) {
	iValue = std::abs(iValue);
	int res = 0;

	while (iValue > 0) {
		res++;
		iValue /= i_numberSys;
	}
	return res;
}
