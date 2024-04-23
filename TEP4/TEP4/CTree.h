#pragma once
#include "CNode.h"
#include "Imports.h"

const std::string s_lastWordsNotReadErrMsg = "Some of the last elements of the formula were not read";
const std::string s_invalidElemsErrMsg = "Some of the elements were invalid. They were replaced with var: " + s_defaultVar + "\n";
const std::string s_tooManyValsErrMsg = "There were too many values. Redundant elements were ignored\n";
const std::string s_tooFewNumsErrMsg = "There were too few values. Variables without values returned number: " + s_defaultNum + "\n";
const std::string s_nonValErrMsg = "All arguments must be valid. Nonvalid elements were replaced with var: " + s_defaultVar + "\n";
const std::string s_divByZeroErrMsg = "There was an attempt to divide by 0. Please check the input\nThe result of the division was replaced with: " + s_defaultNum + "\n";
const std::string s_noVarsErrMsg = "The tree has no variables\n";
const char c_boolFalse = '0';

const std::string s_copyMsg = "Copy constructor called\n";

template <typename T> class CTree
{
private:
	CNode<T>* CRoot;
	std::vector<std::string> CVarsList;

public:
	CTree();
	CTree(std::string& psFormula, std::stringstream& pcSsErrorMsg);
	CTree(const CTree<T>& pcOther);
	CTree(CTree<T>&& pcOther);
	~CTree();

	CTree operator=(const CTree<T>& pcOther);
	CTree operator=(CTree<T>&& pcOther);
	CTree operator+(CTree<T>& pcOther);

	std::string sVars(std::stringstream& pcSsErrorMsg);
	std::string sToStrPrefix();
	T tComp(std::string& psVals, std::stringstream& pcSsErrorMsg);
	void vFillVals(int* piIdx, std::string& psVals, std::vector<T>& CValsVec, bool& bNonNumPresent);
	void vUpdateVarsList();
};

