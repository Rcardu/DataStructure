#ifndef DRIECTEDWEIGHTEDGRAPHPATH_H
#define DRIECTEDWEIGHTEDGRAPHPATH_H
#include "../../utils/common.hpp"
#include "DriectedWeighitedGraph.h"
#include "VertexPiont.h"
using namespace std;
struct PathValue{
    int dist;
    VertexPoint*path;
    PathValue():dist(INT_MAX),path(nullptr){

    }
};
struct cmps{
    bool operator()(pair<VertexPoint*,int>&a,pair<VertexPoint*,int>&b){
        return a.second>b.second;
    }
};
template<typename T>
class DriectedWeightedGraphPath{
private:
    unordered_map<VertexPoint*,PathValue*>PathList;
public:
    DriectedWeightedGraphPath(const vector<VertexPoint*>vertex){
        for(VertexPoint*ver:vertex){
            PathList[ver]=new PathValue();
        }
    }
    ~DriectedWeightedGraphPath(){
        for(auto&Pat:PathList){
            delete Pat.second;
        }
    }

    /*使用优先队列来遍历寻找有权图中的最短路径*/
    void Iterations(DriectedWeightedGraph<int>&graph,VertexPoint*start){
        //修改起点路径值为0
        PathList[start]->dist=0;
        //使用pair来填充优先队列
        pair<VertexPoint*,int>ves(start,PathList[start]->dist);
        //创建优先队列
        priority_queue<pair<VertexPoint*,int>,vector<pair<VertexPoint*,int>>,cmps>que;
        que.push(ves);
        while(!que.empty()){
            pair<VertexPoint*,int>index=que.top();
            que.pop();
            for(auto&grp:graph.duList[index.first]){
                if(PathList[grp.first]->dist<PathList[index.first]->dist+grp.second)
                continue;
                //如果当前最短路径值大于新的最短路径值，就修改当前路径为新的路径值
                PathList[grp.first]->dist=PathList[index.first]->dist+grp.second;
                //并将当前路径改为新路径
                PathList[grp.first]->path=index.first;
                ves.first=grp.first;
                ves.second=PathList[grp.first]->dist;
                que.push(ves);
            }
        }
        return;
    }
    /*输入表的起始与终止结点，获得路径*/
    vector<VertexPoint*>GetPath(VertexPoint*start,VertexPoint*end){
        VertexPoint*find=end;
        vector<VertexPoint*>res;
        while(find!=start){
            res.push_back(find);
            find=PathList[find]->path;
        }
        res.push_back(find);
        return res;
    }
    /*使用优先队列来遍历寻找有权图中的最短路径*/
    void IterationsDist(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,VertexPoint*start){
        //修改起点路径值为0
        PathList[start]->dist=0;
        //使用pair来填充优先队列
        pair<VertexPoint*,int>ves(start,PathList[start]->dist);
        //创建优先队列
        priority_queue<pair<VertexPoint*,int>,vector<pair<VertexPoint*,int>>,cmps>que;
        que.push(ves);
        while(!que.empty()){
            pair<VertexPoint*,int>index=que.top();
            que.pop();
            for(auto&grp:CopysList[index.first]){
                if(PathList[grp.first]->dist<PathList[index.first]->dist+grp.second&&grp.second==0)
                continue;
                //如果当前最短路径值大于新的最短路径值，就修改当前路径为新的路径值
                PathList[grp.first]->dist=PathList[index.first]->dist+grp.second;
                //并将当前路径改为新路径
                PathList[grp.first]->path=index.first;
                ves.first=grp.first;
                ves.second=PathList[grp.first]->dist;
                que.push(ves);
            }
        }
        return;
    }
    /*输入表的起始与终止结点，获得路径*/
    vector<VertexPoint*>GetPathDist(VertexPoint*start,VertexPoint*end){
        VertexPoint*find=end;
        vector<VertexPoint*>res;
        if(PathList[end]->dist==0)return res;
        while(find!=start){
            res.push_back(find);
            find=PathList[find]->path;
        }
        res.push_back(find);
        return res;
    }
    
    /*打印表*/
    void print(){
        cout<<"路径表 = "<<endl;
        for(auto&pat:PathList){
            const auto&key=pat.first;
            const auto&val=pat.second;
            cout<<key->val<<" "<<val->dist<<" ";
            if(val->path==nullptr)cout<<0<<endl;
            else cout<<val->path->key<<endl;
        }
    }


};


#endif