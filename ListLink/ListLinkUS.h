#ifndef LISTLINKUS_H
#define LISTLINKUS_H
#include<iostream>
#include"ListLink.h"
#include<unordered_set>
#include<vector>
#include"ListLinkEXP.h"
template<typename T>class ListLink;
template<typename T>class ListStruct;
template<typename T>
class ListLinkUS
{
private:
public:
    /*将两个按升序排列的单链表LA和LB合并成一个新的单链表LC*/
    void LinkList_Unionlist(ListLink<T>&LA,ListLink<T>&LB,ListLink<T>&LC);
    /*假设链表LA与链表LB各代表一个集合，求集合中不相同的元素即，LA-LB*/
    void LAandLBfost(ListLink<T>&LA,ListLink<T>&LB,ListLink<T>&LC);
    /*求两个链表内的元素的交集*/
    void LAinterLB(ListLink<T>&LA,ListLink<T>&LB,ListLink<T>&LC);
    /*将两个多项式合并*/
    void DAandDBcom(ListLinkExp<T>&DA,ListLinkExp<T>&DB,ListLinkExp<T>&DC);
};
/*将两个按升序排列的单链表LA和LB合并成一个新的单链表LC*/
template<typename T>
void ListLinkUS<T>::LinkList_Unionlist(ListLink<T>&LA,ListLink<T>&LB,ListLink<T>&LC){
    ListStruct<T>*pa,*pb,*pc;
    pa=LA.head;
    pb=LB.head;
    if(pa->data>pb->data){
        LC.head->data=pb->data;
        pb=pb->next;
    }else{
        LC.head->data=pa->data;
        pa=pa->next;
    }
    pc=LC.head;
    
    while((pa!=NULL)&&(pb!=NULL)){
        if(pa->data<=pb->data){
            pc->next=new ListStruct<T>;
            pc->next->data=pa->data;
            pc=pc->next;
            pa=pa->next;
        }else{
            pc->next=new ListStruct<T>;
            pc->next->data=pb->data;
            pc=pc->next;
            pb=pb->next;
        }
    }
    while(pa==NULL&&pb!=NULL){
        pc->next=new ListStruct<T>;
        pc->next->data=pb->data;
        pc=pc->next;
        pb=pb->next;
    }
    while(pa!=NULL&&pb==NULL){
        pc->next=new ListStruct<T>;
        pc->next->data=pa->data;
        pc=pc->next;
        pa=pa->next;
    }
    pc->next=NULL;
}
/*假设链表LA与链表LB各代表一个集合，求集合中不相同的元素即，LA-LB*/
template<typename T>
void ListLinkUS<T>::LAandLBfost(ListLink<T>&LA,ListLink<T>&LB,ListLink<T>&LC){
        ListStruct<T>*pa,*pb,*pc,*tp;
        pa=LA.head;
        pc=LC.head;
        unordered_set<int>used;//记录重复的值
        while(pa!=NULL){//查找重复的值
            pb=LB.head;//扫描LB中的数据找到与LA相同的结点
            while((pb!=NULL)&&(pb->data!=pa->data))
                pb=pb->next;
            if(pb!=NULL)used.insert(pb->data);
            pa=pa->next;
        }
        //将不再used内的值，也就是两个集合中不重复的值插入LC中
        pa=LA.head;
        while(pa!=NULL){//将LA中不重复的值放入LC中
            if(used.find(pa->data)==used.end()){
                pc->data=pa->data;
                pc->next=new ListStruct<T>;
                pc=pc->next;
            }
            pa=pa->next;
        }
        pb=LB.head;
        while(pb!=NULL){
            if(used.find(pb->data)==used.end()){
                pc->data=pb->data;
                tp=pc;//记录pc
                pc->next=new ListStruct<T>;
                pc=pc->next;
            }
            pb=pb->next;
        }
        delete tp->next;
        tp->next=NULL;
        tp=NULL;
        pc=NULL;
    }
template<typename T>
void ListLinkUS<T>::LAinterLB(ListLink<T>&LA,ListLink<T>&LB,ListLink<T>&LC){
    ListStruct<T>*pa,*pb,*pc,*tp;
    pa=LA.head;
    pc=LC.head;
    vector<int>used;
    while(pa){
        pb=LB.head;
        while(pb){
            if(pa->data==pb->data)used.push_back(pa->data);
            pb=pb->next;
        }
        pa=pa->next;
    }
    for(int i=0;i<used.size();i++){
        pc->data=used[i];
        pc->next=new ListStruct<T>;
        tp=pc;
        pc=pc->next;
    }
    delete tp->next;
    tp->next=NULL;
    tp=NULL;
    pc=NULL;
}
template<typename T>
void ListLinkUS<T>::DAandDBcom(ListLinkExp<T>&DA,ListLinkExp<T>&DB,ListLinkExp<T>&DC){
    DA.SortALL();
    DB.SortALL();
    ListStructExp<T>*pa,*pb;
    pa=DA.ReNodehead();
    pb=DB.ReNodehead();
    pb=pb->NextNode();
    pa=pa->NextNode();
    while(pa!=NULL&&pb!=NULL){//都不为空，开始插入
        if(pa->ReExp()==pb->ReExp()){//指数相同就合并
            DC.InsertAfter((pa->ReCoef()+pb->ReCoef()),pa->ReExp());
            pa=pa->NextNode();
            pb=pb->NextNode();
        }else if(pa->ReExp()>pb->ReExp()){//谁的指数小，先插谁
            DC.InsertAfter(pb->ReCoef(),pb->ReExp());
            pb=pb->NextNode();
        }else{
            DC.InsertAfter(pa->ReCoef(),pa->ReExp());
            pa=pa->NextNode();
        }
    }
    while(pa==NULL&&pb!=NULL){//若pb有剩余
        DC.InsertAfter(pb->ReCoef(),pb->ReExp());
        pb=pb->NextNode();
    }
    while(pa!=NULL&&pb==NULL){//若pa有剩余
        DC.InsertAfter(pa->ReCoef(),pa->ReExp());
        pa=pa->NextNode();
    }
}

#endif