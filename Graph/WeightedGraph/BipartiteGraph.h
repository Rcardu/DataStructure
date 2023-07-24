/*二部图及其算法*/
#ifndef BIPARTITEGRAPH_H
#define BIPARTITEGRAPH_H
#include "../../utils/common.hpp"
#include "VertexPiont.h"
class BipartiteGraph{
private:



public:
    bool BipartitedGraphCast(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&Graph,vector<VertexPoint*>vertex){
       unordered_set<VertexPoint*>set;
       queue<VertexPoint*>que;
       que.push(vertex[0]);
       vertex[0]->val=0;
       set.emplace(vertex[0]);
       while(!que.empty()){
        VertexPoint*ver=que.front();
        que.pop();
        for(auto&Gra:Graph[ver]){
            if(set.count(Gra.first)){
                if(Gra.first->val==ver->val)return false;
                else continue;
            }
            Gra.first->val=(ver->val+1)%2;
            que.push(Gra.first);
            set.emplace(Gra.first);
        }
       }
       return true;
    }
    /*将二部图转化为结点集合*/
    void InputTandS(vector<VertexPoint*>&S,vector<VertexPoint*>&T,vector<VertexPoint*>vertex){
        for(VertexPoint*ver:vertex){
            if(ver->val==0)S.push_back(ver);
            else T.push_back(ver);
        }
    }
};









#endif