/*有权节点类*/
#pragma once
#include<iostream>
#include<vector>
using namespace std;
/*顶点类*/
struct VertexPoint{
    int key;//节点
    int val;//权
    VertexPoint(int x,int y):key(x),val(y){

    }
};
/*输入值列表vals,返回顶点列表vets
将vals转化成邻接表节点*/
vector<VertexPoint*>valsToVetsl(vector<vector<int>>vals){
    vector<VertexPoint*>vets;
    for(vector<int> val:vals){
        vets.push_back(new VertexPoint(val[0],val[1]));
    }
    return vets;
}
/*输入顶点列表vets，返回列表vals
将节点列表转化为vals*/
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
/*打印二维数组的值*/
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