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
    /*��ʼ����Ѷ�*/
    vector<int>vec{9,8,6,6,7,5,2,1,4,3,6,2};
    HeapMax maxHeap(vec);
    cout<<"\n�������鲢���Ѻ� "<<endl;
    maxHeap.print();

    /*��ȡ�Ѷ�Ԫ��*/
    int peek=maxHeap.peek();
    cout<<"\n�Ѷ�Ԫ��Ϊ: "<<peek<<endl;

    /*Ԫ�����*/
    maxHeap.push(7);
    cout<<"\nԪ��"<<7<<"��Ѻ�: "<<endl;
    maxHeap.print();

    /*Ԫ�س���*/
    peek=maxHeap.peek();
    maxHeap.pop();
    cout<<"\n�Ѷ�Ԫ�� "<<peek<<"���Ѻ� "<<endl;
    maxHeap.print();

    /*��ȡ�Ѵ�С*/
    cout<<"��ǰ�Ѵ�СΪ��"<<maxHeap.size()<<endl;

    /*�жϵ�ǰ���Ƿ�Ϊ��*/
    cout<<"��ǰ���Ƿ�Ϊ��:  "<<maxHeap.empty()<<endl;
}



#endif