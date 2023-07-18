/*������Ȩͼ*/
#ifndef DIRECTEDWEIGHTITEDGRAPH_H
#define DIRECTEDWEIGHTITEDGRAPH_H
#include"../../utils/common.hpp"
#include"VertexPiont.h"
template<typename T>
class DriectedWeightedGraph{
public:
    //����һ�������ڽӱ�ʹ��map����Ŷ����Լ��ڽӶ��㼯�������Ӧ��Ȩ
    unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>duList;
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
                if(visited.count(dulists.first))//��ǰ�ڵ��ѱ���������������
                continue;
                que.push(dulists.first);
                visited.emplace(dulists.first);//���˽ڵ���Ӳ���¼���ڽӱ���
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
        for(auto vet:graph.duList[start]){
            if(visits.count(vet.first))
            continue;
            GraphDFS(graph,visits,vet.first,res);
        }
    }
public:
    //��vector��ɾ��ָ���ڵ�
    /*Ҫɾ��һ������ָ���Ľڵ�*/
    void removes(vector<pair<VertexPoint*,int>>&vec,VertexPoint*vet){
        for(int i=0;i<vec.size();i++){//����������
            if(vec[i].first==vet){//�ڱ����ҵ�Ҫɾ���ڵ������
                vec.erase(vec.begin()+i);//ʹ������ɾ������ڵ�
                break;
            }
        }
    }
    /*��Ӷ���*/
    void addVertexs(VertexPoint*vet){
        if(duList.count(vet))return;//�˶����Ѵ���
        //���ڽӱ����¼���һ��������
        duList[vet]=vector<pair<VertexPoint*,int>>();
    }
    /*ɾ������*/
    void removeVertexs(VertexPoint*vet){
        if(!duList.count(vet))
            throw out_of_range("�����ڴ˶���");
        //���ڽӱ���ɾ������vet��Ӧ������
        duList.erase(vet);
        //�������������������ɾ���˶���
        for(auto&dul:duList){
            removes(dul.first,vet);
        }
    }
    /*��ӱ�*/
    void addEdges(VertexPoint*vet1,pair<VertexPoint*,int>vecs){
        if(!duList.count(vet1)||!duList.count(vecs.first)||vet1==vecs.first){
            throw out_of_range("�����ڴ˶����ߴ���");
        }
        duList[vet1].push_back(vecs);//����ͼ��ֻ����ǰ������ӱ���Ȩ
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
    DriectedWeightedGraph(const vector<pair<pair<VertexPoint*,VertexPoint*>,int>>&edges){
        //������ж���ͱ�
        for(const auto&edge:edges){
            addVertexs(edge.first.first);//��Ӵ˶���
            addVertexs(edge.first.second);//��Ӵ˶����Ӧ���ڽӶ���
            /*����ж��㱻�ظ������ֱ�ӷ���*/
            pair<VertexPoint*,int>vecs(edge.first.second,edge.second);
            addEdges(edge.first.first,vecs);
        }
    }
    /*��ȡ��������*/
    int sizes(){return duList.size();};
    /*��ӡ�ڽӱ�*/
    void prints(){
        for(auto dul:duList){
            const auto&key1=dul.first;
            const auto&val=dul.second;
            cout<<"�ڽӱ� = ";
            cout<<key1->key<<"->";
            for(auto v:val){
                const auto&key2=v.first;
                const auto&vals=v.second;
                cout<<"("<<key2->key<<" , "<<vals<<")   ";
            }
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