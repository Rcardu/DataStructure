#ifndef USLISTNODESQ_H
#define USLISTNODESQ_H
#include<iostream>
#include"ListNode.h"

using namespace std;
template<typename T>class ListNodeSq;  
template<typename T>
class UsListNodeSq
{
private:

public:
    /*在一个已知升序的顺序表中插入元素data*/
    void Insert(ListNodeSq<T>&L,int data){
        /*如果在使用完函数后继续使用此对象，就使用引用类型的移动构造
            如果在使用完函数后需要的时原来的对象，就不对对象做引用，使用拷贝构造*/
        if(data>=L.elem[L.length-1]){//如果当前数据元素大于，当前顺序表的最后一个数据元素
            L.insert(data);//将此数据元素插入到表的尾部
        }else{
            int i=0;
            while(data>=L.elem[i])//从第一个元素开始寻找插入的位置
                i++;
            L.insert(i+1,data);//调用ListNode的插入函数后长度已经加1了
        }
    }
    /*已知两个线性表LA和LB，将LB中与LA中不重复的数据元素加入到LA中*/
    void CopyUnside(ListNodeSq<T>&LA,ListNodeSq<T>LB){
        for(int i=0;i<LB.length;i++){
            //LA中不存在和LB中相同的元素，则将其插入到LA中
            if(LA.Locate(LB.elem[i])==-1)
                LA.insert(LB.elem[i]);
        }
    }
};

#endif