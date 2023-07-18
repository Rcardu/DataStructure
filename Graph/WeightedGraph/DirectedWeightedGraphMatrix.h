/*有向图有权图的邻接矩阵*/
#ifndef DIRECTEDWEIGHTEDGRAPHMATRIX_H
#define DIRECTEDWEIGHTEDGRAPHMATRIX_H
#include"../../utils/common.hpp"
template<typename T>
class DriectedWeightedGraphMatrix{
/*基础数据*/
private:
    vector<int>Adjacency;//顶点列表
    vector<vector<int>>Matrix;//邻接矩阵
private:
    /*图的广度优先遍历*/
    /*
  [0, 1, 0, 2, 0],
  [0, 0, 3, 0, 0],
  [0, 0, 0, 1, 5],
  [2, 0, 0, 0, 1],
  [0, 0, 1, 0, 0]
    */
    /*从起始顶点开始，使用索引来进行遍历
    将索引对应的顶点值填入结果集中
    索引进入队列并且进入哈希表
    使用索引来创建每个顶点所对应的行数组
    并对数组中的值进行判定，即为0时没有单向关系，或者当数组中的单向关系存在
    但其索引已经在哈希表中出现，说明此索引所对应的值已被遍历*/
    vector<int>MatrixBFS(DriectedWeightedGraphMatrix&graph,int index){
        //哈希表，记录已被遍历的索引
        unordered_set<int>visits={index};
        //队列模拟广度优先
        queue<int>que;
        //结果集
        vector<int>res;
        //将第一个索引入队
        que.push(index);
        while(!que.empty()){//队列为空时表示遍历结束
            index=que.front();//取索引来进行下一个遍历的顶点
            que.pop();
            res.push_back(graph.Adjacency[index]);//将结果加入结果集
            //使用一个数组来取当前索引的邻接矩阵中的一行
            vector<int>ThisNum(graph.Matrix[index].begin(),graph.Matrix[index].end());
            int i=0;//使用索引来遍历着一行
            for(int Adj:ThisNum){//遍历整个数组
                if(Adj==0||visits.count(i)){//当前矩阵点为0没有单向关系，当前矩阵点的索引已存在
                    i++;
                    continue;
                }
                que.push(i);//未被遍历的索引入队
                visits.emplace(i);//加入哈希表
                i++;
            }
        }
        return res;
    }
    /*有向图的深度优先遍历*/
    /*使用递归，包括递归对象、哈希表、递归索引、结果集*/
    void MatrixDFS(DriectedWeightedGraphMatrix&graph,unordered_set<int>&visits,int index,vector<int>&res){
        res.push_back(graph.Adjacency[index]);
        visits.emplace(index);
        for(int i=0;i<graph.Matrix[index].size();i++){
            if(graph.Adjacency[i]==0||visits.count(i))
            continue;
            MatrixDFS(graph,visits,i,res);
        }
    }
public:
    /*构造方法*/
    DriectedWeightedGraphMatrix(const vector<int>&Adj,const vector<vector<int>>&Mat){
        //添加顶点
        for(int val:Adj){
           addVertexMat(val);
        }
        //添加边
        for(const vector<int>&edge:Mat){
            addEdgeMat(edge[0],edge[1],edge[2]);
        }
    }
    /*获取顶点数量*/
    int size(){return Adjacency.size();};
    /*添加顶点*/
    void addVertexMat(int val){
        int n=size();//此顶点的数量
        //向顶点列表中添加新的顶点的值
        Adjacency.push_back(val);
        //添加行
        Matrix.emplace_back(n,0);
        //添加列
        for(vector<int>&Mat:Matrix){
            Mat.push_back(0);
        }
    }
    /*添加边*/
    /*要添加的边的索引,以及权值*/
    void addEdgeMat(int i,int j,int vals){
        //索引越界与相等处理
        if(i<0||j<0||i>=size()||j>=size()||i==j){
            throw out_of_range("顶点不存在");
        }
        //有向图，只添加一个边以及权值
        Matrix[i][j]=vals;
    }
    /*删除顶点*/
    void removeVertexMat(int index){
        if((index>=size())){
            throw out_of_range("顶点不存在");
        }
        //在顶点列表上移除此顶点
        Adjacency.erase(Adjacency.begin()+index);
        //再矩阵中删除此行
        Matrix.erase(Matrix.begin()+index);
        //在矩阵中删除这一列
        for(auto&Mat:Matrix){
            Mat.erase(Mat.begin()+index);
        }
    }
    /*删除边*/
    /*边的索引坐标*/
    void removeEdgeMat(int i,int j){
        if(i<0||j<0||i>=size()||j>=size()||i=j){
            throw out_of_range("索引错误");
        }
        Matrix[i][j]=0;
    }
    /*打印邻接数组*/
    void print(){
        cout<<" 顶点列表 = ";
        printVector(Adjacency);
        cout<<" 邻接矩阵 = ";
        printVectorMatrix(Matrix);
    }
    /*广度优先遍历*/
    vector<int>GraphBFSMat(DriectedWeightedGraphMatrix&graph,int start){
        return MatrixBFS(graph,start);
    }
    /*深度优先遍历*/
    vector<int>GraphDFSMat(DriectedWeightedGraphMatrix&graph,int index){
        vector<int>res;
        unordered_set<int>visits;
        MatrixDFS(graph,visits,index,res);
        return res;
    }
};





#endif