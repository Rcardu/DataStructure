#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include<iostream>

/*结点模板*/
template<typename T>
class DoubleNode{
private:
    DoubleNode<T>*prior,*next;
public:
    T data;
    //构造函数
    //创建一个空链表，用于创建表头
    DoubleNode(void){prior=next=this;};
    //创建一个指向自身的结点并初始化data域，用于创建除表头以外的其他结点
    DoubleNode(const T&item){prior=next=this;data=item;};

    //将结点p插入到双向链表当前结点的前面
    void InsetrPred(DoubleNode<T>*p){
        /*先处理当前结点的前驱*/
        p->prior=prior;//让p结点的前指针指向当前结点前指针指向的结点(让p成为当前结点前驱的后继)
        prior->next=p;//让当前结点的前指针指向的结点的后指针指向p结点(让当前结点的前驱成为p结点的前驱)
        /*再处理当前结点*/
        p->next=this;//让p指针的后指针指向当前结点(让当前结点成为p结点的后继)
        prior=p;//让当前结点的前指针指向p结点(p结点成为当前结点的前驱)
    }
    //将结点p插入到双向链表当前结点的后面
    void InsertNext(DoubleNode<T>*p){
        /*先处理当前结点的后继*/
        p->next=next;//让p结点的尾指针指向当前结点尾指针指向的结点(让p成为当前结点后继的前驱)
        next->prior=p;//让当前结点尾指针指向的结点的前指针指向p结点(让当前结点的后继成为p结点的后继)
        /*再处理当前结点*/
        p->prior=this;//让p结点的前指针指向当前结点(让当前结点成为p结点的前驱)
        next=p;//让当前结点的尾指针指向p结点(让p结点成为当前结点的后继)
    }
    /*从链表中删除当前结点并返回其地址*/
    DoubleNode<T>*DeleteNode(void){
        prior->next=next;//让当前结点的前指针指向的结点的尾指针指向当前结点尾指针指向的结点(让后一个结点成为前一个结点的后继)
        next->prior=prior;//让当前结点的尾指针指向的结点的前指针指向当前结点前指针指向的结点(让前一个结点成为后一个结点的前驱)
        return this;//返回当前结点
    }
    /*取得指向前面结点的指针*/
    DoubleNode<T>*PredNode(void)const{return prior;};
    /*取得指向后面结点的指针*/
    DoubleNode<T>*NextNode(void)const{return next;};
};
/*链表模板(头结点没有数据，即真正的结点从头结点之后开始)*/
template<typename T>
class DoubleList
{
private:
    DoubleNode<T>*header;
    DoubleNode<T>*currPtr;//指向表头的头指针和指向当前结点的指针
    int size;//表中元素的个数，不包含头指针
    void CopyList(const DoubleList<T>&L);//将表L拷贝到当前表尾
public:
    //构造函数
    DoubleList(void);
    DoubleList(const DoubleList<T>&L);

    //析构函数
    ~DoubleList(void);

    //赋值运算符
    DoubleList<T>&operator=(const DoubleList<T>&L);

    //检查当前表的状态
    int ListSize(void)const;
    bool ListEmpty(void)const;

    //遍历表的函数
    void Reset(bool bherder=true);//是从表头开始遍历，还是表尾
    void Prev(void);
    void Next(void);
    bool EndOfList(void);

    //插入函数
    void InsertFront(const T&item);
    void InsertRear(const T&item);
    void InsertAt(const T&item);
    void InsertAfter(const T&item);

    //删除函数
    void DeleteFront(void);
    void DeleteRear(void);
    void DeleteAt(void);

    //返回当前结点的数据
    T& Data(void);
    //判断链表中是否包含该结点
    bool Find(const T&item);
    //清空表的函数
    void ClearList(void);
    //判断当前是否时头
    bool HeadECurIf(void);
    //打印当前链表
    void PrintList(void);
    //获取第m个结点
    void GetNode(int m);
    //复位函数，currPtr复位
    void ResetsPtr(){currPtr=header->NextNode();};
};
/*创建一个新表头*/
template<typename T>
DoubleList<T>::DoubleList(void):size(0){
    currPtr=header=new DoubleNode<T>();
}
/*拷贝构造函数*/
template<typename T>
DoubleList<T>::DoubleList(const DoubleList<T>&L):size(0){
    currPtr=header=new DoubleNode<T>();
    CopyList(L);
}
/*析构函数*/
template<typename T>
DoubleList<T>::~DoubleList(void){
    ClearList();
    delete header;
}
/*将表L拷贝到当前表尾*/
template<typename T>
void DoubleList<T>::CopyList(const DoubleList<T>&L){
    DoubleNode<T>*p=L.header->NextNode();
    while(p!=L.header){
        InsertRear(p->data);
        p=p->NextNode();
    }
}
/*返回表的大小*/
template<typename T>
int DoubleList<T>::ListSize(void)const{
    return size;
}
/*判断表是否为空*/
template<typename T>
bool DoubleList<T>::ListEmpty(void)const{
    return (size==0);//大小为0，表就为空
}
/*遍历表，从表头开始或者从表尾开始*/
template<typename T>
void DoubleList<T>::Reset(bool bheader){
    if(bheader){//从头开始
        currPtr=currPtr->NextNode();
    }else{
        currPtr=currPtr->PredNode();
    }
}
/*返回前一个结点*/
template<typename T>
void DoubleList<T>::Prev(void){
    currPtr=currPtr->PredNode();
}
/*返回后一个结点*/
template<typename T>
void DoubleList<T>::Next(void){
    currPtr=currPtr->NextNode();
}
/*判断当前结点是否是头结点*/
template<typename T>
bool DoubleList<T>::EndOfList(void){
    return (currPtr==header);
}
/*插入元素,头插法，使用头部遍历，遍历到当前结点的后一个结点，时再使用头插法时，能够插到*/
template<typename T>
void DoubleList<T>::InsertFront(const T&item){
    Reset();//可给参数，默认为true(从头开始)
    InsertAt(item);
}
/*插入元素，尾插法*/
template<typename T>
void DoubleList<T>::InsertRear(const T&item){
    currPtr=header;
    InsertAt(item);
}
/*在当前结点之后插入数据，头插法，一直在头结点的后面插入结点*/
template<typename T>
void DoubleList<T>::InsertAt(const T&item){
    DoubleNode<T>*newNode=new DoubleNode<T>(item);
    currPtr->InsertNext(newNode);
    size++;
}
/*在当前结点之前插入数据，尾插法，一直在头结点的前面插入结点*/
template<typename T>
void DoubleList<T>::InsertAfter(const T&item){
    DoubleNode<T>*newNode=new DoubleNode<T>(item);
    currPtr->InsetrPred(newNode);
    size++;
}
/*删除表，从前往后删*/
template<typename T>
void DoubleList<T>::DeleteFront(void){
    Reset();//遍历，从前往后
    DeleteAt();//删除当前结点
}
/*删除表，从后往前删*/
template<typename T>
void DoubleList<T>::DeleteRear(void){
    Reset(false);
    DeleteAt();
}
/*删除结点*/
template<typename T>
void DoubleList<T>::DeleteAt(void){
    if(currPtr==header)return;//结点已被删完
    DoubleNode<T>*p=currPtr->NextNode();
    delete (currPtr->DeleteNode());//删除当前结点
    currPtr=p;
    size--;
}
/*返回当前结点的数据*/
template<typename T>
T& DoubleList<T>::Data(void){
    return currPtr->data;
}
/*判断链表中是否包含该结点*/
template<typename T>
bool DoubleList<T>::Find(const T&item){
    for(Reset();!EndOfList();Next()){
        /*从头开始遍历结点，当前结点不是头结点，this指向下一个结点*/
        if(Data()==item)return true;
    }
    return false;
}
/*重载运算符*/
template<typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList<T>&L){
    if(this=&L)return *this;
    ClearList();
    CopyList(L);
    return *this;
}
/*清空表*/
template<typename T>
void DoubleList<T>::ClearList(void){
    Reset();
    while(currPtr!=header){
        DeleteAt();
    }
}
/*判断当前是否是表头*/
template<typename T>
bool DoubleList<T>::HeadECurIf(void){
    if(currPtr==header)return true;
    else return false;
}
/*打印当前链表*/
template<typename T>
void DoubleList<T>::PrintList(void){
    DoubleNode<T>*pre=header->NextNode();
    while(pre!=header){
        cout<<pre->data<<" ";
        pre=pre->NextNode();
    }
}
/*获取第m个结点，跳过头结点*/
template<typename T>
void DoubleList<T>::GetNode(int k){
    for(int i=1;i<k;i++){
        if(currPtr==header)//遇到头结点就退一步
        i=i-1;
        currPtr=currPtr->NextNode();
        if(size==1){
            currPtr=header->NextNode();
            break;
        }
    }
    if(currPtr==header)currPtr=header->NextNode();//在遍历完时遇到头结点，就设置为下一个结点
}
#endif