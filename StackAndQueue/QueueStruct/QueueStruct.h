/*队列的定义*/
#ifndef QUEUESTRUCT_H
#define QUQUESTRUCT_H
#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class QueueNode{
private:
    T data;//数据
    QueueNode<T>*next;//指针
public:
    QueueNode(){data=this->data;next=this;};
    //获得下一个指针
    QueueNode<T>* NextNode(){return this->next;};
    //获得数据
    T GetData(){return this->data;};
    //修改数据元素
    void SetData(T data){this->data=data;};
    //插入数据
    void InsertNode(QueueNode<T>*p){
        QueueNode<T>*cur=NULL;
        this->next=p;
        p->next=cur;
    }
    //删除数据
    QueueNode<T>* DeleteNode(){
        QueueNode<T>*p=this->next;
        this->next=this->next->next;
        return p;//返回被删除的结点
    }
    //设置指针为空
    void SetNext(){next=NULL;};
};
template<typename T>
class QueueStruct{
private:
    QueueNode<T>*front;//队头指针
    QueueNode<T>*rear;//队尾指针
    int length;
    void CopyQueue(QueueStruct<T>&L);//拷贝L到当前表尾
public:
    QueueStruct();//构造函数
    QueueStruct(QueueStruct<T>&L);//拷贝构造函数
    ~QueueStruct();//析构

    void PushQueue(T data);//入队
    void CreatQueue();//创建队列(int 型)

    T PopQueueDataDe();//出队，并返回其数据
    T PopQueueData();//获得队首元素
    void PopQueue();//出队
    void DeleteQueue();//销毁队列

    bool EmptyQueue();//队列是否为空
    void PrintQueue();//打印当前队列
};
template<typename T>
QueueStruct<T>::QueueStruct(){
    rear=front=new QueueNode<T>();
    front->NextNode()->SetNext();
    length=0;
}
template<typename T>
QueueStruct<T>::QueueStruct(QueueStruct<T>&L){
    front=new QueueNode<T>();
    front->NextNode()->SetNext();
    length=0;
    CopyQueue(L);
}
template<typename T>
QueueStruct<T>::~QueueStruct(){
    while(!EmptyQueue()){
        DeleteQueue();
    }
    delete front;
    front=NULL;
    rear=NULL;
}
template<typename T>
void QueueStruct<T>::CopyQueue(QueueStruct<T>&L){
    QueueNode<T>*p=L.front->NextNode();
    while(p!=L.rear->NextNode()){
        PushQueue(p->GetData());
    }
}
template<typename T>
void QueueStruct<T>::PushQueue(T data){
    QueueNode<T>*newNode=new QueueNode<T>();
    newNode->SetData(data);
    rear->InsertNode(newNode);
    rear=rear->NextNode();
    length++;
}
template<typename T>
void QueueStruct<T>::CreatQueue(){
    int N;
    cin>>N;
    vector<int>create(N);
    for(int i=0;i<N;i++)cin>>create[i];
    for(int i=0;i<N;i++)PushQueue(create[i]);
}
template<typename T>
T QueueStruct<T>::PopQueueDataDe(){
    if(EmptyQueue())return false;
    T item=front->NextNode()->GetData();
    PopQueue();
    return item;
}
template<typename T>
T QueueStruct<T>::PopQueueData(){
    if(EmptyQueue())return false;
    return front->NextNode()->GetData();
}
template<typename T>
void QueueStruct<T>::PopQueue(){
    if(EmptyQueue())return ;
    QueueNode<T>*p=front;
    delete(p->DeleteNode());
    length--;
}
template<typename T>
void QueueStruct<T>::DeleteQueue(){
    while(front->NextNode()!=rear){
        PopQueue();
    }
    PopQueue();
}
template<typename T>
bool QueueStruct<T>::EmptyQueue(){
    return (length==0);
}
template<typename T>
void QueueStruct<T>::PrintQueue(){
    QueueNode<T>*p=front->NextNode();
    while(p!=NULL){
        cout<<p->GetData()<<" ";
        p=p->NextNode();
    }
    cout<<endl;
}




#endif