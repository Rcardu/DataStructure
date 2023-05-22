#ifndef QUEUEDOUBLE_H
#define QUEUEDOUBLE_H
#include<iostream>
#include<vector>
#define MAXDOUBLE 20
using namespace std;
template<typename T>
class DoubleNodes{
private:
    T elem[MAXDOUBLE];
    int front;
    int rear;
public:
    DoubleNodes(){front=0;rear=0;};

    void PushQueue(T item);//入队
    void PopQueue();//出队
    T PopQueueData();//返回队首元素
    T PopQueueDataDe();//出队，并返回队首元素

    void PrintQueue();//打印当前队列
};
template<typename T>
void DoubleNodes<T>::PushQueue(T item){
    this->elem[rear]=item;
    rear=(rear+1)%MAXDOUBLE;
}
template<typename T>
void DoubleNodes<T>::PopQueue(){
    front=(front+1)%MAXDOUBLE;
}
template<typename T>
T DoubleNodes<T>::PopQueueDataDe(){
    T item=elem[front];
    front=(front+1)%MAXDOUBLE;
    return item;
}
template<typename T>
T DoubleNodes<T>::PopQueueData(){
    return this->elem[front];
}
template<typename T>
void DoubleNodes<T>::PrintQueue(){
    if(front==rear)return;
    for(int idx=front;idx<=rear;idx++)cout<<elem[idx]<<" ";
    cout<<endl;
}






#endif