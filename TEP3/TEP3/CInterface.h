#pragma once
#include "CTree.h"
#include "Imports.h"


const std::string s_initMenuMsg = "Available commands: \n";
const std::string s_menuMsgEnd = "END - stop the program\n";
const std::string s_menuMsgEnter = "ENTER <formula> - create a tree based on the formula\n";
const std::string s_menuMsgVars = "VARS - print vars from the tree\n";
const std::string s_menuMsgPrint = "PRINT - print the tree prefix\n";//todo
const std::string s_menuMsgComp = "COMP <vars> - compute a solution for the following arguments\n";
const std::string s_menuMsgJoin = "JOIN <formula> - create a tree from the formula and attach it to the previous tree\n";

const std::string s_endCom = "END";
const std::string s_enterCom = "ENTER";
const std::string s_varsCom = "VARS";
const std::string s_printCom = "PRINT";
const std::string s_compCom = "COMP";
const std::string s_joinCom = "JOIN";

const std::string s_invalidCommandErr = "This command does not exist. Try again.\n";
const std::string s_invalidFormulaErrMsg = "Input was not valid. It was corrected. Created tree: ";
const std::string s_resultMsg = "Result: ";

const std::string s_createTreeSucMsg = "The tree has been created succesfully\n";
const std::string s_joinSucMsg = "The formula was succesfully attached to the tree\n";

class CInterface
{
private:
	void vShowMenu();

public:
	void vRun();
	void vEnter(std::string& psFormula, CTree& pcT);
	void vVars(CTree& pcT);
	void vPrint(CTree& pcT);
	void vComp(std::string& psVars, CTree& pcT);
	void vJoin(std::string& psFormula, CTree& pcT);
};

