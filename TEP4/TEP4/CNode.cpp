#include "CNode.h"
#include "InputControl.h"
#include "StringOpers.h"
#include "BoolOpers.h"

bool bIsVarNameValid(std::string& psStr) {
	if (psStr.empty()) {
		return 0;
	}

	if (std::isdigit(psStr.at(0))) {
		return 0;
	}

	for (char ch : psStr) {
		if (!std::isalnum(ch)) {
			return 0;
		}
	}

	return 1;
}

template <> bool bIsVal<int>(std::string& psStr) {
	return bIsNumber(psStr);
}

template <> bool bIsVal<double>(std::string& psStr) {
	return bIsFloat(psStr);
}

template <> bool bIsVal<bool>(std::string& psStr) {
	return psStr == s_boolNeg || psStr == s_boolPos;
}

template <> bool bIsVal<std::string>(std::string& psStr) {
	if (psStr.size() < 2) {
		return 0;
	}
	return psStr[0] == '\"' && psStr[psStr.size() - 1] == '\"';
}

template <typename T> bool bIsVal(std::string& psStr) {
	return 1;
}

template <typename T> bool bIsOper(std::string& psStr) {
	if (bIsNumOper(psStr)) {
		if (iArgNumOfOper(psStr) == 1) {
			throw std::invalid_argument("Wrong operator");
		}
		return 1;
	}
}

template <> bool bIsOper<std::string>(std::string& psStr) {
	return bIsStringOper(psStr);
}

template <typename T> CNode<T>* pcCreateNode(std::string& psStr, int* piIdx, bool* pbAreAllElemsValid) {
	std::string sWord = sGetNextWord(psStr, piIdx);

	if (bIsVal<T>(sWord)) {
		return new CNodeVal<T>(sWord);
	}
	else if (bIsOper<T>(sWord)) {
		return new CNodeOper<T>(sWord, psStr, piIdx, pbAreAllElemsValid);
	}
	else if (bIsVarNameValid(sWord)) {
		return new CNodeVar<T>(sWord);
	}
	else {
		*pbAreAllElemsValid = 0;
		return pcCreateDefaultNode<T>();
	}
}

template <> CNode<std::string>* pcCreateNode<std::string>(std::string& psStr, int* piIdx, bool* pbAreAllElemsValid) {
	std::string sWord = sGetNextWordStr(psStr, piIdx);

	if (bIsVal<std::string>(sWord)) {
		return new CNodeVal<std::string>(sWord);
	}
	else if (bIsOper<std::string>(sWord)) {
		return new CNodeOper<std::string>(sWord, psStr, piIdx, pbAreAllElemsValid);
	}
	else if (bIsVarNameValid(sWord)) {
		return new CNodeVar<std::string>(sWord);
	}
	else {
		*pbAreAllElemsValid = 0;
		return pcCreateDefaultNode<std::string>();
	}
}

template <> CNode<bool>* pcCreateDefaultNode() {
	return new CNodeVar<bool>(s_defaultVar);
}

template <typename T> CNode<T>* pcCreateDefaultNode() {
	return new CNodeVar<T>(s_defaultVar);
}

template <> ETypeOfVal CNode<int>::eTypeOfVal() {
	return integer;
}

template <> ETypeOfVal CNode<double>::eTypeOfVal() {
	return doub;
}

template <> ETypeOfVal CNode<std::string>::eTypeOfVal() {
	return str;
}

template <> CNodeOper<std::string>::CNodeOper(const std::string& psWord, std::string& psStr, int* piIdx, bool* pbAreAllElemsValid) {
	sOper = psWord;

	for (int i = 0; i < iArgNumOfOperStr(sOper); i++) {
		CNodes.push_back(pcCreateNode<std::string>(psStr, piIdx, pbAreAllElemsValid));
	}
}

template <typename T> CNodeOper<T>::CNodeOper(const std::string& psWord, std::string& psStr, int* piIdx, bool* pbAreAllElemsValid) {
	sOper = psWord;

	for (int i = 0; i < iArgNumOfOper(sOper); i++) {
		CNodes.push_back(pcCreateNode<T>(psStr, piIdx, pbAreAllElemsValid));
	}
}

template <typename T> CNodeOper<T>::CNodeOper(const CNodeOper<T>& pcOther) {
	sOper = pcOther.sOper;

	for (CNode<T>* pcNode : pcOther.CNodes) {
		CNodes.push_back(pcNode->pcClone());
	}
}

template <typename T> CNodeOper<T>::~CNodeOper() {
	for (CNode<T>* pcNode : CNodes) {
		delete pcNode;
	}
}

template <typename T> CNode<T>* CNodeOper<T>::pcClone() {
	return new CNodeOper<T>(*this);
}

template <typename T> ETypeOfNode CNodeOper<T>::eTypeOfNode() {
	return oper;
}

template <typename T> void CNodeOper<T>::operator=(const CNodeOper<T>& pcOther) {
	sOper = pcOther.sOper;

	for (CNode* pcNode : CNodes) {
		delete pcNode;
	}

	CNodes.clear();

	for (CNode* pcNode : pcOther.CNodes) {
		CNodes.push_back(new CNodeOper(*pcNode));
	}
}

template <typename T> T CNodeOper<T>::tEvaluate(std::map<std::string, T>& pcVarMap, bool& pbDivByZero) {
	if (sOper == s_sumOper) {
		return CNodes.at(0)->tEvaluate(pcVarMap, pbDivByZero) + CNodes.at(1)->tEvaluate(pcVarMap, pbDivByZero);
	}
	if (sOper == s_subOper) {
		return CNodes.at(0)->tEvaluate(pcVarMap, pbDivByZero) - CNodes.at(1)->tEvaluate(pcVarMap, pbDivByZero);
	}
	if (sOper == s_mulOper) {
		return CNodes.at(0)->tEvaluate(pcVarMap, pbDivByZero) * CNodes.at(1)->tEvaluate(pcVarMap, pbDivByZero);
	}
	if (sOper == s_divOper) {
		T dDivisor = CNodes.at(1)->tEvaluate(pcVarMap, pbDivByZero);
		if (dDivisor == 0) {
			pbDivByZero = 1;
			return i_defaultVal;
		}
		return CNodes.at(0)->tEvaluate(pcVarMap, pbDivByZero) / dDivisor;
	}
	if (sOper == s_sinOper) {
		return std::sin(CNodes.at(0)->tEvaluate(pcVarMap, pbDivByZero));
	}
	if (sOper == s_cosOper) {
		return std::cos(CNodes.at(0)->tEvaluate(pcVarMap, pbDivByZero));
	}

	return CNodes.at(0)->tEvaluate(pcVarMap, pbDivByZero);
}

template <> std::string CNodeOper<std::string>::tEvaluate(std::map<std::string, std::string>& pcVarMap, bool& pbDivByZero) {
	std::string sVal1 = CNodes.at(0)->tEvaluate(pcVarMap, pbDivByZero);
	std::string sVal2 = CNodes.at(1)->tEvaluate(pcVarMap, pbDivByZero);
	if (sOper == s_sumOper) {
		return sAdd(sVal1, sVal2);
	}
	if (sOper == s_subOper) {
		return sSub(sVal1, sVal2);
	}
	if (sOper == s_mulOper) {
		return sMul(sVal1, sVal2);
	}
	if (sOper == s_divOper) {
		return sDiv(sVal1, sVal2);
	}
	return s_defaultVal;
}

template <> bool CNodeOper<bool>::tEvaluate(std::map<std::string, bool>& pcVarMap, bool& pbDivByZero) {
	bool bVal1 = CNodes.at(0)->tEvaluate(pcVarMap, pbDivByZero);
	bool bVal2 = CNodes.at(1)->tEvaluate(pcVarMap, pbDivByZero);
	if (sOper == s_sumOper) {
		return bAdd(bVal1, bVal2);
	}
	if (sOper == s_subOper) {
		return bSub(bVal1, bVal2);
	}
	if (sOper == s_mulOper) {
		return bMul(bVal1, bVal2);
	}
	if (sOper == s_divOper) {
		return bDiv(bVal1, bVal2);
	}
	return b_defaultBool;
}

template <typename T> void CNodeOper<T>::vAddAllVarsToVec(std::vector<std::string>& pcVars) {
	for (CNode<T>* pcNode : CNodes) {
		pcNode->vAddAllVarsToVec(pcVars);
	}
}

template <typename T> bool CNodeOper<T>::bReplaceLastNode(CNode<T>& pcOther) {
	CNode<T>* pcLast = CNodes.back();

	if (pcLast->bReplaceLastNode(pcOther)) {
		return 1;
	}

	CNodes.pop_back();
	CNodes.push_back(pcOther.pcClone());

	return 1;
}

template <typename T> void CNodeOper<T>::vPrefix(std::stringstream& pcSs) {
	pcSs << sOper << " ";

	for (CNode<T>* pcNode : CNodes) {
		pcNode->vPrefix(pcSs);
	}
}

template <typename T> CNodeVar<T>::CNodeVar(const std::string& psWord) {
	sVarName = psWord;
}

template <typename T> CNodeVar<T>::CNodeVar(const CNodeVar<T>& pcOther) {
	sVarName = pcOther.sVarName;
}

template <typename T> void CNodeVar<T>::operator=(const CNodeVar<T>& pcOther) {
	sVarName = pcOther.sVarName;
}

template <typename T> CNode<T>* CNodeVar<T>::pcClone() {
	return new CNodeVar<T>(*this);
}

template <typename T> ETypeOfNode CNodeVar<T>::eTypeOfNode() {
	return var;
}

template <typename T> T CNodeVar<T>::tEvaluate(std::map<std::string, T>& pcVarMap, bool& pbDivByZero) {
	if (pcVarMap.find(sVarName) == pcVarMap.end()) {
		return i_defaultVal;
	}

	return pcVarMap.at(sVarName);
}

template <> bool CNodeVar<bool>::tEvaluate(std::map<std::string, bool>& pcVarMap, bool& pbDivByZero) {
	if (pcVarMap.find(sVarName) == pcVarMap.end()) {
		return b_defaultBool;
	}

	return pcVarMap.at(sVarName);
}

template <> std::string CNodeVar<std::string>::tEvaluate(std::map<std::string, std::string>& pcVarMap, bool& pbDivByZero) {
	if (pcVarMap.find(sVarName) == pcVarMap.end()) {
		return s_defaultVar;
	}

	std::string sRes = pcVarMap.at(sVarName);
	return sRes.size() > 2 ? sRes.substr(1, sRes.size() - 2) : "";
}

template <typename T> void CNodeVar<T>::vAddAllVarsToVec(std::vector<std::string>& pcVars) {
	pcVars.push_back(sVarName);
}

template <typename T> bool CNodeVar<T>::bReplaceLastNode(CNode<T>& pcOther) {
	return 0;
}

template <typename T> void CNodeVar<T>::vPrefix(std::stringstream& pcSs) {
	pcSs << sVarName << " ";
}

template <> CNodeVal<int>::CNodeVal(const std::string& psStr) {
	tVal = std::stoi(psStr);
}

template <> CNodeVal<double>::CNodeVal(const std::string& psStr) {
	tVal = std::stod(psStr);
}

template <> CNodeVal<bool>::CNodeVal(const std::string& psStr) {
	tVal = (psStr == s_defaultBool) ? b_defaultBool : !b_defaultBool;
}

template <> CNodeVal<std::string>::CNodeVal(const std::string& psStr) {
	if (psStr.size() < 2) {
		tVal = s_defaultVar;
		return;
	}
	tVal = psStr.substr(1, psStr.size() - 2);
}

template <typename T> CNodeVal<T>::CNodeVal(const CNodeVal<T>& pcOther) {
	tVal = pcOther.tVal;
}

template <typename T> void CNodeVal<T>::operator=(const CNodeVal<T>& pcOther) {
	tVal = pcOther.tVal;
}

template <typename T> CNode<T>* CNodeVal<T>::pcClone() {
	return new CNodeVal<T>(*this);
}

template <typename T> ETypeOfNode CNodeVal<T>::eTypeOfNode() {
	return num;
}

template <typename T> T CNodeVal<T>::tEvaluate(std::map<std::string, T>& pcVarMap, bool& pbDivByZero) {
	return tVal;
}

template <typename T> void CNodeVal<T>::vAddAllVarsToVec(std::vector<std::string>& pcVars) {
}

template <typename T> bool CNodeVal<T>::bReplaceLastNode(CNode<T>& pcOther) {
	return 0;
}

template <typename T> void CNodeVal<T>::vPrefix(std::stringstream& pcSs) {
	pcSs << tVal << " ";
}

template <> void CNodeVal<std::string>::vPrefix(std::stringstream& pcSs) {
	pcSs << "\"" << tVal << "\" ";
}

template class CNode<int>;
template class CNode<double>;
template class CNode<bool>;
template class CNode<std::string>;

template CNode<int>* pcCreateNode<int>(std::string& psStr, int* piIdx, bool* pbAreAllElemsValid);
template CNode<double>* pcCreateNode<double>(std::string& psStr, int* piIdx, bool* pbAreAllElemsValid);
template CNode<bool>* pcCreateNode<bool>(std::string& psStr, int* piIdx, bool* pbAreAllElemsValid);
template CNode<std::string>* pcCreateNode<std::string>(std::string& psStr, int* piIdx, bool* pbAreAllElemsValid);

template CNode<int>* pcCreateDefaultNode<int>();
template CNode<double>* pcCreateDefaultNode<double>();
template CNode<bool>* pcCreateDefaultNode<bool>();
template CNode<std::string>* pcCreateDefaultNode<std::string>();