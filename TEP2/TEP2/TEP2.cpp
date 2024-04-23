#include <iostream>
#include "CNumber.h"

int main()
{
	CNumber* pcFirNum = new CNumber(123);
	CNumber* pcSecNum = new CNumber(-3);
	CNumber CRes;
	CRes = 10;
	std::cout << CRes.sToStr() << std::endl;
	CRes = *pcFirNum;
	std::cout << CRes.sToStr() << std::endl;
	CRes = (CRes + CRes);
	std::cout << CRes.sToStr() << std::endl;
	CRes = CRes + 3;
	std::cout << CRes.sToStr() << std::endl;
	CRes = CRes + (-3);
	std::cout << CRes.sToStr() << std::endl << std::endl;

	CRes = (*pcFirNum) - (*pcSecNum);
	std::cout << CRes.sToStr() << std::endl;
	CRes = CRes - CRes;
	std::cout << CRes.sToStr() << std::endl;
	CRes = 5;
	CRes = CRes - 8;
	std::cout << CRes.sToStr() << std::endl << std::endl;

	CRes = (*pcFirNum) * (*pcSecNum);
	//CRes = 31;
	//CRes = CRes * CRes;
	std::cout << CRes.sToStr() << std::endl;
	CRes = 31;
	CRes = CRes * 21;
	std::cout << CRes.sToStr() << std::endl;
	CRes = CRes * (-2);
	std::cout << CRes.sToStr() << std::endl << std::endl;

	CRes = (*pcFirNum) / (*pcSecNum);
	std::cout << CRes.sToStr() << std::endl;
	CRes = 432;
	CRes = CRes / 101;
	std::cout << CRes.sToStr() << std::endl << std::endl;

	//*pcFirNum = NULL;
	//*pcSecNum = NULL;
	//CRes = (*pcFirNum) + (*pcSecNum);
	//std::cout << CRes.sToStr() << std::endl;

	CRes = 100;
	*pcFirNum = 51;
	CRes = CRes.cMod(*pcFirNum, &pcSecNum);
	std::cout << CRes.sToStr() << std::endl;

	delete pcSecNum;
	delete pcFirNum;
}
