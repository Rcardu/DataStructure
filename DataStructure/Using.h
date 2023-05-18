#include<iostream>
#include"ListNode.h"
#include<algorithm>
#include<vector>
#include"UsListNodeSq.h"

using namespace std;
void UseListFormat();

void UseListFormat(){
    ListNodeSq<int>s;
    s.Init_ListNodeSq();
    int N;
    cin>>N;
    vector<int>slist(N);
    for(int i=0;i<N;i++)cin>>slist[i];
    sort(slist.begin(),slist.end());
    for(int i=0;i<slist.size();i++)s.insert(slist[i]);
    UsListNodeSq<int>obj;
    obj.Insert(s,6); 
    s.traverse(print);
}
