 /*����������*/
#ifndef NETWORKFLOWPROBL_H
#define NETWORKFLOWPROBL_H
#include"../../utils/common.hpp"
#include"DriectedWeighitedGraph.h"
#include"DriectedWeightedGraphPath.h"
#include"VertexPiont.h"
void PrintVectorVertex(vector<VertexPoint*>ver);
void GraphDFS(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,unordered_set<VertexPoint*>&visits,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>&res);
class NetWorkFlowProbl{
private:
    unordered_map<VertexPoint*,vector<pair<VertexPoint*,pair<int,int>>>>NetFlow;
public:
/*�������������*/
    void NetWorkPro(DriectedWeightedGraph<int>&graph,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>vertex){
        //Ѱ������������������ͼ����ʼ�㣬�����㣬ͼ�����ж���
        NetWorkProblems(CopysList,start,end,vertex);
        //�������������ͼ
        vector<int>dist;//ʹ����������¼ԭͼ�е�Ȩֵ
        for(VertexPoint*&ver:vertex){//����ÿ�������������ͼ
            dist.clear();
            for(auto&Gra:graph.duList[ver]){//����ԭͼ
                dist.push_back(Gra.second);
            }
            int i=0;
            for(auto&copy:CopysList[ver]){//����������ͼ��ԭͼ-������ͼ��ֵ�����ͼ
                if(i==dist.size())continue;
                pair<VertexPoint*,pair<int,int>>temp;
                temp.first=copy.first;
                temp.second.first=dist[i];
                temp.second.second=dist[i]-copy.second;
                NetFlow[ver].push_back(temp);
                i++;
            }
        }
    }
private:
    /*����������*/
    void NetWorkProblems(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>vertex){
        //DriectedWeightedGraphPath<int>PathGraph(vertex);
        //PathGraph.IterationsDist(CopysList,start);
        vector<VertexPoint*>PathAs;
        unordered_set<VertexPoint*>set;
        GraphDFS(CopysList,set,start,end,PathAs);
        set.clear();
        if(PathAs.size()==1)return;
        PrintVectorVertex(PathAs);
        int MinPath=GetMinPath(CopysList,PathAs);
        if(MinPath==0)return;
        SetPath(CopysList,PathAs,MinPath);
        NetWorkProblems(CopysList,start,end,vertex);
        return;
    }
    /*���Ҵ�·���ϵ���СȨֵ*/
    int GetMinPath(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,vector<VertexPoint*>PathAs){
        int MinPathSize=INT_MAX;
        for(int i=0;i<PathAs.size()-1;i++){
            int Temp;
            for(auto&Grp:CopysList[PathAs[i]]){
                if(Grp.first!=PathAs[i+1])
                continue;
                Temp=Grp.second;
            }
            MinPathSize=min(MinPathSize,Temp);
        }
        return MinPathSize;
    }
    /*�޸Ĵ�·���ϵ�Ȩֵ����Ϊ������ͼ��·�����顢��ǰ·������С������,����Ford-Fulkerson�㷨����ӷ�����*/
    void SetPath(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,vector<VertexPoint*>PathAs,int MinPath){
        /*���������е�·���Ƿ���ģ����Դ����������һ��Ԫ�أ�Ҳ������ʼ�㣩��ʼ����*/
        for(int i=0;i<PathAs.size()-1;i++){
            for(auto&Grp:CopysList[PathAs[i]]){
                if(Grp.first!=PathAs[i+1])
                continue;
                Grp.second=Grp.second-MinPath;
                /*�ж��ڵ�ǰ���������Ƿ��е�ǰ���*/
                bool flag=0;
                int j=0;
                for(auto&fid:CopysList[Grp.first]){
                    if(fid.first==PathAs[i])
                    flag=1;
                    j++;
                }
                if(flag){//�о�ֱ�Ӹı�ֵ
                    CopysList[Grp.first][j-1].second+=MinPath;
                }else{
                    //����һ���µ�·������·��Ϊ������·��
                    pair<VertexPoint*,int>UnderFlow(PathAs[i],MinPath);
                    //������·����ӵ���ǰͼ��
                    CopysList[Grp.first].push_back(UnderFlow);
                }     
            }
        }  
    }
public:
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
public:
    /*�������������Dinic's�㷨*/
    void FLowAsDinic(DriectedWeightedGraph<int>&graph,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>vertex){
        unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>LevelGraph;
        DinicAlgorithmFLow(CopysList,LevelGraph,start,end,vertex);
        vector<int>dist;//ʹ����������¼ԭͼ�е�Ȩֵ
        for(VertexPoint*&ver:vertex){//����ÿ�������������ͼ
            dist.clear();
            for(auto&Gra:graph.duList[ver]){//����ԭͼ
                dist.push_back(Gra.second);
            }
            int i=0;
            for(auto&copy:CopysList[ver]){//����������ͼ��ԭͼ-������ͼ��ֵ�����ͼ
                if(i==dist.size())continue;
                pair<VertexPoint*,pair<int,int>>temp;
                temp.first=copy.first;
                temp.second.first=dist[i];
                temp.second.second=dist[i]-copy.second;
                NetFlow[ver].push_back(temp);
                i++;
            }
        }
    }
private:
    /*Dinic's�㷨Ѱ���������е������
    ��Ҫ����LevelGraph�����и���ʵ��
    ÿ�δ���LevelGraph�󶼶Դ�ͼ���м�·���µ����������㣬��������Ҳ�п������������
    �������������޸�CopysList����ӷ�����
    ��������LevelGraph�޷�����Ŀ���ʱ��ֹ����
    ��ʼ���Ͻ��*/
    void DinicAlgorithmFLow(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&LevelGraph,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>vertex){
        /*��֤ÿ�ε�LevGraph���ǿյ�*/
        ClearLevleGraph(LevelGraph);
        /*�ȴ���LevelGraph*/
        CreatLevelGraph(CopysList,LevelGraph,start,end);
        cout<<"����Levelͼ��"<<endl;
        PrintLevelGraph(LevelGraph,vertex);
        //����������ͼ
        unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>FLowGraph=LevelGraph;
        //��������ͼ
        bool flag=FindTheFLow(FLowGraph,start,end);
        //��ǰͼ��������ͼ�ͷ�����ֹ
        if(!flag)return; 
        //�о�����������ͼ
        SetLevelGraph(LevelGraph,FLowGraph,vertex);
        cout<<"�γɵ�������ͼ: "<<endl;
        PrintLevelGraph(LevelGraph,vertex);
        /*ʹ��LevelGraph�������µ�CopyListͼ*/
        SetCopysListGraph(CopysList,LevelGraph,vertex);
        cout<<"��ӡCopysListͼ"<<endl;
        cout<<endl;
        PrintLevelGraph(CopysList,vertex);
        /*�ݹ���ô˺���*/
        DinicAlgorithmFLow(CopysList,LevelGraph,start,end,vertex);
        return;
    }
    /*���LevelGraph�е�Ԫ�أ���ϣ����value������Ԫ�أ�*/
    void ClearLevleGraph(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&LevelGraph){
        for(auto&lev:LevelGraph){
            if(lev.second.size()==0)continue;
            lev.second.clear();
        }
    }
    /*����LevelGraph*/
    void CreatLevelGraph(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&LevelGraph,VertexPoint*start,VertexPoint*end){
        /*����CopysList������LevelGrap*/
        /*ʹ�ö�������������CopysList*/
        queue<VertexPoint*>que;
        que.push(start);
        /*ʹ�ù�ϣ������¼�Ѿ����������Ľ��*/
        unordered_map<VertexPoint*,int>flag;
        flag[start]=-1;
        //��¼����
        int i=1;
        while(!que.empty()){
            VertexPoint*vet=que.front();
            que.pop();
            for(auto&copy:CopysList[vet]){
                if(flag.count(copy.first)){//�����ǰ����������Ѿ�����¼��
                    if(flag[copy.first]<=flag[vet]||copy.second==0)continue;//��ѯ��¼��������뵱ǰ�����һ�㣬���أ�������������ǰ·��ֵΪ0ʱ����������·
                    LevelGraph[vet].push_back(copy);//�������ͬһ�㣬�޸�LevelGraph���ɣ����ظ��������
                }else {//�����δ����¼������¼�˽�㲢��Ӳ���
                    if(copy.second==0)continue;//��ǰ·��ֵΪ0ʱ����������·��
                    flag[copy.first]=i;
                    LevelGraph[vet].push_back(copy);
                    que.push(copy.first);
                }
            }
            i++;
        }
    }
    /*Ѱ��������*/
    bool FindTheFLow(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&FLowGraph,VertexPoint*start,VertexPoint*end){
        /*��LevelGraph��Ѱ��������*/
        unordered_set<VertexPoint*>set;
        vector<VertexPoint*>PathAs;
        GraphDFS(FLowGraph,set,start,end,PathAs);
        if(PathAs.size()==1)return false;
        set.clear();
        /*����LevelGraph��������*/
        /*�ҵ���СȨֵ*/
        int MinPath=GetMinPath(FLowGraph,PathAs);
        if(MinPath==0)return false;
        /*���ɻ���LevelGraph��������ͼ*/
        SetLevelPath(FLowGraph,PathAs,MinPath);
        FindTheFLow(FLowGraph,start,end);
        return true;
    }
    /*�޸���·��*/
    void SetLevelPath(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&FLowGraph,vector<VertexPoint*>PathAs,int MinPath){
        for(int i=0;i<PathAs.size()-1;i++){
            for(auto&lev:FLowGraph[PathAs[i]]){
                if(lev.first!=PathAs[i+1])continue;
                lev.second-=MinPath;
            }
        }
    }
    /*�޸�LevelGraphͼΪ����ͼ*/
    void SetLevelGraph(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&LevelGraph,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&FLowGraph,vector<VertexPoint*>vertex){
        for(VertexPoint*&vet:vertex){
            vector<int>dist;
            for(auto&flo:FLowGraph[vet]){
                if(flo.first==nullptr)continue;
                dist.push_back(flo.second);
            }
            int i=0;
            for(auto&lev:LevelGraph[vet]){
                if(lev.first==nullptr)continue;
                lev.second-=dist[i];
                i++;
            }
            dist.clear();
        }
    } 
    /*�޸�CopysListͼ*/
    void SetCopysListGraph(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&LevelGraph,vector<VertexPoint*>vertex){
        for(VertexPoint*&vet:vertex){//�������н�����޸�CopyListͼ
            int i=0;
            for(auto&copy:CopysList[vet]){//������ǰ����µ��ڽӵ�
                if(LevelGraph[vet].size()==0)continue;//��LevleGraph��û���ڽӵ�ʱ����
                auto&Lev=LevelGraph[vet];
                if(copy.first==nullptr||Lev[i].first==nullptr)continue;//�κ�һ���ڽӵ�Ϊ��ʱ����
                if(copy.first!=Lev[i].first)continue;//�����ڽӵ㲻���ʱ����(Ҳ������������LevelGraph����û�еģ�����CopysList���У�����������)
                copy.second-=Lev[i].second;
                //�����޸ķ���·��
                bool flag=0;
                int j=0;
                for(auto&Re:CopysList[copy.first]){//Ѱ�Ҵ�·���Ƿ��Ѿ�����
                    if(Re.first==vet)flag=1;
                    j++;
                }
                if(flag){//���ھ�ֱ����ԭֵ�ϼ��ϴ�ֵ
                    CopysList[copy.first][j-1].second+=Lev[i].second;
                }else{//�����´���һ����
                    pair<VertexPoint*,int>temp(vet,Lev[i].second);
                    CopysList[copy.first].push_back(temp);
                }
                i++;
            }
        }
    }
    /*��ӡͼ*/
    void PrintLevelGraph(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&LevelGraph,vector<VertexPoint*>vertex){
        for(VertexPoint*&ver:vertex){
            cout<<ver->key<<" = ";
            for(auto&lev:LevelGraph[ver]){
                if(lev.first==nullptr)continue;
                cout<<"("<<lev.first->key<<" , "<<lev.second<<")";
                cout<<"     ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
};
/*Ѱ��ͼ�еļ�·��,����ͼ����ʼ��ֹ��㡢���������ϣ����֤��·���в����л�·������Edmonds-Karp�㷨Ѱ�Ҽ�·��*/
void GraphDFS(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,unordered_set<VertexPoint*>&visits,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>&res){
        res.push_back(start);
        if(start==end)return;
        visits.emplace(start);
        for(auto vet:CopysList[start]){
            if(visits.count(vet.first)||vet.second==0)
            continue;
            GraphDFS(CopysList,visits,vet.first,end,res);
            if(res.back()==end)return;
            visits.erase(res.back());
            res.pop_back();
        }
    }
/*��ӡ�������*/
void PrintVectorVertex(vector<VertexPoint*>ver){
    for(VertexPoint*&ve:ver){
        cout<<ve->key<<" ";
    }
    cout<<endl;
}



#endif