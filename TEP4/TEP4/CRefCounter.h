#pragma once
class CRefCounter
{
private:
	int iCount;

public:
	CRefCounter();

	int iAdd();
	int iDec();
	int iGet();
};

