#pragma once
#include "Imports.h"

const char* const pc_operators[] = {"+", "-", "*", "/", "sin", "cos"};
const char* const pc_opersWithOneArg[] = {"sin", "cos"};
const char* const pc_opersWithTwoArgs[] = {"+", "-", "*", "/"};
const int i_numOfOpers = 6;
const int i_numOfOpersWithTwoArgs = 4;
const int i_numOfOpersWithOneArg = 2;

bool isNumber(std::string& psStr);
bool isOper(std::string& psStr);
int iArgNumOfOper(std::string& psOper);
std::string sGetNextWord(std::string& psStr, int* piIdx);
void vConvertToUppercase(std::string& psStr);
std::string sRemoveFirstNLetters(std::string& psStr, int iOff);
void vRemoveDuplicatesFromVec(std::vector<std::string>& pcVec);