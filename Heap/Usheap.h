#ifndef USHEAP_H
#define USHEAP_H
#include"..//utils//common.hpp"
#include"heap.h"
#include"heapCreat.h"
using namespace std;
void Useings();
void UsCreat();

void Useings(){
    test1();
}
void UsCreat(){
    /*初始化大堆顶*/
    vector<int>vec{9,8,6,6,7,5,2,1,4,3,6,2};
    HeapMax maxHeap(vec);
    cout<<"\n输入数组并建堆后 "<<endl;
    maxHeap.print();

    /*获取堆顶元素*/
    int peek=maxHeap.peek();
    cout<<"\n堆顶元素为: "<<peek<<endl;

    /*元素入堆*/
    maxHeap.push(7);
    cout<<"\n元素"<<7<<"入堆后: "<<endl;
    maxHeap.print();

    /*元素出堆*/
    peek=maxHeap.peek();
    maxHeap.pop();
    cout<<"\n堆顶元素 "<<peek<<"出堆后 "<<endl;
    maxHeap.print();

    /*获取堆大小*/
    cout<<"当前堆大小为："<<maxHeap.size()<<endl;

    /*判断当前堆是否为空*/
    cout<<"当前堆是否为空:  "<<maxHeap.empty()<<endl;
}



#endif