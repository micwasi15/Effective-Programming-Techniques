#include <iostream>
#include "Zadanie1.h"

void v_alloc_table_fill_34(int iSize) {
	if (iSize < 1) {
		std::cout << s_nonPosSizeOfTableErrMsg << std::endl;
		return;
	}
	int* piTable;
	piTable = new int[iSize];

	for (int i = 0; i < iSize; i++) {
		piTable[i] = i_TableValue;
	}
	for (int i = 0; i < iSize; i++) {
		std::cout << (i + 1) << ". " << piTable[i] << std::endl;
	}

	delete[] piTable;
}