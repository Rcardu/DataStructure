#ifndef USINGLINK_H
#define USINGLINK_H
#include<iostream>
#include<vector>
#include"ListLink.h"
#include"ListLinkUS.h"
using namespace std;
void UsListLinkFormat();

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



#endif