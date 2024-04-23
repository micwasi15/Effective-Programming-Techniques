#include "CInterface.h"
#include "InputControl.h"

void CInterface::vShowMenu() {
	std::cout << s_initMenuMsg;
	std::cout << s_menuMsgCreateTree;

	for (int i = 0; i < i_numOfTypes; i++) {
		std::cout << pc_types[i] << " ";
	}

	std::cout << std::endl << s_menuMsgEnd;
}
void CInterface::vRun() {
	bool bRunning = 1;
	std::string sInput;
	std::string sCommand;
	std::string sType;
	int* piIdx = new int;

	while (bRunning) {
		*piIdx = 0;
		vShowMenu();

		std::getline(std::cin, sInput);
		sCommand = sGetNextWord(sInput, piIdx);
		vConvertToUppercase(sCommand);

		if (sCommand == s_endCom) {
			bRunning = 0;
		}
		else if (sCommand == s_createCom) {
			sType = sGetNextWord(sInput, piIdx);
			vConvertToLowercase(sType);

			bool bTypeError = 1;
			for (int i = 0; i < i_numOfTypes && bTypeError; i++) {
				if (sType == pc_types[i]) {
					bTypeError = 0;
				}
			}

			if (bTypeError) {
				std::cout << s_invalidCommandErr;
			}
			else {
				std::cout << std::endl;
				sInput = sRemoveFirstNLetters(sInput, *piIdx);
				vRunInner(sType);
			}
		}
		else {
			std::cout << s_invalidCommandErr;
		}
		std::cout << std::endl;
	}

	delete piIdx;
}

void CInterface::vRunInner(std::string& psType) {
	if (psType == s_intType) {
		CInnerInterface<int> CII;
		CII.vRun();
	}
	else if (psType == s_doubleType) {
		CInnerInterface<double> CII;
		CII.vRun();
	}
	else if (psType == s_stringType) {
		CInnerInterface<std::string> CII;
		CII.vRun();
	}
	else if (psType == s_boolType) {
		CInnerInterface<bool> CII;
		CII.vRun();
	}
	else {
		std::cout << s_invalidCommandErr;
	}
}

template <typename T> void CInnerInterface<T>::vShowInnerMenu() {
	std::cout << s_initMenuMsg;
	std::cout << s_menuMsgEnd;
	std::cout << s_menuMsgEnter;
	std::cout << s_menuMsgVars;
	std::cout << s_menuMsgPrint;
	std::cout << s_menuMsgComp;
	std::cout << s_menuMsgJoin;
	std::cout << std::endl;
}

template <typename T> void CInnerInterface<T>::vRun() {
	bool bRunning = 1;
	std::string sInput;
	std::string sCommand;
	int* piIdx = new int;
	CTree<T> CT;

	while (bRunning) {
		*piIdx = 0;
		vShowInnerMenu();

		std::getline(std::cin, sInput);
		sCommand = sGetNextWord(sInput, piIdx);
		vConvertToUppercase(sCommand);
		sInput = sRemoveFirstNLetters(sInput, *piIdx);

		if (sCommand == s_endCom) {
			bRunning = 0;
		}
		else if (sCommand == s_varsCom) {
			vVars(CT);
		}
		else if (sCommand == s_printCom) {
			vPrint(CT);
		}
		else if (sCommand == s_enterCom) {
			vEnter(sInput, CT);
		}
		else if (sCommand == s_compCom) {
			vComp(sInput, CT);
		}
		else if (sCommand == s_joinCom) {
			vJoin(sInput, CT);
		}
		else {
			std::cout << s_invalidCommandErr;
		}
		std::cout << std::endl;
	}

	delete piIdx;
}

template <typename T> void CInnerInterface<T>::vEnter(std::string& psFormula, CTree<T>& pcT) {
	std::stringstream CSsErrorMsg;

	pcT = CTree<T>(psFormula, CSsErrorMsg);

	if (!CSsErrorMsg.str().empty()) {
		std::cout << CSsErrorMsg.str() << std::endl;
		std::cout << s_invalidFormulaErrMsg;
		vPrint(pcT);
	}
	else {
		std::cout << s_createTreeSucMsg;
	}
}

template <typename T> void CInnerInterface<T>::vVars(CTree<T>& pcT) {
	std::stringstream CSsErrorMsg;
	std::string sVars = pcT.sVars(CSsErrorMsg);

	if (!CSsErrorMsg.str().empty()) {
		std::cout << CSsErrorMsg.str();
	}
	else {
		std::cout << sVars << std::endl;
	}
}

template <typename T> void CInnerInterface<T>::vPrint(CTree<T>& pcT) {
	std::cout << pcT.sToStrPrefix() << std::endl;
}

template <typename T> void CInnerInterface<T>::vComp(std::string& psVars, CTree<T>& pcT) {
	std::stringstream CSsErrorMsg;
	T tRes = pcT.tComp(psVars, CSsErrorMsg);

	if (!CSsErrorMsg.str().empty()) {
		std::cout << CSsErrorMsg.str();
	}

	std::cout << s_resultMsg << tRes << std::endl;
}

template <typename T> void CInnerInterface<T>::vJoin(std::string& psFormula, CTree<T>& pcT) {
	std::stringstream CSsErrorMsg;
	CTree<T> CTemp;

	CTemp = CTree<T>(psFormula, CSsErrorMsg);
	pcT = pcT + CTemp;

	if (!CSsErrorMsg.str().empty()) {
		std::cout << CSsErrorMsg.str() << std::endl;
		std::cout << s_invalidFormulaErrMsg;
		vPrint(pcT);
	}
	else {
		std::cout << s_joinSucMsg;
	}
}

template <> std::string CInnerInterface<std::string>::sGetTypeName() {
	return s_stringType;
}

template <> std::string CInnerInterface<int>::sGetTypeName() {
	return s_intType;
}

template <> std::string CInnerInterface<double>::sGetTypeName() {
	return s_doubleType;
}

template class CInnerInterface<int>;
template class CInnerInterface<double>;
template class CInnerInterface<std::string>;
template class CInnerInterface<bool>;
