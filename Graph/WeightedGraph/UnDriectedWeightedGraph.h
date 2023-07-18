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
    unordered_map<VertexPoint*,vector<VertexPoint*>>adjList;
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
    UnDriectedWeightedGraph(const vector<vector<VertexPoint*>>&edges){
        for(const auto&edge:edges){
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0],edge[1]);
        }
    }
    /*��ӱ�*/
    void addEdge(VertexPoint*v1,VertexPoint*v2){
        if(!adjList.count(v1)||!adjList.count(v2)||v1==v2)
            throw out_of_range("�����ڴ˽��");
        //��ӱ�vet1��vet2
        adjList[v1].push_back(v2);
        adjList[v2].push_back(v1);
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
        adjList[vet]=vector<VertexPoint*>();
    }
    /*ɾ������*/
    void removeVertex(VertexPoint*vet){
        if(!adjList.count(vet))
            throw out_of_range("�����ڴ˶���");
        adjList.erase(vet);
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
                que.push(adjVet);//���˶������
                visited.emplace(adjVet);//��¼�˶���
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
            if(visited.count(adjMat))
            continue;//�����ѱ����ʵĶ���
            UnDriectedWeightedGraphDFS(graph,visited,res,adjMat);
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