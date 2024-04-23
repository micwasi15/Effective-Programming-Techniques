#include "CTree.h"
#include "InputControl.h"
#include "CNode.h"

template <typename T> CTree<T>::CTree() {
	CRoot = pcCreateDefaultNode<T>();
}

template <typename T> CTree<T>::CTree(std::string& psFormula, std::stringstream& pcSsErrorMsg) {
	int* piIdx = new int;
	*piIdx = 0;
	bool* pbAreAllElemsValid = new bool;
	*pbAreAllElemsValid = 1;

	CRoot = pcCreateNode<T>(psFormula, piIdx, pbAreAllElemsValid);

	CRoot->vAddAllVarsToVec(CVarsList);
	vRemoveDuplicatesFromVec(CVarsList);

	if ((*piIdx) < psFormula.size()) {
		pcSsErrorMsg << s_lastWordsNotReadErrMsg;
	}
	if (!(*pbAreAllElemsValid)) {
		pcSsErrorMsg << s_invalidElemsErrMsg;
	}

	delete piIdx;
	delete pbAreAllElemsValid;
}

template <typename T> CTree<T>::CTree(const CTree<T>& pcOther) {
	std::cout << s_copyMsg;

	CRoot = pcOther.CRoot->pcClone();
	vUpdateVarsList();
}

template <typename T> CTree<T>::CTree(CTree<T>&& pcOther) {
	CVarsList = std::move(pcOther.CVarsList);
	CRoot = pcOther.CRoot;
	pcOther.CRoot = NULL;
}

template <typename T> CTree<T>::~CTree() {
	if (CRoot != NULL) {
		delete CRoot;
	}
}

template <typename T> CTree<T> CTree<T>::operator=(const CTree<T>& pcOther) {
	std::cout << s_copyMsg;

	if (this == &pcOther) {
		return (*this);
	}

	if (CRoot != NULL) {
		delete CRoot;
	}

	CRoot = pcOther.CRoot->pcClone();
	vUpdateVarsList();

	return (*this);
}

template <typename T> CTree<T> CTree<T>::operator=(CTree<T>&& pcOther) {
	if (CRoot != NULL) {
		delete CRoot;
	}

	CVarsList = std::move(pcOther.CVarsList);
	CRoot = pcOther.CRoot;
	pcOther.CRoot = NULL;

	return (*this);
}

template <typename T> CTree<T> CTree<T>::operator+(CTree<T>& pcOther) {
	CTree CTemp;
	CTemp = (*this);

	if (CTemp.CRoot->bReplaceLastNode(*(pcOther.CRoot))) {
		CTemp.vUpdateVarsList();

		return std::move(CTemp);
	}

	return std::move(pcOther);
}

template <typename T> std::string CTree<T>::sVars(std::stringstream& pcSsErrorMsg) {
	if (CVarsList.empty()) {
		pcSsErrorMsg << s_noVarsErrMsg;
		return "";
	}

	std::stringstream CSs;

	for (int i = 0; i < CVarsList.size(); i++) {
		CSs << CVarsList.at(i) << " ";
	}

	return CSs.str();
}

template <typename T> std::string CTree<T>::sToStrPrefix() {
	std::stringstream CSs;

	CRoot->vPrefix(CSs);

	return CSs.str();
}

template <typename T> T CTree<T>::tComp(std::string& psVals, std::stringstream& pcSsErrorMsg) {
	std::vector<T> CVals;
	int* piIdx = new int;
	*piIdx = 0;
	bool bNonNumPresent = 0;

	vFillVals(piIdx, psVals, CVals, bNonNumPresent);

	if (bNonNumPresent) {
		pcSsErrorMsg << s_nonValErrMsg;
	}

	if (CVarsList.size() > CVals.size()) {
		pcSsErrorMsg << s_tooFewNumsErrMsg;
	}
	else if (CVarsList.size() < CVals.size()) {
		pcSsErrorMsg << s_tooManyValsErrMsg;
	}

	std::map<std::string, T> CMapVarVal;

	for (int i = 0; i < CVarsList.size() && i < CVals.size(); i++) {
		CMapVarVal.emplace(CVarsList.at(i), CVals.at(i));
	}

	delete piIdx;

	bool pbDivByZero = 0;
	T tRes = CRoot->tEvaluate(CMapVarVal, pbDivByZero);

	if (pbDivByZero) {
		pcSsErrorMsg << s_divByZeroErrMsg;
	}

	return tRes;
}

template<> void CTree<int>::vFillVals(int* piIdx, std::string& psVals, std::vector<int>& pcVals, bool& pbNonNumPresent) {
	std::string sWord;

	while (*piIdx < psVals.size()) {
		sWord = sGetNextWord(psVals, piIdx);

		if (bIsVal<int>(sWord)) {
			pcVals.push_back(std::atoi(sWord.data()));
		}
		else if (!sWord.empty()) {
			pcVals.push_back(i_defaultVal);
			pbNonNumPresent = 1;
		}
	}
}

template <> void CTree<double>::vFillVals(int* piIdx, std::string& psVals, std::vector<double>& pcVals, bool& pbNonNumPresent) {
	std::string sWord;

	while (*piIdx < psVals.size()) {
		sWord = sGetNextWord(psVals, piIdx);

		if (bIsVal<double>(sWord)) {
			pcVals.push_back(std::atof(sWord.data()));
		}
		else if (!sWord.empty()) {
			pcVals.push_back(i_defaultVal);
			pbNonNumPresent = 1;
		}
	}
}

template<> void CTree<bool>::vFillVals(int* piIdx, std::string& psVals, std::vector<bool>& pcVals, bool& pbNonNumPresent) {
	std::string sWord;

	while (*piIdx < psVals.size()) {
		sWord = sGetNextWord(psVals, piIdx);

		if (bIsVal<bool>(sWord)) {
			if (sWord[0] == c_boolFalse)
				pcVals.push_back(0);
			else
				pcVals.push_back(1);
		}
		else if (!sWord.empty()) {
			pcVals.push_back(i_defaultVal);
			pbNonNumPresent = 1;
		}
	}
}

template <> void CTree<std::string>::vFillVals(int* piIdx, std::string& psVals, std::vector<std::string>& pcValsVec, bool& pbNonNumPresent) {
	std::string sWord;

	while (*piIdx < psVals.size()) {
		sWord = sGetNextWordStr(psVals, piIdx);

		if (bIsVal<std::string>(sWord)) {
			pcValsVec.push_back(sWord);
		}
		else if (!sWord.empty()) {
			pcValsVec.push_back(s_defaultVar);
			pbNonNumPresent = 1;
		}
	}
}

template <typename T> void CTree<T>::vUpdateVarsList() {
	CVarsList.clear();
	CRoot->vAddAllVarsToVec(CVarsList);
	vRemoveDuplicatesFromVec(CVarsList);
}

template class CTree<int>;
template class CTree<double>;
template class CTree<bool>;
template class CTree<std::string>;