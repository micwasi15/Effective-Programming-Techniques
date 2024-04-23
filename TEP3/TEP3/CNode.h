#pragma once
#include "Imports.h"

const int i_defaultVal = 1;
const std::string s_defaultNum = "1";

const std::string s_sumOper = "+";
const std::string s_subOper = "-";
const std::string s_mulOper = "*";
const std::string s_divOper = "/";
const std::string s_sinOper = "sin";
const std::string s_cosOper = "cos";

enum EType {oper, var, num};

bool bIsVarNameValid(std::string& psStr);

class CNode
{
private:
	std::string sVal;
	EType eType;
	std::vector<CNode*> CNodes;

public:
	CNode();
	CNode(std::string& psStr, int* piIdx, bool* pbAreAllElemsValid, bool* pbAreSumOpersValid);
	CNode(const CNode& pcOther);
	~CNode();
	
	void operator=(const CNode& pcOther);

	double dEvaluate(std::map<std::string, int>& pcVarMap, bool* pbDivByZero);
	void vAddAllVarsToVec(std::vector<std::string>& pcVars);
	void vReplaceLastNode(CNode& pcOther);
	void vPrefix(std::stringstream& pcSs);
};
