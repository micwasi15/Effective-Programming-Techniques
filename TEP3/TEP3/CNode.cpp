#include "CNode.h"
#include "InputControl.h"

bool bIsVarNameValid(std::string& psStr) {
	if (psStr.empty()) {
		return 0;
	}

	if (std::isdigit(psStr.at(0))){
		return 0;
	}

	for (char ch : psStr) {
		if (!std::isalnum(ch)) {
			return 0;
		}
	}

	return 1;
}

CNode::CNode() {
	eType = num;
	sVal = s_defaultNum;
}

CNode::CNode(std::string& psStr, int* piIdx, bool* pbAreAllElemsValid, bool* pbAreSumOpersValid) {
	std::string sWord = sGetNextWord(psStr, piIdx);
	sVal = sWord;

	if (isNumber(sWord)) {
		eType = num;
	}
	else if (isOper(sWord)) {
		eType = oper;
	}
	else if (bIsVarNameValid(sWord)) {
		eType = var;
	}
	else {
		eType = num;
		sVal = s_defaultNum;
		*pbAreAllElemsValid = 0;
	}

	if (eType == oper) {
		for (int i = 0; i < iArgNumOfOper(sVal); i++) {
			CNodes.push_back(new CNode(psStr, piIdx, pbAreAllElemsValid, pbAreSumOpersValid));
		}
		
		if (sVal == s_sumOper) {
			CNode* CTemp = CNodes.at(0);

			if (CTemp->eType != num) {
				CTemp->eType = num;
				CTemp->sVal = s_defaultNum;
				for (int i = 0; i < CTemp->CNodes.size(); i++) {
					delete (CTemp->CNodes.at(i));
				}
				CTemp->CNodes.clear();

				*pbAreSumOpersValid = 0;
			}

			CTemp = CNodes.at(1);

			if (CTemp->eType != oper) {
				CTemp->eType = oper;
				CTemp->sVal = s_subOper;
				for (int i = 0; i < iArgNumOfOper(CTemp->sVal); i++) {
					CTemp->CNodes.push_back(new CNode());
				}

				*pbAreSumOpersValid = 0;
			}
		}
	}
}

CNode::CNode(const CNode& pcOther) {
	*this = pcOther;
}

CNode::~CNode() {
	for (int i = 0; i < CNodes.size(); i++) {
		delete CNodes.at(i);
	}
}

void CNode::operator=(const CNode& pcOther) {
	for (int i = 0; i < CNodes.size(); i++) {
		delete CNodes.at(i);
	}
	CNodes.clear();

	for (int i = 0; i < pcOther.CNodes.size(); i++) {
		CNodes.push_back(new CNode(*(pcOther.CNodes.at(i))));
	}

	eType = pcOther.eType;
	sVal = pcOther.sVal;
}

double CNode::dEvaluate(std::map<std::string, int>& pcVarMap, bool* pbDivByZero) {
	if (eType == num) {
		return std::atoi(sVal.data());
	}

	if (eType == oper) {
		if (sVal == s_sumOper) {
			return CNodes.at(0)->dEvaluate(pcVarMap, pbDivByZero) + CNodes.at(1)->dEvaluate(pcVarMap, pbDivByZero);
		}
		if (sVal == s_subOper) {
			return CNodes.at(0)->dEvaluate(pcVarMap, pbDivByZero) - CNodes.at(1)->dEvaluate(pcVarMap, pbDivByZero);
		}
		if (sVal == s_mulOper) {
			return CNodes.at(0)->dEvaluate(pcVarMap, pbDivByZero) * CNodes.at(1)->dEvaluate(pcVarMap, pbDivByZero);
		}
		if (sVal == s_divOper) {
			double dDivisor = CNodes.at(1)->dEvaluate(pcVarMap, pbDivByZero);
			if (dDivisor == 0) {
				*pbDivByZero = 1;
				return i_defaultVal;
			}
			return CNodes.at(0)->dEvaluate(pcVarMap, pbDivByZero) / dDivisor;
		}
		if (sVal == s_sinOper) {
			return std::sin(CNodes.at(0)->dEvaluate(pcVarMap, pbDivByZero));
		}
		if (sVal == s_cosOper) {
			return std::cos(CNodes.at(0)->dEvaluate(pcVarMap, pbDivByZero));
		}
	}

	if (eType == var && pcVarMap.find(sVal) != pcVarMap.cend()) {
		return pcVarMap.at(sVal);
	}

	return i_defaultVal;
}

void CNode::vAddAllVarsToVec(std::vector<std::string>& pcVars) {
	if (eType == var) {
		pcVars.push_back(sVal);
	} 

	else if (eType == oper) {
		for (int i = 0; i < CNodes.size(); i++) {
			CNodes.at(i)->vAddAllVarsToVec(pcVars);
		}
	}
}

void CNode::vReplaceLastNode(CNode& pcOther) {
	if (eType != oper) {
		*this = pcOther;
		return;
	}

	CNode* pcNode = this;
	int iVecSize = (*pcNode).CNodes.size();

	while ((*pcNode).CNodes.at(iVecSize - 1)->eType == oper) {
		pcNode = (*pcNode).CNodes.at(iVecSize - 1);
		iVecSize = (*pcNode).CNodes.size();
	}

	(*pcNode).CNodes.at(iVecSize - 1) = new CNode(pcOther);
}

void CNode::vPrefix(std::stringstream& pcSs) {
	pcSs << sVal << " ";
	if (eType == oper) {
		for (int i = 0; i < CNodes.size(); i++) {
			CNodes.at(i)->vPrefix(pcSs);
		}
	}
}
