#ifndef USDOUBLE_H
#define USDOUBLE_H
#include<iostream>
#include"DoubleList.h"
using namespace std;
void UsDoubleFormat();

void UsDoubleFormat(){
    DoubleList<int>s;
    int N;
    cin>>N;
    for(int i=0;i<N;i++)s.InsertAfter(i+1);
    s.PrintList();
    /*约瑟夫环问题
    cout<<endl;
    int k,m;
    cin>>k;
    s.ResetsPtr();
    s.GetNode(k);
    cin>>m;
    while(!s.ListEmpty()){
        s.GetNode(m);
        cout<<s.Data()<<" ";
        s.DeleteAt();
    }
    */
}



#endif