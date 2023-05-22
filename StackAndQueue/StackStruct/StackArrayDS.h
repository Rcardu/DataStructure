/*两栈共享*/
#ifndef STACKARRAYDS_H
#define STACKARRAYDS_H
#define MAXSIZES 50
#include<iostream>
#include"StackArray.h"
using namespace std;
template<typename T>
class StackArrayDS:public StackArray<T>{
private:
    T elem[MAXSIZES];//栈空间
    int top[2];//双栈指针
public:
    StackArrayDS(/* args */);
    ~StackArrayDS();

    //入栈,可选两个栈
    bool StackPush(T elem,bool flag=true);
    //出栈，可选两个栈
    bool StackPop(bool flag=true);
    //取栈顶元素，可选两个栈
    T StackTop(bool flag=true);
    //打印栈中元素,可选
    void PrintStack(bool flag=true);
};
template<typename T>
StackArrayDS<T>::StackArrayDS(/* args */){
    this->top[0]=0;//栈1
    this->top[1]=MAXSIZES-1;//栈2
}
//入栈
template<typename T>
bool StackArrayDS<T>::StackPush(T elem,bool flag){
    if(this->top[0]==this->top[1])return false;//栈满
    if(flag){//进入栈1
        this->elem[this->top[0]]=elem;
        this->top[0]++;//修改栈指针
        return true;
    }else{
        this->elem[this->top[1]]=elem;
        this->top[1]--;//修改栈指针
        return true;
    }
}
//出栈
template<typename T>
bool StackArrayDS<T>::StackPop(bool flag){
    if(flag){
        if(top[0]==0)return false;//栈1为空
        this->top[0]--;//修改栈指针
        return true;
    }else{
        if(top[1]==MAXSIZES-1)return false;
        this->top[1]++;//修改栈指针
        return true;
    }
}
//取栈顶元素，可选两个栈
template<typename T>
T StackArrayDS<T>::StackTop(bool flag){
    if(flag){
        if(top[0]==0)return false;//栈空
        return elem[this->top[0]-1];
    }else{
        if(top[1]==MAXSIZES-1)return false;//栈空
        return elem[this->top[1]+1];
    }
}
//打印栈中元素,可选
template<typename T>
void StackArrayDS<T>::PrintStack(bool flag){
    if(flag){
        if(top[0]==0)return ;
        for(int i=top[0]-1;i!=-1;i--){
            cout<<elem[i]<<" ";
        }
    }else{
        if(top[1]==MAXSIZES-1)return ;
        for(int i=top[1]+1;i!=MAXSIZES;i++){
            cout<<elem[i]<<" ";
        }
    }
    cout<<endl;
}
//析构
template<typename T>
StackArrayDS<T>::~StackArrayDS(){
    while(top[0]!=0||top[1]!=MAXSIZES-1){
        if(top[0]!=0){
            StackPop();
        }else{
            StackPop(false);
        }
    }
}



#endif