#ifndef SKIPLISTCOPY_H
#define SKIPLISTCOPY_H
#include"../utils/common.hpp"
#include<random>
template<typename T>
class SkipListNodeCopy{
public:
    //包含索引、数据、此类型的链表指针
    int key;
    T data;
    vector<SkipListNodeCopy*>next;
    //构造函数，构造索引、数据、确定数组指针大小
    SkipListNodeCopy(int keys,T val,int Level):key(keys),data(val){
        for(int i=0;i<Level,i++){
            next.push_back(nullptr);
        }
    }
};
//跳跃链表类
template<typename T>
class SkipListCopy{
//基本数据声明与定义
public:
    //包含一个开始的头指针，索引为最小
    SkipListNodeCopy<T>*head;
    //限制最大层数
    int maxLevel;
    //确定最大与最小索引
    const int minInt=numeric_limits<int>::min();
    const int maxInt=numeric_limits<int>::max();
//函数声明与定义
public:
    //构造函数，用来构造初始链表
    //最大层数以及初值
    SkipListCopy(int maxLevel,T iniValue);
    //析构函数，删除头尾结点
    ~SkipListCopy();

    //随机层数方法
    int randomLevel();
    //插入、查询、删除
    SkipListNodeCopy<T>*insert(int keys,T val);
    SkipListNodeCopy<T>*find(int keys);
    SkipListNodeCopy<T>*deleteNode(int keys);
    //打印
    void printNode();
private:
    //包含一个尾指针，索引尾最大
    SkipListNodeCopy<T>*tail;
    //返回当前node的最大层数
    int nodeLevel(vector<SkipListNodeCopy<T>*>next){
        int nedelevel=0;
        if(node[0]->key==maxInt){
            return nedelevel;
        }
        for(int i=0;i<next.size();i++){
            if(next[i]!=nullptr&&next[i]->key!=maxInt){
                nedelevel++;
            }else{
                break;
            }
        }
        return nedelevel;
    }

};
/*构造函数
构造头结点与尾结点
并让头结点指向尾结点*/
template<typename T>
SkipListCopy<T>::SkipListCopy(int maxLevel,T iniValue):maxLevel(maxLevel){
    head=new SkipListNodeCopy<T>(minInt,iniValue,maxLevel);
    tail=new SkipListNodeCopy<T>(maxInt,iniValue,maxLevel);

    for(int i=0;i<maxLevel;i++){
        head->next[i]=tail;
    }
}
/*析构函数，删除头尾结点*/
template<typename T>
SkipListCopy<T>::~SkipListCopy(){
    delete head;
    delete tail;
}
/*随机层数方法，使用time作为种子来获取0~1之间的随机值
初始层数为1
随机一个数，使之在0~1之间生成
为1并且层数没有超过最大层数就使层数加1
*/
template<typename T>
int SkipListCopy<T>::randomLevel(){
    int levels=1;
    int seed=time(NULL);
    static default_random_engine e(seed);
    static uniform_int_distribution u(0,1);
    while(u(e)&&levels<maxLevel){
        levels++;
    }
    return levels;
}
/*插入
判断该节点是否存在，若存在则替换结点数据
否则，获取新节点的随机层数
找到合适的插入位置
插入并调整每层前后的node的指针*/
template<typename T>
SkipListNodeCopy<T>*SkipListCopy<T>::insert(int keys,T val){
    SkipListNodeCopy<T>*newNode=nullptr;
    newNode=find(keys);
    if(newNode){
        newNode->data=val;
        cout<<"已更新节点值"<<endl;
        return head;
    }
    SkipListNodeCopy<T>*temp=head;
    int levels=randomLevel();
    //创建节点
    newNode=new SkipListNodeCopy<T>(keys,val,levels);
    //从最高层开始遍历
    /*注最低层位第一层，所以，最高层位levels-1，当此值小于-1时
    最底层也被遍历完*/
    for(int i=(levels-1);i>-1;i--){
        //从头开始寻找目标节点
        while(temp->next[i]!=nullptr&&temp->next[i]->key>keys){
            temp=temp->next[i];
        }
        //找到后插入
        newNode->next[i]=temp->next[i];
        temp->next[i]=newNode;
    }
    return head;
}
/*查找
列表有序，找到该节点附近的节点，如果下一个节点等于目标节点
则返回该节点，否则返回空指针*/
template<typename T>
SkipListNodeCopy<T>*SkipListCopy<T>::find(int keys){
    SkipListNodeCopy<T>*temp=head;
    //找到当前跳跃链表的最大层数
    int curlevel=nodelevel(temp->next);
    for(int i=(curlevel);i>-1;i--){
        while(temp->next[i]!=nullptr&&temp->next[i]->key<keys){
            temp=temp->next[i];
        }
    }
    //让temp指向下一个节点
    temp=temp->next[0];
    if(temp->key==keys)return temp;
    else return nullptr;
}
/*删除
判断是否存在，不存在则告知
否则，找到小于该节点最近的节点
更改每层前面的节点*/
template<typename T>
SkipListNodeCopy<T>*SkipListCopy<T>::deleteNode(int keys){
    SkipListNodeCopy<T>*node=find(keys);
    if(node==nullptr){
        cout<<"该节点不存在"<<endl;
        return head;
    }else{
        SkipListNodeCopy<T>*temp=head;
        int Levels=node->next.size();
        for(int i=(Levels-1);i>-1;i--){
            while(temp->next[i]!=nullptr&&temp->next[i]->key<keys){
                temp=temp->next[i];
            }
            temp->next[i]=temp->next[i]->next[i];
        }
        return head;
    }
}
template<typename T>
void SkipListCopy<T>::printNode(){
    for(int i=0;i<maxLevel;i++){
        SkipListNodeCopy<T>*temp=head;
        int lineLen=1;

        if(temp->next->key!=maxInt){
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




#endif