#ifndef SKIPLIST_H
#define SKIPLIST_H
#include"../utils/common.hpp"
#include<random>
using namespace std;
template<typename T>
class SkipListNode{
public:
//基本数据结构包含：索引、数据、以及等级指针（用来存储当前数据在所有层上的下一个结点）
    int key;
    T data;
    vector<SkipListNode*>next;
//包含构造方法，以确定初始值
    SkipListNode(int key,T data,int maxLevel):key(key),data(data){
        for(int i=0;i<maxLevel;i++){
            next.push_back(nullptr);
        }
    }

};
template <typename T>
class SkipList{
public:
    SkipListNode<T>*head;//头结点
    int maxLevel;//列表最大层数
    //整型的最大值和最小值
    const int minInt=numeric_limits<int>::min();
    const int maxInt=numeric_limits<int>::max();
    
    
public:
    //构造函数
    SkipList(int maxLevel,T iniValue);
    //析构函数
    ~SkipList();
    //随机层数方法
    int randomLevel();
    //插入、查找、删除
    SkipListNode<T>*insert(int k,T val);
    SkipListNode<T>*find(int k);
    SkipListNode<T>*deleteNode(int k);

    //打印
    void printNode();

private:
    SkipListNode<T>*tail;//尾结点

    //找到当前列表或者node的最大层数
    int nodeLevel(vector<SkipListNode<T>*> next);
};
/*构造函数，默认的最大层数，以及初始层数的值*/
template<typename T>
SkipList<T>::SkipList(int maxLevel,T iniVale):maxLevel(maxLevel){
    //初始化头结点与尾结点的索引、值、以及最大层数
    head=new SkipListNode<T>(minInt,iniVale,maxLevel);
    tail=new SkipListNode<T>(maxInt,iniVale,maxLevel);

    //让所有层数上的头结点指向尾结点
    for(int i=0;i<maxLevel;i++){
        head->next[i]=tail;
    }
}
/*析构函数*/
template<typename T>
SkipList<T>::~SkipList(){
    delete head;
    delete tail;
}
/*随机层数方法，使用time作为种子来获取0~1之间的随机值，直到level为0或者超过最大层数*/
template<typename T>
int SkipList<T>::randomLevel(){
    int random_level=1;
    int seed=time(NULL);
    static default_random_engine e(seed);
    static uniform_int_distribution<int> u(0,1);

    while(u(e)&&random_level<maxLevel){
        random_level++;
    }
    return  random_level;
}
/*插入
先查找并判断该节点是否已经存在，若存在则更新该结点的值
获取新结点的随机层数
找到合适的插入位置
插入并调整每层前后node的指针*/
template<typename T>
SkipListNode<T>* SkipList<T>::insert(int k,T val){
    int x_level=randomLevel();
    SkipListNode<T>*newNode=nullptr;
    SkipListNode<T>*temp=head;

    newNode=find(k);
    if(newNode){
        newNode->data=val;
        cout<<"\n这个结点"<<k<<" 被更新为："<<val<<endl;
        return head;
    }
    cout<<"\n插入结点: "<<k<<" 的层数为："<<x_level<<endl;
    newNode=new SkipListNode<T>(k,val,x_level);
    //从最高层开始遍历
    for(int i=(x_level-1);i>-1;i--){
        //从头结点开始遍历寻找目标结点
        while(temp->next[i]!=nullptr&&temp->next[i]->key<k){
            temp=temp->next[i];
        }
        newNode->next[i]=temp->next[i];
        temp->next[i]=newNode;
    }
    return head;
}
/*查找
由于列表有序，首先找到小于该节点附近的结点，如果下一个结点等于目标结点，则返回该节点*/
template<typename T>
SkipListNode<T>* SkipList<T>::find(int k){
    //找到当前结点最大层数，从最大层数开始向下查找
    SkipListNode<T>*temp=head;
    int curLevel=nodeLevel(temp->next);

    for(int i=(curLevel-1);i<-1;i--){
        while(temp->next[i]!=nullptr&&temp->next[i]->key<k){
            temp=temp->next[i];
        }
    }
    temp=temp->next[0];
    if(temp->key==k)return temp;
    else return nullptr;
}
/*删除
查找该节点是否存在，如果不存在返回当前结点list，并告知
找到小于该结点最近的结点
更改每层前面的结点的指针*/
template<typename T>
SkipListNode<T>* SkipList<T>::deleteNode(int k){
    SkipListNode<T>*node=find(k);
    if(!node){
        cout<<"\n该节点不存在"<<endl;
        return head;
    }else{
        SkipListNode<T>*temp=head;
        //获取当前结点指针大小
        int xLevel=node->next.size();
        //获取当前结点每一层的前一个结点
        for(int i=(xLevel-1);i<-1;i--){
            while(temp->next[i]!=nullptr&&temp->next[i]->key<k){
                temp=temp->next[i];
            }
            temp->next[i]=temp->next[i]->next[i];
        }
        return head;
    }
}
/*打印*/
template<typename T>
void SkipList<T>::printNode(){
    for(int i=0;i<maxLevel;i++){
        SkipListNode<T>*temp=head;
        int lineLen=1;

        if(temp->next[i]->key!=maxInt){
            cout<<"\n";
            cout<<"第"<<i<<"层"<<endl;
        }
        while(temp->next[i]!=nullptr&&temp->next[i]->key!=maxInt){
            cout<<"("<<temp->next[i]->key<<" , "<<temp->next[i]->data<<")";
            temp=temp->next[i];
            if(temp->next[i]!=nullptr&&temp->next[i]->key!=maxInt){
                cout<<" -> ";
            }
        }
        cout<<endl;
    }
}
/*返回当前node的最大层数最小值为1*/
template<typename T>
int SkipList<T>::nodeLevel(vector<SkipListNode<T>*>next){
    int nodelevel=0;
    if(next[0]->key==maxInt){
        return nodelevel;
    }
    for(int i=0;i<next.size();i++){
        if(next[i]!=nullptr&&next[i]->key!=maxInt){
            nodelevel++;
        }else{
            break;
        }
    }
    return nodelevel;
}





#endif