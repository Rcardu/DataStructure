/*������Ȩͼ(�ڽӱ�)*/
#ifndef DRIECTEDUNWEIGHTEDGRAPH_H
#define DRIECTEDUNWEIGHTEDGRAPH_H
#include"../../utils/common.hpp"
#include "UnDriectedUnWeightedGraph.h"
template<typename T>
class DriectedUnWeightedGraph{
private:
public:
    //�ڽӱ�key�����㣬value���ö���������ڽӵ�
    unordered_map<Vertex*,vector<Vertex*>>adjList;
    /*��vector��ɾ��ָ�����*/
    void remove(vector<Vertex*>&vec,Vertex*vet){
        for(int i=0;i<vec.size();i++){//�����ڽӵ�����
            if(vec[i]==vet){//�ҵ���Ӧ�ڽӵ㣬��ɾ��
                vec.erase(vec.begin()+i);
                break;
            }
        }
    }
    /*���췽��*/
    DriectedUnWeightedGraph(const vector<vector<Vertex*>>&edges){
        //������ж���ͱ�
        for(const vector<Vertex*>&edge:edges){//���������е�����
            addVertex(edge[0]);                 //��edge���±�0���±�n
            addVertex(edge[1]);
            addEdge(edge[0],edge[1]);
        }
    }
    /*��ȡ��������*/
    int size(){return adjList.size();};
    /*��ӱ�*/
    void addEdge(Vertex*vet1,Vertex*vet2){
        if(!adjList.count(vet1)||!adjList.count(vet2)||vet1==vet2){
            throw out_of_range("�����ڴ˶���");
        }
        //��ӱ�vet1��vet2
        adjList[vet1].push_back(vet2);
    }
    //ɾ����
    void removeEdge(Vertex*vet1,Vertex*vet2){
        if(!adjList.count(vet1)||!adjList.count(vet2)||vet1==vet2){
            throw out_of_range("�����ڴ˶���");
        }
        remove(adjList[vet1],vet2);
    }
    /*��Ӷ���*/
    void addVertex(Vertex*vet){
        if(adjList.count(vet))return;//�Ѿ����ڴ˶���
        //���ڽ����������һ��������
        adjList[vet]=vector<Vertex*>();
    }
    /*ɾ������*/
    void removeVertex(Vertex*vet){
        if(!adjList.count(vet))
            throw out_of_range("�����ڴ˶���");
        //���ڽ�������ɾ������ vet ��Ӧ������
        adjList.erase(vet);
        //�����������������ɾ������vet�ı�
        for(auto&adj:adjList){
            remove(adj.second,vet);
        }
    }
    /*��ӡ�ڽӱ�*/
    void print(){
        cout<<"�ڽӱ� = "<<endl;
        for(auto&adj:adjList){
            const auto&key=adj.first;
            const auto&vec=adj.second;
            cout<<key->val<<": ";
            printVector(vetsToVals(vec));
        }
    }
private:
    /*����ͼ�Ĺ�����ȱ���*//*�����ڽ��������Ͷ�����ʼ��*/
    vector<Vertex*>DriectedUnWeightedGraphBFS(DriectedUnWeightedGraph&graph,Vertex*strat){
        /*ʹ�ö��������й�����ȱ�����ʹ�ù�ϣset����ֹ�ظ�����*/
        vector<Vertex*>res;
        queue<Vertex*>que;
        que.push(strat);
        unordered_set<Vertex*>visited={strat};//���ӣ���¼�˶���
        while(!que.empty()){
            Vertex*vet=que.front();
            que.pop();//���׶������
            res.push_back(vet);//��¼���ʽ��
            for(auto adjVet:graph.adjList[vet]){//����adjList[vet]�����ÿ������Ԫ��
                if(visited.count(adjVet))//����Ѿ����������������˶���
                continue;
                que.push(adjVet);//���˶������
                visited.emplace(adjVet);//��¼�˶���
            }
        }
        //���ض�������
        return res;
    }
    /*����ͼ��������ȱ���,�ݹ�*/
    void DriectedUnWeightedGraphDFS(DriectedUnWeightedGraph&graph,unordered_set<Vertex*>&visited,vector<Vertex*>&res,Vertex*vet){
        res.push_back(vet);//��¼���ʶ���
        visited.emplace(vet);//����ѷ���
        //�����ö���������ڽӶ���
        for(auto adjMat:graph.adjList[vet]){
            if(visited.count(adjMat))
            continue;//�����ѱ����ʵĶ���
            DriectedUnWeightedGraphDFS(graph,visited,res,adjMat);
        }
    }
public:
    /*������ȱ���*/
    vector<int>DriectedUnWeightedGraphBFSIn(DriectedUnWeightedGraph&graph,Vertex*strat){
        return vetsToVals(DriectedUnWeightedGraphBFS(graph,strat));
    }
    /*������ȱ���*/
    vector<int>DriectedUnWeightedGraphDFSIn(DriectedUnWeightedGraph&graph,Vertex*start){
        vector<Vertex*>res;
        unordered_set<Vertex*>visited;
        DriectedUnWeightedGraphDFS(graph,visited,res,start);
        return vetsToVals(res);
    }

};



#endif