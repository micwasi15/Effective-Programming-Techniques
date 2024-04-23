#include "BoolOpers.h"

bool bAdd(bool& pbBool1, bool& pbBool2) {
	return pbBool1 || pbBool2;
}

bool bSub(bool& pbBool1, bool& pbBool2) {
	return !pbBool1;
}

bool bMul(bool& pbBool1, bool& pbBool2) {
	return pbBool1 && pbBool2;
}

bool bDiv(bool& pbBool1, bool& pbBool2) {
	return !pbBool2;
}
