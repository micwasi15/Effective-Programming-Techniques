#include <iostream>
#include "CTable.h"
#include <algorithm>

CTable::CTable() {
	sName = s_defaultName;
	piTable = new int[i_defaultSize];
	iTableLenght = i_defaultSize;

	std::cout << s_nonParMsg << "'" << sName << "'" << std::endl;
}

CTable::CTable(std::string sName, int iTableLen) {
	if (sName.empty()) {
		sName = s_defaultName;
	}
	if (iTableLen < 1) {
		iTableLen = i_defaultSize;
	}
	this->sName = sName;
	piTable = new int[iTableLen];
	iTableLenght = iTableLen;

	std::cout << s_parMsg << "'" << this->sName << "'" << std::endl;
}

CTable::CTable(CTable& pcOther) {
	std::cout << s_copyMsg << "'" << pcOther.sName << "'" << std::endl;
	sName = pcOther.sName + s_copyNamePostfix;
	iTableLenght = pcOther.iTableLenght;
	piTable = new int[iTableLenght];

	for (int i = 0; i < iTableLenght; i++) {
		piTable[i] = pcOther.piTable[i];
	}
}

CTable::CTable(int iSize) {
	sName = s_defaultName;
	iTableLenght = iSize;
	piTable = new int[iSize];

	for (int i = 0; i < iSize; i++) {
		piTable[i] = i + 1;
	}
}

CTable::~CTable() {
	std::cout << s_delMsg << "'" << sName << "'" << std::endl;
	delete[] piTable;
}

void CTable::vSetName(std::string sName) {
	if (!sName.empty()) {
		this->sName = sName;
	}
}

bool CTable::bSetNewSize(int iTableLen) {
	if (iTableLen < 1) {
		return false;
	}
	int iElementsToCopy = std::min(iTableLen, iTableLenght);
	iTableLenght = iTableLen;
	int* piTableCopy = new int[iTableLen];

	for (int i = 0; i < iElementsToCopy; i++) {
		piTableCopy[i] = piTable[i];
	}
	delete[] piTable;
	piTable = piTableCopy;

	return true;
}

int CTable::iGetSize() {
	return iTableLenght;
}

void CTable::vPrintTable() {
	for (int i = 0; i < iTableLenght; i++) {
		std::cout << piTable[i] << " ";
	}
}

CTable* CTable::pcClone() {
	return new CTable(*this);
}

void CTable::vAdd1AndCopy(CTable** cRes) {
	*cRes = new CTable(sName, iTableLenght + 1);
	for (int i = 0; i < iTableLenght; i++) {
		(*cRes)->piTable[i] = piTable[i];
	}
	(*cRes)->piTable[iTableLenght] = 1;
}

void v_mod_tab(CTable* pcTab, int iNewSize) {
	if (pcTab != nullptr) {
		pcTab->bSetNewSize(iNewSize);
	}
}

void v_mod_tab(CTable cTab, int iNewSize) {
	cTab.bSetNewSize(iNewSize);
}