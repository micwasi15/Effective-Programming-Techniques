#include "CSmartPointer.h"

template <typename T> CSmartPointer<T>::CSmartPointer(T* pcOther) {
	pcPointer = pcOther;
	pcRefCounter = new CRefCounter();
	pcRefCounter->iAdd();
}

template <typename T> CSmartPointer<T>::CSmartPointer(const CSmartPointer<T>& pcOther) {
	pcPointer = pcOther.pcPointer;
	pcRefCounter = pcOther.pcRefCounter;
	pcRefCounter->iAdd();
}

template <typename T> CSmartPointer<T>::~CSmartPointer() {
	if (pcRefCounter->iDec() == 0) {
		delete pcPointer;
		delete pcRefCounter;
	}
}

template <typename T> T& CSmartPointer<T>::operator*() {
	return (*pcPointer);
}

template <typename T> T* CSmartPointer<T>::operator->() {
	return pcPointer;
}

template <typename T> void CSmartPointer<T>::operator=(const CSmartPointer<T>& pcOther) {
	if (pcRefCounter->iDec() == 0) {
		delete pcPointer;
		delete pcRefCounter;
	}

	pcPointer = pcOther.pcPointer;
	pcRefCounter = pcOther.pcRefCounter;
	pcRefCounter->iAdd();
}

template <typename T> CSmartPointer<T> CSmartPointer<T>::cDuplicate() {
	return CSmartPointer(*this);
}

template class CSmartPointer<int>;
template class CSmartPointer<double>;
template class CSmartPointer<char>;
template class CSmartPointer<std::string>;
