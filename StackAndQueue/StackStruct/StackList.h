/*栈结构，链表式*/
#ifndef STACKLIST_H
#define STACKLIST_H
#include<iostream>
#include"D:\Project\project\DataStructure\ListStruct\ListLink\ListLinkEXP.h"
#define MAXList 20;
using namespace std;
template<typename T>class ListStructExp;
template<typename T>class ListLinkExp;


template<typename T>
class StackNode{
private:
    T data;//数据
    StackNode<T>*next;//链表指针
public: 
    //构造函数
    StackNode(){data=this->data;next=this;};
    //返回数据元素
    T GetData(){return data;};
    //修改数据元素
    void SetData(const T&data){this->data=data;};
    //返回当前结点
    StackNode<T>*NextNode(){return this->next;};
    //将数据插入到当前结点的后面
    void InsertNode(StackNode<T>*p){
        StackNode<T>*cur=this->next;//让cur指向要插入结点的下一个结点
        this->next=p;//让当前结点的下一个结点为p
        p->next=cur;//让p成为当前结点原来后继的前驱
        cur=NULL;
    } 
    StackNode<T>* DeleteNode(void){
        StackNode<T>*p=this->next;//让p指向当前结点的下一个结点（即要删除的结点）
        this->next=p->next;//让当前结点指向p结点的下一个结点（即当前结点指向要删除的结点的下一个结点）
        return p;//返回要删除的结点(即当前结点的下一个结点)
    }
    //修改结点指针为空
    void SetNext(){next=NULL;};
};

template<typename T>
class StackList
{
private:
    StackNode<T>*top;//栈顶指针
    StackNode<T>*curPtr;//栈底指针
    int size;//链表大小
public:

    StackList(/* args */);
    ~StackList();

    //入栈
    void ListPush(T item);
    //出栈
    void ListPop();
    //清栈
    void ClearStack();
    //打印栈
    void PrintStack();
    //取栈顶元素
    T GetTop(){return top->GetData();};
    //判空
    bool IsEmpty(){return (size==0);};
};
//构造函数
template<typename T>
StackList<T>::StackList(){
    curPtr=top=new StackNode<T>();
    top->NextNode()->SetNext();
    size=0;
}
//入栈,(链表使用头插法)
template<typename T>
void StackList<T>::ListPush(T item){
    top=curPtr;
    StackNode<T>*newNode=new StackNode<T>();
    newNode->SetData(item);
    top->InsertNode(newNode);
    size++;
    top=curPtr->NextNode();
}
//出栈
template<typename T>
void StackList<T>::ListPop(){
    if(size==0)return ;//空栈，无法删除
    top=curPtr;
    StackNode<T>*p=top->NextNode()->NextNode();
    delete(top->DeleteNode());
    top=p;
    size--;
}
//清栈
template<typename T>
void StackList<T>::ClearStack(){
    top=curPtr;
    while(size!=0){
        ListPop();
    }
}
template<typename T>
StackList<T>::~StackList(){
    ClearStack();
    delete curPtr;
    curPtr=NULL;
    top=NULL;
}
template<typename T>
void StackList<T>::PrintStack(){
    top=curPtr->NextNode();
    while(top!=NULL){
        cout<<top->GetData()<<" ";
        top=top->NextNode();
    }
    top=curPtr;
    cout<<endl;
}


#endif