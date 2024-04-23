#pragma once
#include "Imports.h"

const char* const pc_operators[] = { "+", "-", "*", "/", "sin", "cos" };
const char* const pc_opersWithOneArg[] = { "sin", "cos" };
const char* const pc_opersWithTwoArgs[] = { "+", "-", "*", "/" };
const int i_numOfOpers = 6;
const int i_numOfOpersWithTwoArgs = 4;
const int i_numOfOpersWithOneArg = 2;

const char* const pc_strOpers[] = {"+" , "-", "*", "/"};
const char* const pc_strOpersWithTwoArgs[] = { "+", "-", "*", "/" };
const int i_numOfStrOpers = 4;
const int i_numOfStrOpersWithTwoArgs = 4;

const char* const pc_boolOpers[] = { "+" , "-", "*", "/" };
const char* const pc_boolOpersWithZeroArgs[] = { "-", "/" };
const char* const pc_boolOpersWithTwoArgs[] = { "+", "*" };
const int i_numOfBoolOpers = 4;
const int i_numOfBoolOpersWithZeroArgs = 2;
const int i_numOfBoolOpersWithTwoArgs = 2;


bool bIsNumber(std::string& psStr);
bool bIsFloat(std::string& psStr);

bool bIsNumOper(std::string& psStr);
bool bIsStringOper(std::string& psStr);

int iArgNumOfOper(std::string& psOper);
int iArgNumOfOperStr(std::string& psOper);

std::string sGetNextWord(std::string& psStr, int* piIdx);
std::string sGetNextWordStr(std::string& psStr, int* piIdx);
void vConvertToUppercase(std::string& psStr);
void vConvertToLowercase(std::string& psStr);
std::string sRemoveFirstNLetters(std::string& psStr, int iOff);
void vRemoveDuplicatesFromVec(std::vector<std::string>& pcVec);
void vCopyElemsFromVec(std::vector<std::string>& pcVecRes, const std::vector<std::string>& pcVecCopy);
