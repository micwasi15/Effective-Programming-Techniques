#pragma once
#include "CTree.h"
#include "Imports.h"

const std::string s_intType = "int";
const std::string s_doubleType = "double";
const std::string s_stringType = "string";
const std::string s_boolType = "bool";
const char* const pc_types[] = { s_intType.c_str(), s_doubleType.c_str(), s_stringType.c_str(), s_boolType.c_str()};
const int i_numOfTypes = 4;

const std::string s_initMenuMsg = "Available commands: \n";
const std::string s_menuMsgCreateTree = "CREATE <type> - create a new tree. Available types: ";
const std::string s_menuMsgEnd = "END - stop the program\n";
const std::string s_menuMsgEnter = "ENTER <formula> - create a tree based on the formula\n";
const std::string s_menuMsgVars = "VARS - print vars from the tree\n";
const std::string s_menuMsgPrint = "PRINT - print the tree prefix\n";
const std::string s_menuMsgComp = "COMP <vars> - compute a solution for the following arguments\n";
const std::string s_menuMsgJoin = "JOIN <formula> - create a tree from the formula and attach it to the previous tree\n";

const std::string s_endCom = "END";
const std::string s_enterCom = "ENTER";
const std::string s_varsCom = "VARS";
const std::string s_printCom = "PRINT";
const std::string s_compCom = "COMP";
const std::string s_joinCom = "JOIN";
const std::string s_createCom = "CREATE";

const std::string s_invalidCommandErr = "This command does not exist. Try again.\n";
const std::string s_invalidFormulaErrMsg = "Input was not valid. It was corrected. Created tree: ";
const std::string s_resultMsg = "Result: ";

const std::string s_createTreeSucMsg = "The tree has been created succesfully\n";
const std::string s_joinSucMsg = "The formula was succesfully attached to the tree\n";

class CInterface
{
private:
	void vShowMenu();
	void vRunInner(std::string& psType);

public:
	void vRun();
};

template <typename T> class CInnerInterface {
private:
	void vShowInnerMenu();
	void vEnter(std::string& psFormula, CTree<T>& pcT);
	void vVars(CTree<T>& pcT);
	void vPrint(CTree<T>& pcT);
	void vComp(std::string& psVars, CTree<T>& pcT);
	void vJoin(std::string& psFormula, CTree<T>& pcT);
	std::string sGetTypeName();

public:
	void vRun();
};

