#ifndef LISTLINK_H
#define LISTLINK_H
#include<iostream>
#include<vector>
#include"ListLinkUS.h"
template<typename T>
class ListStruct{
public:
    T data;//数据
    ListStruct<T>*next;//指针结点
};
template<typename T>
class ListLink
{
private:
    ListStruct<T>*head;//头结点
public:
    ListLink();//构造函数
    void CreateList();//创建单链表
    ~ListLink();//析构函数
    int Length();//返回链表长度
    T GetElem(int index);//得到第index个元素的值
    int Locate(T data);//得到第一个元素值为data的序列号
    bool Insert(int index,T data);//在序列号为index的位置插入元素值为data的结点
    bool Delete(int index);//删除序号为index的结点
    bool PrintList();//输出单链表所有结点的元素值
    void Exchangedata(int index1,int index2);//交换两节点的元素值
    void SortALL();//将链表按升序排列
    ListLink(const ListLink<T>&L);//拷贝构造函数


    friend class ListLinkUS<T>;
};
/*构造函数，创建头结点*/
template<typename T>
ListLink<T>::ListLink(){
    head=new ListStruct<T>;
    head->data=0;
    head->next=NULL; 
}
/*创建单链表*/
template<typename T>
void ListLink<T>::CreateList(){
    int length;
    T data;
    //cout<<"开始创建链表，输入要创建的链表的长度（尾部插入）"<<endl;
    cin>>length;
    //cout<<"输入元素值"<<endl;
    for(int i=0;i<length;i++){
        cin>>data;
        if(i==0)head->data=data;
        else Insert(Length()+1,data);
    }
}
/*析构函数，销毁单链表*/
template<typename T>
ListLink<T>::~ListLink(){
    ListStruct<T>*del;
    while(head->next!=NULL){
        del=head;
        head=head->next;
        delete del;
    }
    delete head;
    //cout<<"单链表销毁成功✧*｡ (ˊᗜˋ*) ✧*｡"<<endl;
}
/*返回当前链表长度*/
template<typename T>
int ListLink<T>::Length(){
    ListStruct<T>*pre=head;
    int num=1;
    while(pre->next!=NULL){
        num++;
        pre=pre->next;
    }
    return num;
}
/*返回第index个元素的值*/
template<typename T>
T ListLink<T>::GetElem(int index){
    ListStruct<T>*pre=head;
    if(index<0||index>Length()){
        //index值不合法
        //cout<<"index值不合法 ჴ˘ര‸രჴ  "<<endl;
        return 0;
    }else{
        for(int i=0;i<index-1;i++){
            pre=pre->next;
        }
        //cout<<"查找成功！◝(⑅•ᴗ•⑅)◜..°♡ "<<endl;
        return pre->data;
    }
    return 0;
}
/*得到第一个元素值为data的序列号*/
template<typename T>
int ListLink<T>::Locate(T data){
    ListStruct<T>*pre=head;
    for(int i=0;i<Length();i++){
        if(pre->data==data){
            //cout<<"找到啦 (*＞◡❛) "<<endl;
            return i+1;
        }
        pre=pre->next;
    }
   // cout<<"没找到 (。•́︿•̀。) "<<endl;
    return -1;
}
/*在序列号为index的位置插入元素值为data的结点*/
template<typename T>
bool ListLink<T>::Insert(int index,T data){
    ListStruct<T>*pre=head,*s;
    if(index<0){
        //cout<<"插入位置不合法 ( ´◔︎ ‸◔︎`) "<<endl;
        return false;
    }
    if(index>Length()){//插入位置大于链表长度时
        while(pre->next!=NULL){
            pre=pre->next;
        }
        s=new ListStruct<T>;//创建一个临时结点s
        pre->next=s;//s为pre的后继结点
        s->data=data;//给数据
        s->next=NULL;//s的后继设置为空
        return true;
    }else{
        for(int i=0;i<index-2;i++)
            pre=pre->next;
        s=new ListStruct<T>;
        s->next=pre->next;//让pre的后继成为s的后继
        pre->next=s;//让s成为pre的后继
        s->data=data;//插入元素
        //cout<<"插入成功！ ❛‿˂̵✧ "<<endl;
        return true;
    }
    return false;
}
template<typename T>
bool ListLink<T>::Delete(int index){
    ListStruct<T>*pre=head,*s;
    if(index<0||index>Length())return false;
    else if(index==Length()){
        for(int i=0;i<Length()-2;i++){
            pre=pre->next;
        }
        pre->next=NULL;
        return true;
    }else{
        for(int i=0;i<index-2;i++)
            pre=pre->next;//找到要删除结点的前一个结点
        s=new ListStruct<T>;
        s=pre->next;//让s指向要删除的结点
        pre->next=s->next;//让pre指向要删除结点的下一个结点
        return true;
    }
}
template<typename T>
bool ListLink<T>::PrintList(){
    ListStruct<T>*pre=head;
    if(pre==NULL)return false;
    else{
        while(pre!=NULL){
            cout<<pre->data<<" ";
            pre=pre->next;
        }
    }
    cout<<endl;
    return true;
}
template<typename T>
void ListLink<T>::Exchangedata(int index1,int index2){
    ListStruct<T>*pre=head,*s1,*s2;
    int Min,Max,data;
    //定位结点的前后
    Min=(index1>index2)?index2:index1;
    Max=(index1>index2)?index1:index2;
    if(Min>0&&Max<Length()){
        for(int i=0;i<Min-2;i++)
            pre=pre->next;
        s1=pre->next;
        pre=head;
        for(int i=0;i<Max-2;i++)
            pre=pre->next;
        s2=pre->next;
        data=s1->data;
        s1->data=s2->data;
        s2->data=data;
    }
}
/*链表按升序*/
template<typename T>
void ListLink<T>::SortALL(){
    //两个指针，两层循环
    ListStruct<T>*p=head,*s;
    for(int i=0;i<Length()&&p->next!=NULL;i++){
        s=p->next;
        for(int j=i;j<Length()&&s!=NULL;j++){
            if(p->data>s->data){
                int tem=p->data;
                p->data=s->data;
                s->data=tem;
            }
            s=s->next;
        }
        p=p->next;
    }
}
/*拷贝构造函数*/
template<typename T>
ListLink<T>::ListLink(const ListLink<T>&L){
    ListStruct<T>*head=new ListStruct<T>;
    ListStruct<T>*p=L.head,*s;
    head->data=p->data;
    p=p->next;
    s=head;
    while(p!=NULL){
        s->next=new ListStruct<T>;
        s->next->data=p->data;
        p=p->next;
        s=s->next;
    }
}

#endif