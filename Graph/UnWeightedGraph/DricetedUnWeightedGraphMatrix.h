/*������Ȩͼ(�ڽӾ���)*/
#ifndef DRIECETEDUNWEIGHTEDGRAPHMATRIX_H
#define DRIECETEDUNWEIGHTEDGRAPHMATRIX_H
#include"../../utils/common.hpp"
using namespace std;
template<typename T>
class DriectedUnWeightedGraphMatrix{
private:
    vector<int>vertices;
    vector<vector<int>>adjMat;
public:
    //���캯��
    DriectedUnWeightedGraphMatrix(const vector<int>&vertices,const vector<vector<int>>&edges){
        
        for(int val:vertices){
            addVertex(val);
        }
        
        for(const vector<int>&edge:edges){
            addEdge(edge[0],edge[1]);
        }
    }
   //��ȡ���������С
    int size()const{return vertices.size();};
    //��Ӷ���
    void addVertex(int val){
        int n=size();
        //��Ӷ���
        vertices.push_back(val);
        //�ھ��������һ��
        adjMat.emplace_back(n,0);
        //�ھ��������һ��
        for(vector<int>&row:adjMat){
            row.push_back(0);
        }
    }
    //ɾ������
    void removeVertex(int index){
        if((index>=size())){
            throw out_of_range("�����ڴ˶���");
        }
        //ɾ�������еĶ���
        vertices.erase(vertices.begin()+index);
        //ɾ�������е�һ��
        adjMat.erase(adjMat.begin()+index);
        //ɾ�������е�һ��
        for(vector<int>&row:adjMat){
            row.erase(row.begin()+index);
        }
    }
    //��ӱ�
    void addEdge(int i,int j){

        if(i<0||j<0||i>=size()||j>=size()||i==j){
            throw out_of_range(" �����ڴ˶���");
        }

        adjMat[i][j]=1;
    }
    //ɾ����
    void removeEdge(int i,int j){
        if(i<0||j<0||i>=size()||j>=size()||i==j){
            throw out_of_range(" �����ڴ˶���");
        }
        adjMat[i][j]=0;
    }
    //��ӡ
    void print(){
        cout<<" ���� = ";
        printVector(vertices);
        cout<<" �ڽӾ��� = ";
        printVectorMatrix(adjMat);
    }
};




#endif