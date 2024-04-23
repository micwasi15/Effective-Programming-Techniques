#include "CInterface.h"
#include "InputControl.h"

void CInterface::vShowMenu() {
	std::cout << s_initMenuMsg;
	std::cout << s_menuMsgEnd;
	std::cout << s_menuMsgEnter;
	std::cout << s_menuMsgVars;
	std::cout << s_menuMsgPrint;
	std::cout << s_menuMsgComp;
	std::cout << s_menuMsgJoin;
	std::cout << std::endl;
}

void CInterface::vRun() {
	bool bRunning = 1;
	std::string sInput;
	std::string sCommand;
	int* piIdx = new int;
	CTree CT;

	while (bRunning) {
		*piIdx = 0;
		vShowMenu();

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

void CInterface::vEnter(std::string& psFormula, CTree& pcT) {
	std::stringstream CSsErrorMsg;
	pcT = CTree(psFormula, CSsErrorMsg);

	if (!CSsErrorMsg.str().empty()) {
		std::cout << CSsErrorMsg.str() << std::endl;
		std::cout << s_invalidFormulaErrMsg;
		vPrint(pcT);
	}
	else {
		std::cout << s_createTreeSucMsg;
	}
}

void CInterface::vVars(CTree& pcT) {
	std::cout << pcT.sVars() << std::endl;
}

void CInterface::vPrint(CTree& pcT) {
	std::cout << pcT.sToStrPrefix() << std::endl;
}

void CInterface::vComp(std::string& psVars, CTree& pcT) {
	std::stringstream CSsErrorMsg;
	double dRes = pcT.dComp(psVars, CSsErrorMsg);

	if (!CSsErrorMsg.str().empty()) {
		std::cout << CSsErrorMsg.str();
	}

	std::cout << s_resultMsg << dRes << std::endl;
}

void CInterface::vJoin(std::string& psFormula, CTree& pcT) {
	std::stringstream CSsErrorMsg;
	CTree CTemp = CTree(psFormula, CSsErrorMsg);
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