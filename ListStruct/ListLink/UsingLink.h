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
    ListLinkExp<int>DA,DB,DC;
    int N,M;
    cin>>N>>M;
    vector<float>Coefa(N);
    vector<int>Expa(N);
    for(int i=0;i<N;i++)cin>>Coefa[i];
    for(int i=0;i<N;i++)cin>>Expa[i];
    for(int i=0;i<N;i++)DB.InsertAfter(Coefa[i],Expa[i]);
    vector<float>Coefb(M);
    vector<int>Expb(M);
    for(int i=0;i<M;i++)cin>>Coefb[i];
    for(int i=0;i<M;i++)cin>>Expb[i];
    for(int i=0;i<M;i++)DA.InsertAfter(Coefb[i],Expb[i]);
    ListLinkUS<int>obj;
    obj.DAandDBcom(DA,DB,DC);
    DC.PrintList();
    
}

#endif