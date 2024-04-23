#pragma once
#include "Imports.h"

const int i_defaultVal = 1;
const std::string s_defaultNum = "1";
const std::string s_defaultVal = "\"default\"";
const std::string s_defaultVar = "default";
const std::string s_defaultBool = "1";
const std::string s_boolPos = "1";
const std::string s_boolNeg = "0";
const bool b_defaultBool = 1;

const std::string s_sumOper = "+";
const std::string s_subOper = "-";
const std::string s_mulOper = "*";
const std::string s_divOper = "/";
const std::string s_sinOper = "sin";
const std::string s_cosOper = "cos";

enum ETypeOfNode { oper, var, num };
enum ETypeOfVal { integer, doub, str };

bool bIsVarNameValid(std::string& psStr);
template <typename T> bool bIsVal(std::string& psStr);
template <typename T> bool bIsOper(std::string& psStr);

template <typename T> class CNode
{
private:

public:
	virtual T tEvaluate(std::map<std::string, T>& pcVarMap, bool& pbDivByZero) = 0;
	virtual void vAddAllVarsToVec(std::vector<std::string>& pcVars) = 0;
	virtual bool bReplaceLastNode(CNode<T>& pcOther) = 0;
	virtual void vPrefix(std::stringstream& pcSs) = 0;
	virtual CNode<T>* pcClone() = 0;

	ETypeOfVal eTypeOfVal();
	virtual ETypeOfNode eTypeOfNode() = 0;
};

template <typename T> class CNodeOper : public CNode<T>
{
public:
	CNodeOper(const std::string& psWord, std::string& psStr, int* piIdx, bool* pbAreAllElemsValid);
	CNodeOper(const CNodeOper& pcOther);
	~CNodeOper();

	void operator=(const CNodeOper& pcOther);
	T tEvaluate(std::map<std::string, T>& pcVarMap, bool& pbDivByZero);
	void vAddAllVarsToVec(std::vector<std::string>& pcVars);
	bool bReplaceLastNode(CNode<T>& pcOther);
	void vPrefix(std::stringstream& pcSs);
	CNode<T>* pcClone();
	ETypeOfNode eTypeOfNode();

private:
	std::string sOper;
	std::vector<CNode<T>*> CNodes;
};

template <typename T> class CNodeVar : public CNode<T>
{
private:
	std::string sVarName;

public:
	CNodeVar(const std::string& psWord);
	CNodeVar(const CNodeVar& pcOther);

	void operator=(const CNodeVar& pcOther);
	T tEvaluate(std::map<std::string, T>& pcVarMap, bool& pbDivByZero);
	void vAddAllVarsToVec(std::vector<std::string>& pcVars);
	bool bReplaceLastNode(CNode<T>& pcOther);
	void vPrefix(std::stringstream& pcSs);
	CNode<T>* pcClone();
	ETypeOfNode eTypeOfNode();
};

template <typename T> class CNodeVal : public CNode<T>
{
private:
	T tVal;

public:
	CNodeVal(const std::string& psStr);
	CNodeVal(const CNodeVal& pcOther);

	void operator=(const CNodeVal& pcOther);
	T tEvaluate(std::map<std::string, T>& pcVarMap, bool& pbDivByZero);
	void vAddAllVarsToVec(std::vector<std::string>& pcVars);
	bool bReplaceLastNode(CNode<T>& pcOther);
	void vPrefix(std::stringstream& pcSs);
	CNode<T>* pcClone();
	ETypeOfNode eTypeOfNode();
};

template <typename T> CNode<T>* pcCreateNode(std::string& psStr, int* piIdx, bool* pbAreAllElemsValid);
template <typename T> CNode<T>* pcCreateDefaultNode();
