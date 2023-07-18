/*������Ȩͼ�ڽӱ�*/
#ifndef UNDRIECTEDWEIGHTEDGRAPH_H
#define UNDRIECTEDWEIGHTEDGRAPH_H
#include"..//..//utils//common.hpp"
#include"VertexPiont.h"
template<typename T>
class UnDriectedWeightedGraph
{
private:
public:
    //�ڽӱ�key�����㣬value���ö���������ڽӵ�
    unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>adjList;
    /*��vector��ɾ��ָ�����*/
    void remove(vector<VertexPoint*>&vec,VertexPoint*vet){
        for(int i=0;i<vec.size();i++){//�����ڽӵ�����
            if(vec[i]==vet){//�ҵ���Ӧ�ڽӵ㣬��ɾ��
                vec.erase(vec.begin()+i);
                break;
            }
        }
    }
    /*���췽��*/
    UnDriectedWeightedGraph(const vector<pair<pair<VertexPoint*,VertexPoint*>,int>>&edges){
        for(const auto&edge:edges){
            addVertex(edge.first.first);
            addVertex(edge.first.second);
            pair<VertexPoint*,int>vecs(edge.first.second,edge.second);
            addEdge(edge.first.first,vecs);
        }
    }
    /*��ӱ�*/
    void addEdge(VertexPoint*v1,pair<VertexPoint*,int>vecs){
        if(!adjList.count(v1)||!adjList.count(vecs.first)||v1==vecs.first)
            throw out_of_range("�����ڴ˽��");
        //��ӱ�vet1��vet2
        adjList[v1].push_back(vecs);
        adjList[vecs.first].push_back(<v1,vecs.second>);
    }
    //ɾ����
    void removeEdge(VertexPoint*v1,VertexPoint*v2){
        if(!adjList.count(v1)||!adjList.count(v2)||v2==v1)
            throw out_of_range("�����ڴ˶���");
        remove(adjList[v1],v2);
        remove(adjList[v2],v1);
    }
    /*��Ӷ���*/
    void addVertex(VertexPoint*vet){
        if(adjList.count(vet))return;
        adjList[vet]=vector<pair<VertexPoint*,int>>();
    }
    /*ɾ������*/
    void removeVertex(VertexPoint*vet){
        if(!adjList.count(vet))
            throw out_of_range("�����ڴ˶���");
        adjList.erase(vet);
        for(auto&adj:adjList){
            remove(adj.first,vet);
        }
    }
    /*��ӡ�ڽӱ�*/
    void print(){
        cout<<"�ڽӱ� = "<<endl;
        for(auto&adj:adjList){
            const auto&key=adj.first;
            const auto&vec=adj.second;
            cout<<key->val<<": ";
            printSforTwo(vetsTovalsl(vec));
        }
    }
private:
    /*����ͼ�Ĺ�����ȱ���*//*�����ڽ��������Ͷ�����ʼ��*/
    vector<VertexPoint*>UnDriectedWeightedGraphBFS(UnDriectedWeightedGraph&graph,VertexPoint*strat){
         /*ʹ�ö��������й�����ȱ�����ʹ�ù�ϣset����ֹ�ظ�����*/
        vector<VertexPoint*>res;
        queue<VertexPoint*>que;
        que.push(strat);
        unordered_set<VertexPoint*>visited={strat};//���ӣ���¼�˶���
        while(!que.empty()){
            VertexPoint*vet=que.front();
            que.pop();//���׶������
            res.push_back(vet);//��¼���ʽ��
            for(auto adjVet:graph.adjList[vet]){//����adjList[vet]�����ÿ������Ԫ��
                if(visited.count(adjVet))//����Ѿ����������������˶���
                continue;
                que.push(adjVet.first);//���˶������
                visited.emplace(adjVet.first);//��¼�˶���
            }
        }
        //���ض�������
        return res;
    }
    /*����ͼ��������ȱ���,�ݹ�*/
    void UnDriectedWeightedGraphDFS(UnDriectedWeightedGraph&graph,unordered_set<VertexPoint*>&visited,vector<VertexPoint*>&res,VertexPoint*vet){
        res.push_back(vet);//��¼���ʶ���
        visited.emplace(vet);//����ѷ���
        //�����ö���������ڽӶ���
        for(auto adjMat:graph.adjList[vet]){
            if(visited.count(adjMat.first))
            continue;//�����ѱ����ʵĶ���
            UnDriectedWeightedGraphDFS(graph,visited,res,adjMat.first);
        }
    }
public:
    /*������Ȩͼ�Ĺ�����ȱ���*/
    vector<vector<int>>UnDriectedWeightedGraphBFSIn(UnDriectedWeightedGraph&graph,VertexPoint*start){
        return vetsTovalsl(UnDriectedWeightedGraphBFS(graph,start));
    }
    /*������Ȩͼ��������ȱ���*/
    vector<vector<int>>UnDriectedWeightedGraphDFSIn(UnDriectedWeightedGraph&graph,VertexPoint*start){
        vector<VertexPoint*>res;
        unordered_set<VertexPoint*>visited;
        UnDriectedWeightedGraphDFS(graph,visited,res,start);
        return vetsTovalsl(res);
    }
    
};






#endif 