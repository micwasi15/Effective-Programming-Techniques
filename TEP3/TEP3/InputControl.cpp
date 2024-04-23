#include "InputControl.h"

bool isNumber(std::string& psStr) {
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

bool isOper(std::string& psStr) {
    for (int i = 0; i < i_numOfOpers; i++) {
        if (psStr == pc_operators[i]) {
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

void vConvertToUppercase(std::string& psStr) {
    for (char& ch : psStr) {
        ch = std::toupper(ch);
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