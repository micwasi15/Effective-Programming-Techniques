#pragma once

const std::string s_defaultName = "default";
const int i_defaultSize = 10;
const std::string s_nonParMsg = "bezp: ";
const std::string s_parMsg = "parametr: ";
const std::string s_copyMsg = "kopiuj: ";
const std::string s_copyNamePostfix = "_copy";
const std::string s_delMsg = "usuwam: ";

class CTable
{
private:
	std::string sName;
	int *piTable;
	int iTableLenght;

public:
	CTable();
	CTable(std::string sName, int iTableLen);
	CTable(const CTable& pcOther);
	CTable(int iTableLen);
	~CTable();
	
	void vSetName(std::string sName);
	bool bSetNewSize(int iTableLen);
	int iGetSize();
	CTable* pcClone();
	void vAdd1AndCopy(CTable** cRes);
	void vPrintTable();
};

void v_mod_tab(CTable* pcTab, int iNewSize);
void v_mod_tab(CTable pcTab, int iNewSize);

