#include<iostream>
#include"ListNode.h"
#include<algorithm>
#include<vector>
#include"UsListNodeSq.h"

using namespace std;
void UseListFormat();

void UseListFormat(){
    vector<ListNodeSq<int>>s(2);
    s[0].Init_ListNodeSq();
    s[1].Init_ListNodeSq();
    int N,M;
    cin>>N>>M;
    vector<int>slist(N);
    vector<int>tlist(M);
    for(int i=0;i<N;i++)cin>>slist[i];
    for(int i=0;i<M;i++)cin>>tlist[i];
    for(int i=0;i<slist.size();i++)s[0].insert(slist[i]);
    for(int i=0;i<tlist.size();i++)s[1].insert(tlist[i]);
    UsListNodeSq<int>obj;
    obj.CopyUnside(s[0],s[1]); 
    s[0].traverse(print);
}
