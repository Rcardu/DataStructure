#ifndef USINGSTACK_H
#define USINGSTACK_H
#include<iostream>
#include<vector>
#include"StackArray.h"
#include"StackArrayDS.h"
#include"StackList.h"
using namespace std;
void UsStack();
void UsStackDS();
void UsStackList();
//�ж����źϷ���
void UsStackListstr();

void UsStack(){
    int N[5]={1,2,3,4,5};
    StackArray<int>obj;
    for(int i=0;i<5;i++)obj.StackPush(N[i]);
    cout<<obj.StackTop()<<endl;
    obj.StackPop();
    obj.StackPush(2);
    cout<<obj.StackTop()<<endl;
    obj.StackPop();
    obj.PrintStack();
}
void UsStackDS(){
    int N[5]={1,2,3,5,6};
    int M[5]={9,5,3,8,7};
    StackArrayDS<int>obj;
    for(int i=0;i<5;i++)obj.StackPush(N[i]);
    for(int i=0;i<5;i++)obj.StackPush(M[i],false);
    obj.PrintStack();
    cout<<endl;
    obj.PrintStack(false);
    obj.StackPop();
    obj.PrintStack();
    obj.StackPop(false);
    obj.PrintStack(false);
    cout<<obj.StackTop()<<endl;
    cout<<obj.StackTop(false)<<endl;
}
void UsStackList(){
    //��һ���Ǹ�ʮ������Nװ����d�������
    //ʮ��������d����
    int N,d;
    cin>>N>>d;
    StackList<int>obj;
    int x;
    while(N>0){
        x=N%d;
        obj.ListPush(x);
        N/=d;
    }
    obj.PrintStack();
}
//�ж�����
void UsStackListstr(){
    vector<char>chr;
    int N;
    cin>>N;
    StackList<char>obj;
    for(int i=0;i<N;i++){
        char ch;
        cin>>ch;
        chr.push_back(ch);
    }
    for(int i=0;i<N;i++){
        switch(chr[i]){
            case '(':
            case '[':
            case '{':
            obj.ListPush(chr[i]);
            break;
            case ')':
                if(obj.IsEmpty()){
                    cout<<") ����";
                    break;
                }else{
                    if(obj.GetTop()!='('){
                        cout<<"��ƥ��"<<endl;
                    }else   obj.ListPop();
                }
                break;
            case ']':
                if(obj.IsEmpty()){
                    cout<<"] ����";
                    break;
                }else{
                    if(obj.GetTop()!='['){
                        cout<<"��ƥ��"<<endl;
                    }else   obj.ListPop();
                }
                break;
            case '}':
                if(obj.IsEmpty()){
                        cout<<"} ����";
                        break;
                    }else{
                        if(obj.GetTop()!='{'){
                            cout<<"��ƥ��"<<endl;
                        }else   obj.ListPop();
                    }
                    break;
            default:break;
        }
    }
}


#endif