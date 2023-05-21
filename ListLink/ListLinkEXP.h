#ifndef LISTLINKEXP_H
#define LISTLINKEXP_H
#include<iostream>
#include"ListLink.h"
using namespace std;
template<typename T>class ListLink;
template<typename T>
class ListStructExp{
private:
    float coef;//系数
    int exp;//指数
    ListStructExp<T>*next;//指针
public:
    //构造函数
    ListStructExp(){coef=this->coef;exp=this->exp;next=this;};
    //将数据插入到当前结点的后面
    void InsertNode(ListStructExp<T>*p){
        ListStructExp<T>*cur=this->next;//让cur指向要插入结点的下一个结点
        this->next=p;//让当前结点的下一个结点为p
        p->next=cur;//让p成为当前结点原来后继的前驱
        cur=NULL;
    }   
    //删除当前结的下一个结点并返回其地址
    ListStructExp<T>* DeleteNode(void){
        ListStructExp<T>*p=this->next;//让p指向当前结点的下一个结点（即要删除的结点）
        this->next=p->next;//让当前结点指向p结点的下一个结点（即当前结点指向要删除的结点的下一个结点）
        return p;//返回要删除的结点(即当前结点的下一个结点)
    }
    //取得下一个指针
    ListStructExp<T>*NextNode(void){return this->next;};
    //返回系数
    float ReCoef(){return coef;};
    //返回指数
    int ReExp(){return exp;};
    //修改系数
    void SetCoef(const float&coefs){this->coef=coefs;};
    //修改指数
    void SetExp(const int&exps){this->exp=exps;};
    //修改结点指针为空
    void SetNext(){next=NULL;};
};
template<typename T>
class ListLinkExp:public ListLink<T>{
private:
    ListStructExp<T>*head;//头指针
    ListStructExp<T>*curPtr;//指向当前结点的指针
    int length;
    void CopyList(const ListLinkExp<T>&L);//将表L拷贝到当前表尾
public:
    ListLinkExp();//构造函数
    ListLinkExp(const ListLinkExp<T>&L);//拷贝构造函数
    ~ListLinkExp();//析构函数

    //检查当前表的状态
    int ListLen();
    bool ListEmpty();

    //插入函数
    void InsertFront(const float&coefs,const int&exps);
    void InsertAfter(const float&coefs,const int&exps);
    void InsertIndex(const float&coefs,const int&exps,int idx);

    //删除函数
    void DeleteFront(void);
    void DeleteRear(void);
    void DeleteIndex(int idx);
    void DeleteThis(void);

    //调整curPtr指针位置
    void ResetcurPtr();
    //返回指定位置的结点(使curPtr指向指定节点)
    void ReNodeNext(int idx);
    //打印当前链表的数据
    void PrintList();
    //清空链表数据
    void ClearList();
    //排序，合并相同的指数
    void SortListExp();
    //交换当前结点和指定结点
    void SwipNode(ListStructExp<T>*p);
    //合并结点
    void ComNode(ListStructExp<T>*p);

};
//构造函数
template<typename T>
ListLinkExp<T>::ListLinkExp(void):length(0){
    curPtr=head=new ListStructExp<T>();
    head->NextNode()->SetNext();
}
//拷贝构造函数
template<typename T>
ListLinkExp<T>::ListLinkExp(const ListLinkExp<T>&L):length(0){
    curPtr=head=new ListStructExp<T>();
    head->NextNode()->SetNext();
    CopyList(L);
}
//析构函数
template<typename T>
ListLinkExp<T>::~ListLinkExp(){
    ClearList();
    delete head;
}
//返回表的长度
template<typename T>
int ListLinkExp<T>::ListLen(void){
    return length;
}
//判断表是否为空
template<typename T>
bool ListLinkExp<T>::ListEmpty(){
    return (length==0);//不包含头结点
}
//插入，头插法
template<typename T>
void ListLinkExp<T>::InsertFront(const float&coefs,const int&exps){
    curPtr=head;
    ListStructExp<T>*newNode=new ListStructExp<T>();
    newNode->SetCoef(coefs);
    newNode->SetExp(exps);
    curPtr->InsertNode(newNode);
    length++;
}
//调整curPtr指针位置,使curPtr指向上一个结点
template<typename T>
void ListLinkExp<T>::ResetcurPtr(){
    ListStructExp<T>*p=head;
    if(curPtr==head)return;//如果curPtr指向头结点，那么就直接返回
    else{//否则将curPtr调整到当前所指结点的前一个结点
        while(p->NextNode()!=curPtr){
            p=p->NextNode();
        }
        curPtr=p;
    }  
}
//插入，尾插法
template<typename T>
void ListLinkExp<T>::InsertAfter(const float&coefs,const int&exps){
    ListStructExp<T>*newNode=new ListStructExp<T>();
    newNode->SetCoef(coefs);
    newNode->SetExp(exps);
    curPtr->InsertNode(newNode);
    curPtr=curPtr->NextNode();
    length++;
}
//返回指定结点(使curPtr指向指定节点)
template<typename T>
void ListLinkExp<T>::ReNodeNext(int idx){
    if(idx<=0||idx>length)return;
    curPtr=head->NextNode();
    for(int i=1;i<idx;i++)curPtr=curPtr->NextNode();
}
//插入，在指定位置插入
template<typename T>
void ListLinkExp<T>::InsertIndex(const float&coefs,const int&exps,int idx){
    ReNodeNext(idx);//指向指定节点
    ResetcurPtr();//指向要插入节点的上一个节点
    ListStructExp<T>*newNode=new ListStructExp<T>();
    newNode->SetCoef(coefs);
    newNode->SetExp(exps);
    curPtr->InsertNode(newNode);
    length++;
}
//删除，头删法，从头结点之后开始删除
template<typename T>
void ListLinkExp<T>::DeleteFront(){
    curPtr=head;
    if(length==0)return;//节点已被删完
    ListStructExp<T>*p=curPtr->NextNode()->NextNode();
    delete(curPtr->DeleteNode());
    curPtr=p;
    length--;
}
//删除，尾删法，从尾部开始删除
template<typename T>
void ListLinkExp<T>::DeleteRear(){
    if(length==0);//节点已被删完
    ReNodeNext(length);//找到最后一个节点
    ListStructExp<T>*p=curPtr->NextNode();
    ResetcurPtr();//找到最后一个节点的前一个结点
    delete(curPtr->DeleteNode());
    curPtr=p;
    length--;
}
//删除，删除指定位置的结点
template<typename T>
void ListLinkExp<T>::DeleteIndex(int idx){
    if(idx<=0||idx>length)return;//不合法
    ReNodeNext(idx);//找到要删除的结点
    ListStructExp<T>*p=curPtr->NextNode();
    ResetcurPtr();//找到要删除结点的上一个结点
    delete(curPtr->DeleteNode());
    curPtr=p;
    length--;
}
//删除，删除当前位置结点
template<typename T>
void ListLinkExp<T>::DeleteThis(){
    if(curPtr==head)return;//头结点不可删除
    if(curPtr==NULL)return;//这是一个空结点
    if(ListEmpty())return;//表为空返回
    ListStructExp<T>*p=curPtr->NextNode();
    ResetcurPtr();//指向要删除结点的上一个结点
    delete(curPtr->DeleteNode());
    curPtr=p;
    length--;
}
//将表L拷贝到当前表尾
template<typename T>
void ListLinkExp<T>::CopyList(const ListLinkExp<T>&L){
    ListStructExp<T>*p=L.head->NextNode();
    while(p!=NULL){
        InsertAfter(p->ReCoef(),p->ReExp());
        p=p->NextNode();
    }
}
//打印当前链表的数据
template<typename T>
void ListLinkExp<T>::PrintList(){
    ListStructExp<T>*p=head->NextNode();
    ReNodeNext(length);
    while(p!=curPtr->NextNode()){
        cout<<p->ReCoef()<<" "<<p->ReExp()<<" ";
        p=p->NextNode();
    }
    cout<<endl;
}
//清空链表
template<typename T>
void ListLinkExp<T>::ClearList(){
    curPtr=head->NextNode();
    while(length!=0){
        DeleteFront();
    }
}
//排序，合并相同的指数(当前链表)
template<typename T>
void ListLinkExp<T>::SortListExp(){
    curPtr=head->NextNode();
    while(curPtr->NextNode()!=NULL){
        ListStructExp<T>*p=curPtr->NextNode();
        while(p!=NULL){
            if(curPtr->ReExp()>p->ReExp()){
                SwipNode(p);
            }else if(curPtr->ReExp()==p->ReExp()){
                ComNode(p);
                p=curPtr;
            }
            p=p->NextNode();
        }
        curPtr=curPtr->NextNode();
    }
}
//交换当前结点和指定结点
template<typename T>
void ListLinkExp<T>::SwipNode(ListStructExp<T>*p){
    float tempcoefs=p->ReCoef();
    int tempexps=p->ReExp();
    p->SetCoef(curPtr->ReCoef());
    p->SetExp(curPtr->ReExp());
    curPtr->SetCoef(tempcoefs);
    curPtr->SetExp(tempexps);
}
//合并结点
template<typename T>
void ListLinkExp<T>::ComNode(ListStructExp<T>*p){
    if(curPtr==NULL||p==NULL)return;//有一个是空节点无法合并
    if(curPtr==head||p==head)return;//有一个指向了头结点，无法合并
    if(length<2)return;//结点数小于2，无法合并
    curPtr->SetCoef((p->ReCoef()+curPtr->ReCoef()));//将两个系数相加即可
    ListStructExp<T>*tmp=curPtr;//保存此结点
    curPtr=p;//要删除的是结点p
    p=tmp;//让结点p指向已合并的节点
    DeleteThis();//删除curPtr指向的结点
    curPtr=tmp;//让cur指向已合并的结点 
}

#endif