#ifndef LISTSQSTUDENT_H
#define LISTSQSTUDENT_H
#include<iostream>
#include<string>
#include<cstdlib>
#include<cstring>
#include"ListNode.h"
using namespace std;
template<typename T>class UsListNodeSq;
template<typename T>class ListNodeSq;
template<typename T>
class Student{
private:
    char no[5];
    char name[10];
    int soure[5];
    int total;
public:
    Student()=default;
    ~Student(){};
    //获取学号指针
    char* GetNo(){return no;};
    //获取指定成绩
    int Getsoure(int idx){return soure[idx];};
    //获取总成绩
    int Gettotal(){return total;};

    void Insertstudet();//插入数据元素
    void printst();//打印数据元素



};
//插入数据元素
template<typename T>
void Student<T>::Insertstudet(){
    cin>>no;
    cin>>name;
    total=0;
    for(int i=0;i<5;i++){
        cin>>soure[i];
        total+=soure[i];
    }
}
//打印数据元素
template<typename T>
void Student<T>::printst(){
    cout<<no<<" "<<name<<" ";
    for(int i=0;i<5;i++)cout<<soure[i]<<" ";
    cout<<total;
}

/*学生表类，继承顺序表*/
template<typename T>
class StudentList:public ListNodeSq<T>{
private:
public:
    void creatStudent(ListNodeSq<T>&L,int n);//创建表单
    void searchNo(ListNodeSq<T>&L,int n);//按照学号查询学生成绩信息
    void sortTosour(ListNodeSq<T>&L,int idx,bool flag=true);//按照指定成绩升序排序
};

/*创建学生表*/
template<typename T>
void StudentList<T>::creatStudent(ListNodeSq<T>&L,int n){
    for(int i=0;i<n;i++)(L.GetDatas())[i].Insertstudet();
    L.LengthSet(n);
}
/*按学号查询信息*/
template<typename T>
void StudentList<T>::searchNo(ListNodeSq<T>&L,int n){
    char sno[10];
    cin>>sno;
    for(int i=0;i<n;i++){
        if(strcmp(sno,L.GetDatas()[i].GetNo())==0)
            L.traverse(i);
    }
}
//按照指定成绩升序排序
template<typename T>
void StudentList<T>::sortTosour(ListNodeSq<T>&L,int idx,bool flag){
    T ptr;/*elem的数据类型为Student<int>,所以ptr的类型应为模板自动适配此类型*/
    if(flag){//按照指定成绩升序
        for(int i=0;i<L.Getlen();i++){
            for(int j=i+1;j<L.Getlen();j++){
                if(L.GetDatas()[i].Getsoure(idx)>L.GetDatas()[j].Getsoure(idx)){
                    ptr=L.GetDatas()[j];
                    L.GetDatas()[j]=L.GetDatas()[i];
                    L.GetDatas()[i]=ptr;
                }
            }
        }
    }else{
        for(int i=0;i<L.Getlen();i++){
            for(int j=i+1;j<L.Getlen();j++){
                if(L.GetDatas()[i].Gettotal()>L.GetDatas()[j].Gettotal()){
                    ptr=L.GetDatas()[j];
                    L.GetDatas()[j]=L.GetDatas()[i];
                    L.GetDatas()[i]=ptr;
                }
            }
        }
    }
}


#endif