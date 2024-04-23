#pragma once
#include "Imports.h"
#include "CTree.h"
#include "CRefCounter.h"

template <typename T> class CSmartPointer
{
private:
	CRefCounter* pcRefCounter;
	T* pcPointer;

public:
	CSmartPointer(T* pcOther);
	CSmartPointer(const CSmartPointer& pcOther);
	~CSmartPointer();

	void operator=(const CSmartPointer<T>& pcOther);
	T& operator*();
	T* operator->();

	CSmartPointer cDuplicate();
};
