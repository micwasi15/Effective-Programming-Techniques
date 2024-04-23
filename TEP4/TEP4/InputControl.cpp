#include "InputControl.h"

bool bIsNumber(std::string& psStr) {
    if (psStr.empty()) {
        return 0;
    }

    for (char ch : psStr) {
        if (!std::isdigit(ch)) {
            return 0;
        }
    }

    return 1;
}

bool bIsFloat(std::string& psStr) {
    if (psStr.empty()) {
		return 0;
	}

	bool bIsDot = 0;
    for (char ch : psStr) {
        if (ch == '.') {
            if (bIsDot) {
				return 0;
			}
			bIsDot = 1;
		}
        else if (!std::isdigit(ch)) {
			return 0;
		}
	}

	return 1;
}

bool bIsNumOper(std::string& psStr) {
    for (int i = 0; i < i_numOfOpers; i++) {
        if (psStr == pc_operators[i]) {
            return 1;
        }
    }

    return 0;
}

bool bIsStringOper(std::string& psStr) {
    for (int i = 0; i < i_numOfStrOpers; i++) {
        if (psStr == pc_strOpers[i]) {
			return 1;
		}
	}

	return 0;
}

int iArgNumOfOper(std::string& psOper) {
    for (int i = 0; i < i_numOfOpersWithOneArg; i++) {
        if (pc_opersWithOneArg[i] == psOper) {
            return 1;
        }
    }

    for (int i = 0; i < i_numOfOpersWithTwoArgs; i++) {
        if (pc_opersWithTwoArgs[i] == psOper) {
            return 2;
        }
    }

    return 0;
}

int iArgNumOfOperStr(std::string& psOper) {
    return 2;
}

std::string sGetNextWord(std::string& psStr, int* piIdx) {
    std::stringstream CSs;
    
    while ((*piIdx) < psStr.length() && psStr.at(*piIdx) == ' ') {
        (*piIdx)++;
    }

    while ((*piIdx) < psStr.length() && psStr.at(*piIdx) != ' ') {
        CSs << psStr.at(*piIdx);
        (*piIdx)++;
    }

    return CSs.str();
}

std::string sGetNextWordStr(std::string& psStr, int* piIdx) {
	std::stringstream CSs;

    while ((*piIdx) < psStr.length() && psStr.at(*piIdx) == ' ') {
		(*piIdx)++;
	}

    bool bVal = psStr[*piIdx] == '\"';

    if (bVal) {
        CSs << psStr.at(*piIdx);
		(*piIdx)++;
    }

    while ((*piIdx) < psStr.length() && (psStr.at(*piIdx) != ' ' || bVal)) {
        if (psStr.at(*piIdx) == '\"') {
			bVal = 0;
		}
		CSs << psStr.at(*piIdx);
		(*piIdx)++;
	}

    std::string sRes = CSs.str();
    if (sRes.size() > 1 && sRes[0] == '\"' && sRes[sRes.size() - 1] != '\"') {
		CSs << '\"';
        return CSs.str();
	}

    return sRes;
}   

void vConvertToUppercase(std::string& psStr) {
    for (char& ch : psStr) {
        ch = std::toupper(ch);
    }
}

void vConvertToLowercase(std::string& psStr) {
    for (char& ch : psStr) {
		ch = std::tolower(ch);
	}
}

std::string sRemoveFirstNLetters(std::string& psStr, int iOff) {
    if (iOff >= psStr.length()) {
        return "";
    }

    return psStr.substr(iOff);
}

void vRemoveDuplicatesFromVec(std::vector<std::string>& pcVec) {
    std::vector<std::string> CRes;
    std::set<std::string> CHs;

    for (std::string sElem : pcVec) {
        if (CHs.find(sElem) == CHs.cend()) {
            CRes.push_back(sElem);
            CHs.insert(sElem);
        }
    }

    pcVec = CRes;
}

void vCopyElemsFromVec(std::vector<std::string>& pcVecRes, const std::vector<std::string>& pcVecCopy) {
    for (int i = 0; i < pcVecCopy.size(); i++) {
        pcVecRes.push_back(pcVecCopy.at(1));
    }
}
