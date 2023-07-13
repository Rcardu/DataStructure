#include"SkipList.h"
#include<iostream>
using namespace std;




int main(){
    int maxLevel=6;
    SkipList<int>l(maxLevel,0);
    for(int i=0;i<15;i++){
        l.insert(i,i);
    }
    l.printNode();
    while(getchar()!='\n')
    continue;
    getchar();

    return 0;
}