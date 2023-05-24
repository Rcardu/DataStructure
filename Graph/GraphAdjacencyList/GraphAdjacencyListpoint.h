#ifndef GRAPHADJACENCYLISTPOINT_H
#define GRAPHADJACENCYLISTPOINT_H
#include"..//..//utils//common.hpp"
template<typename T>
class GraphAdjacencyListpoint
{
private:
public:
    //�ڽӱ�key�����㣬value���ö���������ڽӵ�
    unordered_map<Vertex*,vector<Vertex*>>adjList;
    /*��vector��ɾ��ָ�����*/
    void remove(vector<Vertex*>&vec,Vertex*vet){
        //在vec数组�?删除顶点vet
        for(int i=0;i<vec.size();i++){//�����ڽӵ�����
            if(vec[i]==vet){//�ҵ���Ӧ�ڽӵ㣬��ɾ��
                vec.erase(vec.begin()+i);
                break;
            }
        }
    }
    /*���췽��*/
    GraphAdjacencyListpoint(const vector<vector<Vertex*>>&edges){
        for(const auto&edge:edges){
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0],edge[1]);
        }
    }
    /*��ӱ�*/
    void addEdge(Vertex*v1,Vertex*v2){
        if(!adjList.count(v1)||!adjList.count(v2)||v1==v2)
            throw out_of_range("�����ڴ˽��");
        //��ӱ�vet1��vet2
        adjList[v1].push_back(v2);
    }
    //ɾ����
    void removeEdge(Vertex*v1,Vertex*v2){
        if(!adjList.count(v1)||!adjList.count(v2)||v2==v1)
            throw out_of_range("�����ڴ˶���");
        remove(adjList[v1],v2);
    }
    /*��Ӷ���*/
    void addVertex(Vertex*vet){
        if(adjList.count(vet))return;
        adjList[vet]=vector<Vertex*>();
    }
    /*ɾ������*/
    void removeVertex(Vertex*vet){
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
            printVector(vetsToVals(vec));
        }
    }
    /*����ͼ�Ĺ�����ȱ���*//*�����ڽ��������Ͷ�����ʼ��*/
    vector<Vertex*>graphBFS(GraphAdjacencyListpoint&graph,Vertex*strat){
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
    void dfs(GraphAdjacencyListpoint&graph,unordered_set<Vertex*>&visited,vector<Vertex*>&res,Vertex*vet){
        res.push_back(vet);//��¼���ʶ���
        visited.emplace(vet);//����ѷ���
        //�����ö���������ڽӶ���
        for(auto adjMat:graph.adjList[vet]){
            if(visited.count(adjMat))
            continue;//�����ѱ����ʵĶ���
            dfs(graph,visited,res,adjMat);
        }
    }
    /*�����������������*/
    vector<Vertex*>graphDFS(GraphAdjacencyListpoint&graph,Vertex*start){
        vector<Vertex*>res;
        unordered_set<Vertex*>visited;
        dfs(graph,visited,res,start);
        return res;
    }
};






#endif 