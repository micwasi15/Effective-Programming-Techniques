#include <iostream>
#include "Zadanie1.h"
#include "Zadanie2.h"
#include "Zadanie3.h"
#include "CTable.h"

int main()
{
	v_alloc_table_fill_34(5);
	int** pi_table;
	std::cout << b_alloc_table_2_dim(&pi_table, 5, 3) << std::endl;
	std::cout << b_dealloc_table_2_dim(pi_table, 5, 3) << std::endl;
	std::cout << b_alloc_table_2_dim(NULL, 3, 3) << std::endl << std::endl;


	CTable* pcTable = new CTable();
	delete pcTable;

	pcTable = new CTable("tablica", 5);
	delete pcTable;

	pcTable = new CTable("", 0);
	CTable* pcSecTab = new CTable(*pcTable);
	delete pcSecTab;

	std::cout << pcTable->bSetNewSize(12) << std::endl;
	std::cout << pcTable->bSetNewSize(4) << std::endl << std::endl;


	pcTable->vSetName("nowa nazwa");
	pcSecTab = pcTable->pcClone();
	delete pcSecTab;

	v_mod_tab(pcTable, 8);
	std::cout << pcTable->iGetSize() << std::endl;
	v_mod_tab(*pcTable, 3);
	std::cout << pcTable->iGetSize() << std::endl;
	delete pcTable;

	std::cout << std::endl;
	CTable* cpTableArray = new CTable[5];
	delete[] cpTableArray;
	CTable cStaticAllocTab;

	std::cout << "\n\n\n";
	CTable cOrig(4);
	CTable* pcCopy;
	cOrig.vAdd1AndCopy(&pcCopy);
	pcCopy->vPrintTable();
	delete pcCopy;
}
