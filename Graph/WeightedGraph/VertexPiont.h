/*��Ȩ�ڵ���*/
#pragma once
#include<iostream>
#include<vector>
using namespace std;
/*������*/
struct VertexPoint{
    int key;//�ڵ�
    int val;//Ȩ
    VertexPoint(int x,int y):key(x),val(y){

    }
};
/*����ֵ�б�vals,���ض����б�vets
��valsת�����ڽӱ�ڵ�*/
vector<VertexPoint*>valsToVetsl(vector<vector<int>>vals){
    vector<VertexPoint*>vets;
    for(vector<int> val:vals){
        vets.push_back(new VertexPoint(val[0],val[1]));
    }
    return vets;
}
/*���붥���б�vets�������б�vals
���ڵ��б�ת��Ϊvals*/
vector<vector<int>>vetsTovalsl(vector<VertexPoint*>vets){
    vector<int>temp;
    vector<vector<int>>vals;
    int i=0;
    for(VertexPoint*vet:vets){
        temp.push_back(vet->key);
        temp.push_back(vet->val);
        vals.push_back(temp);
        temp.clear();
    }
    return vals;
}
/*��ӡ��ά�����ֵ*/
void printSforTwo(vector<vector<int>>result){
    for(auto res:result){
        for(int i=0;i<res.size();i++){
            cout<<"("<<res[i]<<" , ";
        }
        cout<<")";
        cout<<"  ";
    }
    cout<<endl;
}