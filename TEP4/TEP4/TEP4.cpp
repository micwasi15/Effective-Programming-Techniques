#include "CInterface.h"
#include "CSmartPointer.h"

int main() {
    CInterface CI;
    CI.vRun();

    int* i = new int(5);
    CSmartPointer<int> CSP1(i);
    CSmartPointer<int> CSP2 = CSP1.cDuplicate();
    std::cout << *CSP2;

    /*int a = 2;
    CSmartPointer<int> CSP3(&a);*/
}