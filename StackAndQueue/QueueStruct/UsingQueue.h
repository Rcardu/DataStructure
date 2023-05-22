#ifndef USINGQUEUE_H
#define USINGQUEUE_H
#include<iostream>
#include<vector>
#include"QueueStruct.h"
#include"QueueDouble.h"
using namespace std;

void usQueueStrcutFormat();
void UsQueueDoubleFormat();

void usQueueStrcutFormat(){
    QueueStruct<int>obj;
    obj.CreatQueue();
    obj.PrintQueue();
    obj.PopQueueDataDe();
    obj.PrintQueue();
    obj.PushQueue(8);
    obj.PrintQueue();
    cout<<obj.PopQueueData()<<endl;
    obj.PrintQueue();
}
void UsQueueDoubleFormat(){
    DoubleNodes<int>obj;
    int N;
    cin>>N;
    int i,j,k=0;
    int temp,x;
    obj.PushQueue(1);
    for(i=2;i<=N;i++){
        for(k=1;k<=40-(i-2)*2;k++){
            cout<<" ";
        }
        obj.PushQueue(1);
        for(j=1;j<=i-2;j++){
            temp=obj.PopQueueDataDe();
            cout<<temp<<" ";
            x=obj.PopQueueData();
            temp=temp+x;
            obj.PushQueue(temp);
        }
        temp=obj.PopQueueDataDe();
        cout<<temp<<endl;
        obj.PushQueue(1);

    }
    for(k=1;k<=40-(N-1)*2;k++)cout<<" ";
    for(i=1;i<=N;i++){
        cout<<obj.PopQueueDataDe()<<" ";
    }
    cout<<endl;


}


#endif