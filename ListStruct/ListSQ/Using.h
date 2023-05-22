#include<iostream>
#include"ListNode.h"
#include<algorithm>
#include<vector>
#include"UsListNodeSq.h"
#include"ListSqStudent.h"

using namespace std;
void UseListFormat();

void UseListFormat(){
    StudentList<Student<int>>s;
    int n;
    cin>>n;
    cout<<"正在创建信息表,请输入学生信息："<<endl;
    s.creatStudent(s,n);
    cout<<"学生信息表如下:"<<endl;
    s.traverse();
    cout<<"请输入要查询的学生学号: "<<endl;
    s.searchNo(s,s.Getlen());
    cout<<"请输入要按照那样成绩排序："<<endl;
    int p,m;
    cin>>n>>m;
    s.sortTosour(s,n,m);
    cout<<"学生信息排序如下："<<endl;
    s.traverse();
}
