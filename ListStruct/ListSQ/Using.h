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
    cout<<"���ڴ�����Ϣ��,������ѧ����Ϣ��"<<endl;
    s.creatStudent(s,n);
    cout<<"ѧ����Ϣ������:"<<endl;
    s.traverse();
    cout<<"������Ҫ��ѯ��ѧ��ѧ��: "<<endl;
    s.searchNo(s,s.Getlen());
    cout<<"������Ҫ���������ɼ�����"<<endl;
    int p,m;
    cin>>n>>m;
    s.sortTosour(s,n,m);
    cout<<"ѧ����Ϣ�������£�"<<endl;
    s.traverse();
}
