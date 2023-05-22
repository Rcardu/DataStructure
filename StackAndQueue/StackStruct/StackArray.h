/*数组型栈的实现*/
#ifndef STACKARRAY_H
#define STACKARRAY_H
#include<iostream>
#define MAXSIZE 100
using namespace std;
template<typename T>
class StackArray{
private:
    T elem[MAXSIZE];//存放栈元素的一维数组空间
    int top;//栈顶指针变量
    T*cur;//指针
public:
    StackArray();//构造函数
    ~StackArray();//析构函数
    StackArray(StackArray<T>&L);//拷贝构造函数

    //入栈
    bool StackPush(T elem);
    //出栈
    bool StackPop();
    //取栈顶元素
    T StackTop();
    //打印栈中的元素
    void PrintStack();

};
template<typename T>
StackArray<T>::StackArray(){
    this->top=0;
}
template<typename T>
StackArray<T>::~StackArray(){
    while(top!=0){
        StackPop();
    }
}
/*入栈*/
template<typename T>
bool StackArray<T>::StackPush(T elem){
    if(top==MAXSIZE)return false;//栈满
    this->elem[this->top]=elem;
    this->top++;
    return true;
}
/*出栈*/
template<typename T>
bool StackArray<T>::StackPop(){
    if(this->top==0)return false;//栈空
    this->top--;//修改栈顶指针
    return true;
}
/*取栈顶元素*/
template<typename T>
T StackArray<T>::StackTop(){
    if(this->top==0)return false;
    return elem[this->top-1];
}
/*打印栈中的元素*/
template<typename T>
void StackArray<T>::PrintStack(){
    if(top==0)return ;
    for(int i=top-1;i!=-1;i--){
        cout<<elem[i]<<" ";
    }
    cout<<endl;
}


#endif