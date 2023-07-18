/*������Ȩͼ�����·���㷨*/
#ifndef UNDRIECTEDUNWEIGHTEDGRAPHSHORTPATH_H
#define UNDRICETEDUNWEIGHTEDGRAPHSHORTPATH_H
#include "../../utils/common.hpp"
#include"UnDriectedUnWeightedGraph.h"
/*�������ݽṹ�����������������ʼ�ڵ�ľ��롢·��*/
struct Preparations{
    bool visit;//�������
    int dist;//����
    Vertex* paths;//·��
    Preparations():visit(false),dist(INT_MAX),paths(nullptr){

    }
};
template<typename T>
class UnDriectedUnWeightedGraphShortPath{
private:
    unordered_map<Vertex*,Preparations*>State;
public:
    //���캯�������ṹ�����ʼ����������ʼ�ڵ�ķ����������Ϊ��,����Ϊ0
    UnDriectedUnWeightedGraphShortPath(const vector<Vertex*>ver){
        for(int i=0;i<ver.size();i++){
            State[ver[i]]=new Preparations();
        }
    }
    /*����*/
    ~UnDriectedUnWeightedGraphShortPath(){
        for(auto&stl:State){
            delete stl.second;
        }
    }
    /*��ʼ�������·��*/
    /*������ʼ�ڵ�������Լ�ͼ���󣬷���һ���ṹ������ʾ���*/
    vector<Preparations*>Iterations(UnDriectedUnWeightedGraph<int>&graph,Vertex* start){
        //��ʼ����ʼ�ڵ�
        State[start]->visit=true;
        State[start]->dist=0;
        //ʹ�ö��н��б���Ѱ��
        queue<Vertex*>que;//���м�¼�ڵ������
        //��¼�����
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
    /*Ѱ�������ڵ�֮������·��*/
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
    /*��ӡ����*/
    void print(){
        cout<<"·���� = "<<endl;
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