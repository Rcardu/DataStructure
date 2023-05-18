#ifndef USING_H
#define USING_H
#include<iostream>
#include"ListNode.h"
#endif
using namespace std;
void UseListFormat();

void UseListFormat(){
    ListNodeSq<int>s;
    int tmp;
    s.Init_ListNodeSq();
    s.insert(2);
    s.insert(3);
    s.insert(2,5);
    s.traverse(print);
    s.remove(4, tmp);
    s.traverse(print);
}
