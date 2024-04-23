#include "CTree.h"
#include "InputControl.h"

CTree::CTree() {
	CRoot = CNode();
}

CTree::CTree(std::string& psFormula, std::stringstream& pcSsErrorMsg) {
	int* piIdx = new int;
	*piIdx = 0;
	bool* pbAreAllElemsValid = new bool;
	*pbAreAllElemsValid = 1;
	bool* pbAreSumOpersValid = new bool;
	*pbAreSumOpersValid = 1;

	CRoot = CNode(psFormula, piIdx, pbAreAllElemsValid, pbAreSumOpersValid);

	CRoot.vAddAllVarsToVec(CVarsList);
	vRemoveDuplicatesFromVec(CVarsList);

	if ((*piIdx) < psFormula.size()) {
		pcSsErrorMsg << s_lastWordsNotReadErrMsg;
	}
	if (!(*pbAreAllElemsValid)) {
		pcSsErrorMsg << s_invalidElemsErrMsg;
	}
	if (!(*pbAreSumOpersValid)) {
		pcSsErrorMsg << s_sumNonValidErrMsg;
	}

	delete piIdx;
	delete pbAreAllElemsValid;
	delete pbAreSumOpersValid;
}

CTree::CTree(const CTree& pcOther) {
	*this = pcOther;
}

void CTree::operator=(const CTree& pcOther) {
	CRoot = CNode(pcOther.CRoot);
	CVarsList = pcOther.CVarsList;
}

CTree CTree::operator+(CTree& pcOther) {
	CTree CTemp;
	CTemp = *this;
	CTemp.CRoot.vReplaceLastNode(pcOther.CRoot);

	return CTemp;
}

std::string CTree::sVars() {
	std::stringstream CSs;

	for (std::string sStr : CVarsList) {
		CSs << sStr << " ";
	}

	return CSs.str();
}

std::string CTree::sToStrPrefix() {
	std::stringstream CSs;

	CRoot.vPrefix(CSs);

	return CSs.str();
}

double CTree::dComp(std::string& psVals, std::stringstream& pcSsErrorMsg) {
	std::vector<int> CVals;
	std::string sWord;
	int* piIdx = new int;
	*piIdx = 0;
	bool bNonNumPresent = 0;

	while (*piIdx < psVals.size()) {
		sWord = sGetNextWord(psVals, piIdx);

		if (isNumber(sWord)) {
			CVals.push_back(std::atoi(sWord.data()));
		}
		else if (!sWord.empty()) {
			CVals.push_back(i_defaultVal);
			bNonNumPresent = 1;
		}
	}

	if (bNonNumPresent) {
		pcSsErrorMsg << s_nonNumErrMsg;
	}

	if (CVarsList.size() > CVals.size()) {
		pcSsErrorMsg << s_tooFewValsErrMsg;
	}
	else if (CVarsList.size() < CVals.size()) {
		pcSsErrorMsg << s_tooManyValsErrMsg;
	}

	std::map<std::string, int> CMapVarVal;

	for (int i = 0; i < CVarsList.size() && i < CVals.size(); i++) {
		CMapVarVal.emplace(CVarsList.at(i), CVals.at(i));
	}

	delete piIdx;

	bool* pbDivByZero = new bool;
	*pbDivByZero = 0;
	double dRes = CRoot.dEvaluate(CMapVarVal, pbDivByZero);

	if (*pbDivByZero) {
		pcSsErrorMsg << s_divByZeroErrMsg;
		return i_defaultVal;
	}

	return dRes;
}
