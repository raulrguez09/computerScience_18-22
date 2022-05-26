#include<iostream>

#include "ArrayProc.hpp"
#include "Functions.hpp"

using namespace std;
 
int main()
{
    int c;
    double n[MAX];

    cout<<"La operacion que se realizara es: (A[i]+A[j])*A[k] "<<endl;

    c= readNumElem ();
    readVectorElements (c,n);
    showVectorElements (c,n);
    choiceElemExpr (c,n);
}
