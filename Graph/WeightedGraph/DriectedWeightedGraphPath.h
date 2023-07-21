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

    /*ʹ�����ȶ���������Ѱ����Ȩͼ�е����·��*/
    void Iterations(DriectedWeightedGraph<int>&graph,VertexPoint*start){
        //�޸����·��ֵΪ0
        PathList[start]->dist=0;
        //ʹ��pair��������ȶ���
        pair<VertexPoint*,int>ves(start,PathList[start]->dist);
        //�������ȶ���
        priority_queue<pair<VertexPoint*,int>,vector<pair<VertexPoint*,int>>,cmps>que;
        que.push(ves);
        while(!que.empty()){
            pair<VertexPoint*,int>index=que.top();
            que.pop();
            for(auto&grp:graph.duList[index.first]){
                if(PathList[grp.first]->dist<PathList[index.first]->dist+grp.second)
                continue;
                //�����ǰ���·��ֵ�����µ����·��ֵ�����޸ĵ�ǰ·��Ϊ�µ�·��ֵ
                PathList[grp.first]->dist=PathList[index.first]->dist+grp.second;
                //������ǰ·����Ϊ��·��
                PathList[grp.first]->path=index.first;
                ves.first=grp.first;
                ves.second=PathList[grp.first]->dist;
                que.push(ves);
            }
        }
        return;
    }
    /*��������ʼ����ֹ��㣬���·��*/
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
    /*ʹ�����ȶ���������Ѱ����Ȩͼ�е����·��*/
    void IterationsDist(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,VertexPoint*start){
        //�޸����·��ֵΪ0
        PathList[start]->dist=0;
        //ʹ��pair��������ȶ���
        pair<VertexPoint*,int>ves(start,PathList[start]->dist);
        //�������ȶ���
        priority_queue<pair<VertexPoint*,int>,vector<pair<VertexPoint*,int>>,cmps>que;
        que.push(ves);
        while(!que.empty()){
            pair<VertexPoint*,int>index=que.top();
            que.pop();
            for(auto&grp:CopysList[index.first]){
                if(PathList[grp.first]->dist<PathList[index.first]->dist+grp.second&&grp.second==0)
                continue;
                //�����ǰ���·��ֵ�����µ����·��ֵ�����޸ĵ�ǰ·��Ϊ�µ�·��ֵ
                PathList[grp.first]->dist=PathList[index.first]->dist+grp.second;
                //������ǰ·����Ϊ��·��
                PathList[grp.first]->path=index.first;
                ves.first=grp.first;
                ves.second=PathList[grp.first]->dist;
                que.push(ves);
            }
        }
        return;
    }
    /*��������ʼ����ֹ��㣬���·��*/
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
    
    /*��ӡ��*/
    void print(){
        cout<<"·���� = "<<endl;
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