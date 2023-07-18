/*无向有权图邻接表*/
#ifndef UNDRIECTEDWEIGHTEDGRAPH_H
#define UNDRIECTEDWEIGHTEDGRAPH_H
#include"..//..//utils//common.hpp"
#include"VertexPiont.h"
template<typename T>
class UnDriectedWeightedGraph
{
private:
public:
    //邻接表，key：顶点，value：该顶点的所有邻接点
    unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>adjList;
    /*在vector中删除指定结点*/
    void remove(vector<VertexPoint*>&vec,VertexPoint*vet){
        for(int i=0;i<vec.size();i++){//遍历邻接点数组
            if(vec[i]==vet){//找到对应邻接点，就删除
                vec.erase(vec.begin()+i);
                break;
            }
        }
    }
    /*构造方法*/
    UnDriectedWeightedGraph(const vector<pair<pair<VertexPoint*,VertexPoint*>,int>>&edges){
        for(const auto&edge:edges){
            addVertex(edge.first.first);
            addVertex(edge.first.second);
            pair<VertexPoint*,int>vecs(edge.first.second,edge.second);
            addEdge(edge.first.first,vecs);
        }
    }
    /*添加边*/
    void addEdge(VertexPoint*v1,pair<VertexPoint*,int>vecs){
        if(!adjList.count(v1)||!adjList.count(vecs.first)||v1==vecs.first)
            throw out_of_range("不存在此结点");
        //添加边vet1，vet2
        adjList[v1].push_back(vecs);
        adjList[vecs.first].push_back(<v1,vecs.second>);
    }
    //删除边
    void removeEdge(VertexPoint*v1,VertexPoint*v2){
        if(!adjList.count(v1)||!adjList.count(v2)||v2==v1)
            throw out_of_range("不存在此顶点");
        remove(adjList[v1],v2);
        remove(adjList[v2],v1);
    }
    /*添加顶点*/
    void addVertex(VertexPoint*vet){
        if(adjList.count(vet))return;
        adjList[vet]=vector<pair<VertexPoint*,int>>();
    }
    /*删除顶点*/
    void removeVertex(VertexPoint*vet){
        if(!adjList.count(vet))
            throw out_of_range("不存在此顶点");
        adjList.erase(vet);
        for(auto&adj:adjList){
            remove(adj.first,vet);
        }
    }
    /*打印邻接表*/
    void print(){
        cout<<"邻接表 = "<<endl;
        for(auto&adj:adjList){
            const auto&key=adj.first;
            const auto&vec=adj.second;
            cout<<key->val<<": ";
            printSforTwo(vetsTovalsl(vec));
        }
    }
private:
    /*无向图的广度优先遍历*//*传入邻接链表对象和顶点起始点*/
    vector<VertexPoint*>UnDriectedWeightedGraphBFS(UnDriectedWeightedGraph&graph,VertexPoint*strat){
         /*使用队列来进行广度优先遍历，使用哈希set来防止重复遍历*/
        vector<VertexPoint*>res;
        queue<VertexPoint*>que;
        que.push(strat);
        unordered_set<VertexPoint*>visited={strat};//进队，记录此顶点
        while(!que.empty()){
            VertexPoint*vet=que.front();
            que.pop();//队首顶点出队
            res.push_back(vet);//记录访问结点
            for(auto adjVet:graph.adjList[vet]){//遍历adjList[vet]顶点的每个数组元素
                if(visited.count(adjVet))//如果已经遍历过，就跳过此顶点
                continue;
                que.push(adjVet.first);//将此顶点入队
                visited.emplace(adjVet.first);//记录此顶点
            }
        }
        //返回顶点序列
        return res;
    }
    /*无向图的深度优先遍历,递归*/
    void UnDriectedWeightedGraphDFS(UnDriectedWeightedGraph&graph,unordered_set<VertexPoint*>&visited,vector<VertexPoint*>&res,VertexPoint*vet){
        res.push_back(vet);//记录访问顶点
        visited.emplace(vet);//标记已访问
        //遍历该顶点的所有邻接顶点
        for(auto adjMat:graph.adjList[vet]){
            if(visited.count(adjMat.first))
            continue;//跳过已被访问的顶点
            UnDriectedWeightedGraphDFS(graph,visited,res,adjMat.first);
        }
    }
public:
    /*无向有权图的广度优先遍历*/
    vector<vector<int>>UnDriectedWeightedGraphBFSIn(UnDriectedWeightedGraph&graph,VertexPoint*start){
        return vetsTovalsl(UnDriectedWeightedGraphBFS(graph,start));
    }
    /*无向有权图的深度优先遍历*/
    vector<vector<int>>UnDriectedWeightedGraphDFSIn(UnDriectedWeightedGraph&graph,VertexPoint*start){
        vector<VertexPoint*>res;
        unordered_set<VertexPoint*>visited;
        UnDriectedWeightedGraphDFS(graph,visited,res,start);
        return vetsTovalsl(res);
    }
    
};






#endif 