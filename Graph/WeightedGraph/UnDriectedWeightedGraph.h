/*������Ȩͼ�ڽӱ�*/
#ifndef UNDRIECTEDWEIGHTEDGRAPH_H
#define UNDRIECTEDWEIGHTEDGRAPH_H
#include"..//..//utils//common.hpp"
#include"VertexPiont.h"

//���ȶ����ж�����
bool cmp(pair<VertexPoint*,int>&a,pair<VertexPoint*,int>&b){
    return a.second>b.second;
}

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
        pair<VertexPoint*,int>As(v1,vecs.second);
        adjList[vecs.first].push_back(As);
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
            for(auto&v:vec){
                cout<<v.first->key<<" "<<v.second<<" | ";
            }
            cout<<endl;
        }
        cout<<endl;
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
                if(visited.count(adjVet.first))//����Ѿ����������������˶���
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
    struct cmp1{
        bool operator()(pair<VertexPoint*,pair<VertexPoint*,int>>&a,pair<VertexPoint*,pair<VertexPoint*,int>>&b){
            return a.second.second>b.second.second;
        }
    };
    /*��С������*/
    /*��һ������������һ���ڵ�������n���ڵ�*/
    /*��ʼ��ʱ����ֻ��һ���ڵ㣬ÿ��ѭ���ҳ�һ���ڵ��һ���ߣ������������*/
    /*��֤��1.������ͨͼ
            2.û�л�·*/
    /*�㷨ѭ���������ڽڵ������*/

    /*ѡ���һ���ڵ㣬�Ӵν�㿪ʼ�����ڽӽڵ㣬�����˽ڵ�����ϣ����*/
    /*ȡ���ڵ�����С��һ���������Ӧ�Ľڵ�������У����ù�ϣ���¼*/
    vector<pair<VertexPoint*,VertexPoint*>>PrimMinimumTree(UnDriectedWeightedGraph&graph,VertexPoint*start){
        //��¼��
        vector<pair<VertexPoint*,VertexPoint*>>Edge;
        //���ȼ����У�������űߣ�ÿ��ѭ��ȡ�����ȼ���͵�һ����
        priority_queue<pair<VertexPoint*,pair<VertexPoint*,int>>,vector<pair<VertexPoint*,pair<VertexPoint*,int>>>,cmp1>que;
        //��֤ÿ���ڵ�ֻ�ܱ�����һ��
        unordered_set<VertexPoint*>set;
        //���������ڵ�
        queue<VertexPoint*>ques;
        //��ʼ�ڵ����
        ques.push(start);
        //��ʼ�ڵ㲻�ñ�����
        set.emplace(start);
        while(!ques.empty()){
            VertexPoint*ptr=ques.front();
            ques.pop();
            //��ȡ��
            pair<VertexPoint*,pair<VertexPoint*,int>>temp;
            //��ȡ�ߵ���ʼ��
            temp.first=ptr;
            for(auto&Gra:graph.adjList[ptr]){//������ǰ����������ڽӵ�
                if(set.count(Gra.first))//�����ǰ�ڽӵ��Ѿ�����������Ͳ����ٱ�����
                continue;
                temp.second.first=Gra.first;
                temp.second.second=Gra.second;
                que.push(temp);
            }
            //��������Ѿ��ǽڵ�����-1����ô֤�������ˣ��˳�����
            if(Edge.size()==graph.adjList.size()-1)
            break;
            temp=que.top();
            while(set.count(temp.second.first)){
                que.pop();
                temp=que.top();
            }
            que.pop();
            pair<VertexPoint*,VertexPoint*>tep(temp.first,temp.second.first);
            Edge.push_back(tep);
            ques.push(tep.second);
            set.emplace(tep.second);
        }
        return Edge;
    }
    /*Kruskal�㷨Ѱ����С������
    ����ͼ����ͼ�����б�ѹ�����ȶ���
    ȡ�����ȼ���͵������ߣ��ж���������Ƿ�����ͬһɭ��
    ����ͬһɭ�־�ֱ��ɾ�������ߣ����������ߵ��������ϲ�Ϊһ��ɭ����*/
    vector<pair<VertexPoint*,VertexPoint*>>KruskalMinimumTree(UnDriectedWeightedGraph&graph,vector<VertexPoint*>vertex){
        vector<pair<VertexPoint*,VertexPoint*>>res;//�����
        unordered_map<VertexPoint*,int>flag;//ʹ�ñ�ǣ���ʼʱÿ����ı�Ƕ���һ��
        int i=1;
        for(auto&ver:vertex){
            flag[ver]=i;
            i++;
        }
        //���ȶ��У��������еı�
        priority_queue<pair<VertexPoint*,pair<VertexPoint*,int>>,vector<pair<VertexPoint*,pair<VertexPoint*,int>>>,cmp1>que;
        unordered_set<VertexPoint*>set;
        for(i=0;i<vertex.size();i++){
            pair<VertexPoint*,pair<VertexPoint*,int>>temp;
            temp.first=vertex[i];
            for(auto&Grp:graph.adjList[vertex[i]]){
                if(set.count(Grp.first))
                continue;
                temp.second.first=Grp.first;
                temp.second.second=Grp.second;
                que.push(temp);
            }
            set.emplace(temp.first);
        }
        while(!que.empty()){
            pair<VertexPoint*,pair<VertexPoint*,int>>temp=que.top();
            que.pop();
            if(flag[temp.first]==flag[temp.second.first])
            continue;
            pair<VertexPoint*,VertexPoint*>Re(temp.first,temp.second.first);
            res.push_back(Re);
            int elem=flag[temp.second.first];
            for(auto&ver:vertex){
                if(flag[ver]==elem){
                    flag[ver]=flag[temp.first];
                }
            }
            if(res.size()==graph.adjList.size()-1)
            break;
        }
        return res;
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
    //Prim�㷨Ѱ����С������
    void PrimMinimumTreeIn(UnDriectedWeightedGraph&graph,VertexPoint*start){
        for(auto&res:PrimMinimumTree(graph,start)){
            cout<<"("<<res.first->key<<" , "<<res.second->key<<")"<<endl;
        }
        cout<<endl;
    }

    void KruskalMinimumTreeIn(UnDriectedWeightedGraph&graph,vector<VertexPoint*>vertex){
        for(auto&vet:KruskalMinimumTree(graph,vertex)){
            cout<<" "<<vet.first->key<<"   "<<vet.second->key<<endl;
        }
    }
};






#endif 