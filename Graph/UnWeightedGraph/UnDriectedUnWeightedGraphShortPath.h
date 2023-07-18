/*无向无权图的最短路径算法*/
#ifndef UNDRIECTEDUNWEIGHTEDGRAPHSHORTPATH_H
#define UNDRICETEDUNWEIGHTEDGRAPHSHORTPATH_H
#include "../../utils/common.hpp"
#include"UnDriectedUnWeightedGraph.h"
/*设置数据结构包含访问情况、与起始节点的距离、路径*/
struct Preparations{
    bool visit;//访问情况
    int dist;//距离
    Vertex* paths;//路径
    Preparations():visit(false),dist(INT_MAX),paths(nullptr){

    }
};
template<typename T>
class UnDriectedUnWeightedGraphShortPath{
private:
    unordered_map<Vertex*,Preparations*>State;
public:
    //构造函数，将结构数组初始化，并将起始节点的访问情况设置为真,距离为0
    UnDriectedUnWeightedGraphShortPath(const vector<Vertex*>ver){
        for(int i=0;i<ver.size();i++){
            State[ver[i]]=new Preparations();
        }
    }
    /*析构*/
    ~UnDriectedUnWeightedGraphShortPath(){
        for(auto&stl:State){
            delete stl.second;
        }
    }
    /*开始计算最短路径*/
    /*输入起始节点的索引以及图对象，返回一个结构表来表示结果*/
    vector<Preparations*>Iterations(UnDriectedUnWeightedGraph<int>&graph,Vertex* start){
        //初始化起始节点
        State[start]->visit=true;
        State[start]->dist=0;
        //使用队列进行遍历寻找
        queue<Vertex*>que;//队列记录节点的索引
        //记录结果集
        vector<Preparations*>res;
        que.push(start);
        while(!que.empty()){
            Vertex* index=que.front();
            que.pop();
            res.push_back(State[index]);
            for(auto&vec:graph.adjList[index]){
                if(State[vec]->visit)
                continue;
                que.push(vec);
                State[vec]->visit=true;
                State[vec]->dist=State[index]->dist+1;
                State[vec]->paths=index;
            }
        }
        return res;
    }    
    /*寻找两个节点之间的最短路径*/
    vector<int>ShortestPath(UnDriectedUnWeightedGraph<int>&graph,Vertex*start,Vertex*end){
        Iterations(graph,start);
        if(State[end]->paths==nullptr){
            return vector<int>(1,0);
        }
        Vertex*finds=end;
        vector<int>res;
        res.push_back(State[end]->dist);
        while(finds!=start){
            res.push_back(finds->val);
            finds=State[finds]->paths;
        }
        res.push_back(start->val);
        return res;
    }
    /*打印函数*/
    void print(){
        cout<<"路径表 = "<<endl;
        for(auto&stl:State){
            const auto&key=stl.first;
            const auto&val=stl.second;
            cout<<key->val<<": ";
            if(val->visit)cout<<"yes"<<" ";
            else cout<<"no"<<" ";
            cout<<val->dist<<" ";
            if(val->paths==nullptr){
                cout<<0;
            }else{
                cout<<val->paths->val;
            }
            cout<<endl;
        }
    }

};





#endif