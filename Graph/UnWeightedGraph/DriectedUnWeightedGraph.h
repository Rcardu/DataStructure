/*有向无权图(邻接表)*/
#ifndef DRIECTEDUNWEIGHTEDGRAPH_H
#define DRIECTEDUNWEIGHTEDGRAPH_H
#include"../../utils/common.hpp"
#include "UnDriectedUnWeightedGraph.h"
template<typename T>
class DriectedUnWeightedGraph{
private:
public:
    //邻接表，key：顶点，value：该顶点的所有邻接点
    unordered_map<Vertex*,vector<Vertex*>>adjList;
    /*在vector中删除指定结点*/
    void remove(vector<Vertex*>&vec,Vertex*vet){
        for(int i=0;i<vec.size();i++){//遍历邻接点数组
            if(vec[i]==vet){//找到对应邻接点，就删除
                vec.erase(vec.begin()+i);
                break;
            }
        }
    }
    /*构造方法*/
    DriectedUnWeightedGraph(const vector<vector<Vertex*>>&edges){
        //添加所有顶点和边
        for(const vector<Vertex*>&edge:edges){//遍历数组中的数组
            addVertex(edge[0]);                 //即edge从下标0到下标n
            addVertex(edge[1]);
            addEdge(edge[0],edge[1]);
        }
    }
    /*获取顶点数量*/
    int size(){return adjList.size();};
    /*添加边*/
    void addEdge(Vertex*vet1,Vertex*vet2){
        if(!adjList.count(vet1)||!adjList.count(vet2)||vet1==vet2){
            throw out_of_range("不存在此顶点");
        }
        //添加边vet1，vet2
        adjList[vet1].push_back(vet2);
    }
    //删除边
    void removeEdge(Vertex*vet1,Vertex*vet2){
        if(!adjList.count(vet1)||!adjList.count(vet2)||vet1==vet2){
            throw out_of_range("不存在此顶点");
        }
        remove(adjList[vet1],vet2);
    }
    /*添加顶点*/
    void addVertex(Vertex*vet){
        if(adjList.count(vet))return;//已经存在此顶点
        //在邻接链表中添加一个新链表
        adjList[vet]=vector<Vertex*>();
    }
    /*删除顶点*/
    void removeVertex(Vertex*vet){
        if(!adjList.count(vet))
            throw out_of_range("不存在此顶点");
        //在邻接链表中删除顶点 vet 对应的链表
        adjList.erase(vet);
        //遍历其他顶点的链表，删除含有vet的边
        for(auto&adj:adjList){
            remove(adj.second,vet);
        }
    }
    /*打印邻接表*/
    void print(){
        cout<<"邻接表 = "<<endl;
        for(auto&adj:adjList){
            const auto&key=adj.first;
            const auto&vec=adj.second;
            cout<<key->val<<": ";
            printVector(vetsToVals(vec));
        }
    }
private:
    /*无向图的广度优先遍历*//*传入邻接链表对象和顶点起始点*/
    vector<Vertex*>DriectedUnWeightedGraphBFS(DriectedUnWeightedGraph&graph,Vertex*strat){
        /*使用队列来进行广度优先遍历，使用哈希set来防止重复遍历*/
        vector<Vertex*>res;
        queue<Vertex*>que;
        que.push(strat);
        unordered_set<Vertex*>visited={strat};//进队，记录此顶点
        while(!que.empty()){
            Vertex*vet=que.front();
            que.pop();//队首顶点出队
            res.push_back(vet);//记录访问结点
            for(auto adjVet:graph.adjList[vet]){//遍历adjList[vet]顶点的每个数组元素
                if(visited.count(adjVet))//如果已经遍历过，就跳过此顶点
                continue;
                que.push(adjVet);//将此顶点入队
                visited.emplace(adjVet);//记录此顶点
            }
        }
        //返回顶点序列
        return res;
    }
    /*无向图的深度优先遍历,递归*/
    void DriectedUnWeightedGraphDFS(DriectedUnWeightedGraph&graph,unordered_set<Vertex*>&visited,vector<Vertex*>&res,Vertex*vet){
        res.push_back(vet);//记录访问顶点
        visited.emplace(vet);//标记已访问
        //遍历该顶点的所有邻接顶点
        for(auto adjMat:graph.adjList[vet]){
            if(visited.count(adjMat))
            continue;//跳过已被访问的顶点
            DriectedUnWeightedGraphDFS(graph,visited,res,adjMat);
        }
    }
public:
    /*广度优先遍历*/
    vector<int>DriectedUnWeightedGraphBFSIn(DriectedUnWeightedGraph&graph,Vertex*strat){
        return vetsToVals(DriectedUnWeightedGraphBFS(graph,strat));
    }
    /*深度优先遍历*/
    vector<int>DriectedUnWeightedGraphDFSIn(DriectedUnWeightedGraph&graph,Vertex*start){
        vector<Vertex*>res;
        unordered_set<Vertex*>visited;
        DriectedUnWeightedGraphDFS(graph,visited,res,start);
        return vetsToVals(res);
    }

};



#endif