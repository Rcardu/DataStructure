#ifndef USINGLINK_H
#define USINGLINK_H
#include<iostream>
#include<vector>
#include"ListLink.h"
#include"ListLinkUS.h"
#include"ListLinkEXP.h"
using namespace std;
void UsListLinkFormat();
void UsListLinkExpFotmat();

void UsListLinkFormat(){
    ListLink<int>LA,LB,LC;
    LA.CreateList();
    LB.CreateList();
    //LA.SortALL();
    //LB.SortALL();
    LA.PrintList();
    LB.PrintList();
    ListLinkUS<int>obj;
    //obj.LinkList_Unionlist(LA,LB,LC);
    //obj.LAandLBfost(LA,LB,LC);
    //LC.PrintList();
    obj.LAinterLB(LA,LB,LC);
    LC.PrintList();
}
void UsListLinkExpFotmat(){
    ListLinkExp<int>L;
    int N;
    cin>>N;
    vector<float>Coefs(N);
    vector<int>Exps(N);
    for(int i=0;i<N;i++)cin>>Coefs[i];
    for(int i=0;i<N;i++)cin>>Exps[i];
    for(int i=0;i<N;i++)L.InsertAfter(Coefs[i],Exps[i]);
    L.SortListExp();
    L.PrintList();
    
}

#endif