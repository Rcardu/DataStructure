#ifndef USDOUBLE_H
#define USDOUBLE_H
#include<iostream>
#include"DoubleList.h"
using namespace std;
void UsDoubleFormat();

void UsDoubleFormat(){
    DoubleList<int>s;
    int N[6]={1,5,3,6,7,8};
    for(int i=0;i<6;i++)s.InsertFront(N[i]);
    s.PrintList();

}



#endif