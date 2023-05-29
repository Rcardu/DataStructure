#ifndef HEAP_H
#define HEAP_H
#include"..//utils//common.hpp"
void testPush(priority_queue<int>&heap,int val){
    heap.push(val);
    cout<<endl;
    printHeap(heap);
}
void testPop(priority_queue<int>&heap){
    int val=heap.top();
    heap.pop();
    cout<<endl;
    printHeap(heap);
}

void test1(){
    priority_queue<int,vector<int>,less<int>>maxHeap;

    cout<<endl;

    testPush(maxHeap,1);
    testPush(maxHeap,3);
    testPush(maxHeap,2);
    testPush(maxHeap,4);
    testPush(maxHeap,5);

    int tops=maxHeap.top();
    cout<<tops<<endl;

    testPop(maxHeap);
    testPop(maxHeap);
    testPop(maxHeap);
    testPop(maxHeap);
    testPop(maxHeap);

    vector<int>input={1,3,2,4,5};
    priority_queue<int,vector<int>,greater<int>>minHape(input.begin(),input.end());
    printHeap(minHape);
}





#endif