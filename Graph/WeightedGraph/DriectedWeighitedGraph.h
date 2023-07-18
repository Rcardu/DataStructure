/*������Ȩͼ*/
#ifndef DIRECTEDWEIGHTITEDGRAPH_H
#define DIRECTEDWEIGHTITEDGRAPH_H
#include"../../utils/common.hpp"
#include"VertexPiont.h"
template<typename T>
class DriectedWeightedGraph{
private:
    //����һ�������ڽӱ�ʹ��map����Ŷ����Լ��ڽӶ���
    unordered_map<VertexPoint*,vector<VertexPoint*>>duList;
        /*����ͼ�Ĺ�����ȱ���*/
    /*��������ͼ���ڽӱ����ʼ����*/
    /*ʹ�ö��������й�����ȱ���
    ����:1 --> 2,4,5
        2 --> 3,4
        3 --> 4,5
        4 --> 5
        ���Ƚ�1��Ӳ��ù�ϣ���¼�˶��㣬Ȼ���ٽ���ʼ���������������еĲ�����
        ʹ��ѭ������������һ���ڽӶ��㣬���������ͬʱ�жϵ�ǰ�����Ƿ��Ѿ���ɱ���
        ��Ѻ�ʹ�ù�ϣ���¼�˶���
        �������
        1 2 4 5 3 
         */
    vector<VertexPoint*>GraphBFS(DriectedWeightedGraph&graph,VertexPoint*start){
        queue<VertexPoint*>que;//����˳��
        vector<VertexPoint*>res;//�������
        que.push(start);//����ʼ�������
        unordered_set<VertexPoint*>visited={start};//��¼��ǰ��ӵĽڵ�
        while(!que.empty()){
            VertexPoint*vet=que.front();//ѡȡ�����еĵ�һ���ڵ�
            que.pop();//����
            res.push_back(vet);//��¼���
            for(auto dulists:graph.duList[vet]){
                if(visited.count(dulists))//��ǰ�ڵ��ѱ���������������
                continue;
                que.push(dulists);
                visited.emplace(dulists);//���˽ڵ���Ӳ���¼���ڽӱ���
            }
        }
        return res;//���ؽ����
    }
    /*������ȱ���*/
    /*�����ڽӱ���ϣ����ֹ�ظ�����������ʼ�ڵ㡢�����*/
    /*���Ƚ���ʼ�ڵ�����������ٽ���ʼ�ڵ��¼
    ʹ��ѭ����������ǰ�ڵ��ÿ���ڽӽڵ�
    ����ǰ�ڵ��ѱ�����ʱ����
    �����ǰ�ڵ�û�б������ͽ���ǰ�ڵ�ݹ���ȱ���
    ��ʾΪ�ڵ�1-->2�����ڵ�2δ����������ʼ��2Ϊ���������-->3
    ��������*/
    void GraphDFS(DriectedWeightedGraph&graph,unordered_set<VertexPoint*>&visits,VertexPoint*start,vector<VertexPoint*>&res){
        res.push_back(start);
        visits.emplace(start);
        for(VertexPoint*vet:graph.duList[start]){
            if(visits.count(vet))
            continue;
            GraphDFS(graph,visits,vet,res);
        }
    }
public:
    //��vector��ɾ��ָ���ڵ�
    /*Ҫɾ��һ������ָ���Ľڵ�*/
    void removes(vector<VertexPoint*>&vec,VertexPoint*vet){
        for(int i=0;i<vec.size();i++){//����������
            if(vec[i]==vet){//�ڱ����ҵ�Ҫɾ���ڵ������
                vec.erase(vec.begin()+i);//ʹ������ɾ������ڵ�
                break;
            }
        }
    }
    /*��Ӷ���*/
    void addVertexs(VertexPoint*vet){
        if(duList.count(vet))return;//�˶����Ѵ���
        //���ڽӱ����¼���һ��������
        duList[vet]=vector<VertexPoint*>();
    }
    /*ɾ������*/
    void removeVertexs(VertexPoint*vet){
        if(!duList.count(vet))
            throw out_of_range("�����ڴ˶���");
        //���ڽӱ���ɾ������vet��Ӧ������
        duList.erase(vet);
        //�������������������ɾ���˶���
        for(auto&dul:duList){
            removes(dul.second,vet);
        }
    }
    /*��ӱ�*/
    void addEdges(VertexPoint*vet1,VertexPoint*vet2){
        if(!duList.count(vet1)||!duList.count(vet2)||vet1==vet2){
            throw out_of_range("�����ڴ˶����ߴ���");
        }
        duList[vet1].push_back(vet2);//����ͼ��ֻ����ǰ������ӱ�
    }
    /*ɾ����,ɾ��ָ��������ڽӶ���*/
    void removeEdges(VertexPoint*vet1,VertexPoint*vet2){
        if(!duList.count(vet1)||!duList.count(vet2)||vet1==vet2){
            throw out_of_range("�����ڴ˶����ߴ���");
        }
        removes(duList[vet1],vet2);//ɾ���˶����е��ڽӶ��㼴��
    }
public:
    /*���췽��*/
    DriectedWeightedGraph(const vector<vector<VertexPoint*>>&edges){
        //������ж���ͱ�
        for(const vector<VertexPoint*> edge:edges){
            addVertexs(edge[0]);//��Ӵ˶���
            addVertexs(edge[1]);//��Ӵ˶����Ӧ���ڽӶ���
            /*����ж��㱻�ظ������ֱ�ӷ���*/
            addEdges(edge[0],edge[1]);
        }
    }
    /*��ȡ��������*/
    int sizes(){return duList.size();};
    /*��ӡ�ڽӱ�*/
    void prints(){
        for(auto dul:duList){
            cout<<"�ڽӱ� = "<<endl;
            const auto&key=dul.first;
            const auto&vec=dul.second;
            cout<<"( "<<key->key<<" , ";
            cout<<key->val<<" ) :";
            printSforTwo(vetsTovalsl(vec));
            cout<<endl;
        }
    }
    /*������ȱ���*/
    vector<vector<int>>GraphBFSIn(DriectedWeightedGraph&graph,VertexPoint*start){
        return vetsTovalsl(GraphBFS(graph,start));
    }
    /*������ȱ���*/
    vector<vector<int>>GraphDFSIn(DriectedWeightedGraph&graph,VertexPoint*start){
        vector<VertexPoint*>res;
        unordered_set<VertexPoint*>visits;
        GraphDFS(graph,visits,start,res);
        return vetsTovalsl(res);
    }
};







#endif