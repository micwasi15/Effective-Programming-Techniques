#pragma once
#include "CNode.h"
#include "Imports.h"

const std::string s_lastWordsNotReadErrMsg = "Some of the last elements of the formula were not read";
const std::string s_invalidElemsErrMsg = "Some of the elements were invalid. They were replaced with element: " + s_defaultNum + "\n";
const std::string s_tooManyValsErrMsg = "There were too many values. Redundant numbers were ignored\n";
const std::string s_tooFewValsErrMsg = "There were too few values. Variables without values returned number: " + s_defaultNum + "\n";
const std::string s_nonNumErrMsg = "All arguments must be numbers. Nonnumber elements were replaced with value: " + s_defaultNum + "\n";
const std::string s_divByZeroErrMsg = "There was an attempt to divide by 0. Please check the input\nThe result of the division was replaced with: " + s_defaultNum + "\n";
const std::string s_sumNonValidErrMsg = "The " + s_sumOper + "'s right argument has to be an operator. It was replaced with: " + s_subOper + " " + s_defaultNum + " " + s_defaultNum + "\n";

class CTree
{
private:
	CNode CRoot;
	std::vector<std::string> CVarsList;

public:
	CTree();
	CTree(std::string& psFormula, std::stringstream& pcSsErrorMsg);
	CTree(const CTree& pcOther);
	
	void operator=(const CTree& pcOther);
	CTree operator+(CTree& pcOther);

	std::string sVars();
	std::string sToStrPrefix();
	double dComp(std::string& psVals, std::stringstream& pcSsErrorMsg);
};

