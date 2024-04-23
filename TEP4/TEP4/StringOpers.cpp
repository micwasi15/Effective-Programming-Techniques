#include "StringOpers.h"

void KLM(std::string& psPat, std::string psStr, std::vector<int>& pvRes) {
	if (psPat.empty()) {
		return;
	}

	int i = 0;
	int j = 0;
	int* piLps = new int[psPat.size()];
	piLps[0] = 0;

	for (int i = 1; i < psPat.size(); i++) {
		while (j > 0 && psPat[j] != psPat[i]) {
			j = piLps[j - 1];
		}
		if (psPat[j] == psPat[i]) {
			j++;
		}
		piLps[i] = j;
	}

	j = 0;
	while (i < psStr.size()) {
		while (j > 0 && psPat[j] != psStr[i]) {
			j = piLps[j - 1];
		}
		if (psPat[j] == psStr[i]) {
			j++;
		}
		if (j == psPat.size()) {
			pvRes.push_back(i - j + 1);
			j = piLps[j - 1];
		}
		i++;
	}

	delete[] piLps;
}

std::string sAdd(std::string& psStr1, std::string& psStr2) {
	return psStr1 + psStr2;
}

std::string sSub(std::string& psStr1, std::string& psStr2) {
	std::vector<int> vOff;
	KLM(psStr2, psStr1, vOff);

	if (vOff.empty()) {
		return psStr1;
	}

	std::stringstream CSs;

	for (int i = 0; i < psStr1.size(); i++) {
		if (i == vOff.back()) {
			i += psStr2.size() - 1;
		}
		else {
			CSs << psStr1[i];
		}
	}

	return CSs.str();
}

std::string sMul(std::string& psStr1, std::string& psStr2) {
	std::vector<int> vOff;
	std::string sFirstChar = !psStr2.empty() ? psStr2.substr(0, 1) : "";
	KLM(sFirstChar, psStr1, vOff);

	if (vOff.empty()) {
		return psStr1;
	}

	std::stringstream CSs;
	int iOffIdx = 0;

	for (int i = 0; i < psStr1.size(); i++) {
		if (i == vOff.at(iOffIdx)) {
			CSs << psStr2;
			if (iOffIdx < vOff.size() - 1) {
				iOffIdx++;
			}
		}
		else {
			CSs << psStr1[i];
		}
	}

	return CSs.str();
}

std::string sDiv(std::string& psStr1, std::string& psStr2) {
	std::vector<int> vOff;
	KLM(psStr2, psStr1, vOff);

	if (vOff.empty()) {
		return psStr1;
	}

	std::stringstream CSs;
	int iOffIdx = 0;

	for (int i = 0; i < psStr1.size(); i++) {
		CSs << psStr1[i];

		if (i == vOff.at(iOffIdx)) {
			i += psStr2.size() - 1;
			if (iOffIdx < vOff.size() - 1) {
				iOffIdx++;
			}
		}
	}

	return CSs.str();
}