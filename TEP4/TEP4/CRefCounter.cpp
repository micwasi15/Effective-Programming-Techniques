#include "CRefCounter.h"

CRefCounter::CRefCounter() {
	iCount = 0;
}

int CRefCounter::iAdd() {
	return (++iCount);
}

int CRefCounter::iDec() {
	return (--iCount);
}

int CRefCounter::iGet() {
	return iCount;
}