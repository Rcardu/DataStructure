/*����������*/
#ifndef NETWORKFLOWPROBL_H
#define NETWORKFLOWPROBL_H
#include"../../utils/common.hpp"
#include"DriectedWeighitedGraph.h"
#include"DriectedWeightedGraphPath.h"
#include"VertexPiont.h"
class NetWorkFlowProbl{
private:
    unordered_map<VertexPoint*,vector<pair<VertexPoint*,pair<int,int>>>>NetFlow;
public:
/*�������������*/
    void NetWorkPro(DriectedWeightedGraph<int>&graph,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>vertex){
        NetWorkProblems(CopysList,start,end,vertex);
        for(VertexPoint*&ver:vertex){
            vector<int>dist;
            for(auto&Gra:graph.duList[ver]){
                dist.push_back(Gra.second);
            }
            int i=0;
            for(auto&copy:CopysList[ver]){
                pair<VertexPoint*,pair<int,int>>temp;
                temp.first=copy.first;
                temp.second.first=dist[i];
                temp.second.second=dist[i]-copy.second;
                NetFlow[ver].push_back(temp);
                i++;
            }
        }
    }
    /*����������*/
    void NetWorkProblems(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>vertex){
        DriectedWeightedGraphPath<int>PathGraph(vertex);
        PathGraph.IterationsDist(CopysList,start);
        vector<VertexPoint*>PathAs=PathGraph.GetPathDist(start,end);
        if(PathAs.size()==0)return;
        int MinPath=GetMinPath(CopysList,PathAs);
        if(MinPath==0)return;
        SetPath(CopysList,PathAs,MinPath);
        NetWorkProblems(CopysList,start,end,vertex);
        return;
    }
    /*���Ҵ�·���ϵ���СȨֵ*/
    int GetMinPath(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,vector<VertexPoint*>PathAs){
        int MinPathSize=INT_MAX;
        for(int i=PathAs.size()-1;i>0;i--){
            int Temp;
            for(auto&Grp:CopysList[PathAs[i]]){
                if(Grp.first!=PathAs[i-1])
                continue;
                Temp=Grp.second;
            }
            MinPathSize=min(MinPathSize,Temp);
        }
        return MinPathSize;
    }
    /*�޸Ĵ�·���ϵ�Ȩֵ*/
    void SetPath(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,vector<VertexPoint*>PathAs,int MinPath){
        for(int i=PathAs.size()-1;i>0;i--){
            for(auto&Grp:CopysList[PathAs[i]]){
                if(Grp.first!=PathAs[i-1])
                continue;
                Grp.second=Grp.second-MinPath;
            }
        }
    }
    /*��ǰ��������ֵ*/
    void NetWorkValue(VertexPoint*start){
        int value=0;
        for(auto&Net:NetFlow[start]){
            value+=Net.second.second;
        }
        cout<<"��ǰ��������һ����Ϊ��"<<value;
    }
    /*��ӡ���������*/
    void print(){
        for(auto&Net:NetFlow){
            auto&key=Net.first;
            auto&value=Net.second;
            cout<<key->key<<" = "<<endl;
            for(auto&val:value){
                if(val.first==nullptr)
                continue;
                cout<<val.first->key<<" "<<val.second.first<<" "<<val.second.second<<endl;
            }
            cout<<endl;
        }
    }
};






#endif