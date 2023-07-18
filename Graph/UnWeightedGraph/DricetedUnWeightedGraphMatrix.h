/*有向无权图(邻接矩阵)*/
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
    //构造函数
    DriectedUnWeightedGraphMatrix(const vector<int>&vertices,const vector<vector<int>>&edges){
        
        for(int val:vertices){
            addVertex(val);
        }
        
        for(const vector<int>&edge:edges){
            addEdge(edge[0],edge[1]);
        }
    }
   //获取顶点数组大小
    int size()const{return vertices.size();};
    //添加顶点
    void addVertex(int val){
        int n=size();
        //添加顶点
        vertices.push_back(val);
        //在矩阵中添加一行
        adjMat.emplace_back(n,0);
        //在矩阵中添加一列
        for(vector<int>&row:adjMat){
            row.push_back(0);
        }
    }
    //删除顶点
    void removeVertex(int index){
        if((index>=size())){
            throw out_of_range("不存在此顶点");
        }
        //删除数组中的顶点
        vertices.erase(vertices.begin()+index);
        //删除矩阵中的一行
        adjMat.erase(adjMat.begin()+index);
        //删除矩阵中的一列
        for(vector<int>&row:adjMat){
            row.erase(row.begin()+index);
        }
    }
    //添加边
    void addEdge(int i,int j){

        if(i<0||j<0||i>=size()||j>=size()||i==j){
            throw out_of_range(" 不存在此顶点");
        }

        adjMat[i][j]=1;
    }
    //删除边
    void removeEdge(int i,int j){
        if(i<0||j<0||i>=size()||j>=size()||i==j){
            throw out_of_range(" 不存在此顶点");
        }
        adjMat[i][j]=0;
    }
    //打印
    void print(){
        cout<<" 顶点 = ";
        printVector(vertices);
        cout<<" 邻接矩阵 = ";
        printVectorMatrix(adjMat);
    }
};




#endif