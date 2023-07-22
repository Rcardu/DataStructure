 /*网络流问题*/
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
/*网络流结果梳理*/
    void NetWorkPro(DriectedWeightedGraph<int>&graph,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>vertex){
        //寻找网络流输入网络流图，起始点，结束点，图的所有顶点
        NetWorkProblems(CopysList,start,end,vertex);
        //创建网络流结果图
        vector<int>dist;//使用数组来记录原图中的权值
        for(VertexPoint*&ver:vertex){//遍历每个结点来创建此图
            dist.clear();
            for(auto&Gra:graph.duList[ver]){//遍历原图
                dist.push_back(Gra.second);
            }
            int i=0;
            for(auto&copy:CopysList[ver]){//遍历网络流图将原图-网络流图的值给结果图
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
    /*网络流问题*/
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
    /*查找此路径上的最小权值*/
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
    /*修改此路径上的权值输入为网络流图、路径数组、当前路径的最小网络流,基于Ford-Fulkerson算法来添加反向流*/
    void SetPath(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,vector<VertexPoint*>PathAs,int MinPath){
        /*由于数组中的路径是反向的，所以从数组中最后一个元素（也就是起始点）开始遍历*/
        for(int i=0;i<PathAs.size()-1;i++){
            for(auto&Grp:CopysList[PathAs[i]]){
                if(Grp.first!=PathAs[i+1])
                continue;
                Grp.second=Grp.second-MinPath;
                /*判断在当前反向结点中是否有当前结点*/
                bool flag=0;
                int j=0;
                for(auto&fid:CopysList[Grp.first]){
                    if(fid.first==PathAs[i])
                    flag=1;
                    j++;
                }
                if(flag){//有就直接改变值
                    CopysList[Grp.first][j-1].second+=MinPath;
                }else{
                    //创建一个新的路径，此路径为反向流路径
                    pair<VertexPoint*,int>UnderFlow(PathAs[i],MinPath);
                    //将反向路径添加到当前图中
                    CopysList[Grp.first].push_back(UnderFlow);
                }     
            }
        }  
    }
public:
    /*当前网络流量值*/
    void NetWorkValue(VertexPoint*start){
        int value=0;
        for(auto&Net:NetFlow[start]){
            value+=Net.second.second;
        }
        cout<<"当前网络流的一个解为："<<value;
    }
    /*打印网络流情况*/
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
    /*网络流输入就与Dinic's算法*/
    void FLowAsDinic(DriectedWeightedGraph<int>&graph,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>vertex){
        unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>LevelGraph;
        DinicAlgorithmFLow(CopysList,LevelGraph,start,end,vertex);
        vector<int>dist;//使用数组来记录原图中的权值
        for(VertexPoint*&ver:vertex){//遍历每个结点来创建此图
            dist.clear();
            for(auto&Gra:graph.duList[ver]){//遍历原图
                dist.push_back(Gra.second);
            }
            int i=0;
            for(auto&copy:CopysList[ver]){//遍历网络流图将原图-网络流图的值给结果图
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
    /*Dinic's算法寻找网络流中的最大流
    需要创建LevelGraph来进行辅助实现
    每次创建LevelGraph后都对此图进行简单路径下的阻塞流计算，（阻塞流也有可能是最大流）
    阻塞流创建后修改CopysList并添加反向流
    当创建的LevelGraph无法到达目标点时终止程序
    开始整合结果*/
    void DinicAlgorithmFLow(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&LevelGraph,VertexPoint*start,VertexPoint*end,vector<VertexPoint*>vertex){
        /*保证每次的LevGraph都是空的*/
        ClearLevleGraph(LevelGraph);
        /*先创建LevelGraph*/
        CreatLevelGraph(CopysList,LevelGraph,start,end);
        cout<<"创建Level图："<<endl;
        PrintLevelGraph(LevelGraph,vertex);
        //创建阻塞流图
        unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>FLowGraph=LevelGraph;
        //查找阻塞图
        bool flag=FindTheFLow(FLowGraph,start,end);
        //当前图无阻塞流图就返回终止
        if(!flag)return; 
        //有就生成阻塞流图
        SetLevelGraph(LevelGraph,FLowGraph,vertex);
        cout<<"形成的阻塞流图: "<<endl;
        PrintLevelGraph(LevelGraph,vertex);
        /*使用LevelGraph来生成新的CopyList图*/
        SetCopysListGraph(CopysList,LevelGraph,vertex);
        cout<<"打印CopysList图"<<endl;
        cout<<endl;
        PrintLevelGraph(CopysList,vertex);
        /*递归调用此函数*/
        DinicAlgorithmFLow(CopysList,LevelGraph,start,end,vertex);
        return;
    }
    /*清除LevelGraph中的元素（哈希表中value的数组元素）*/
    void ClearLevleGraph(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&LevelGraph){
        for(auto&lev:LevelGraph){
            if(lev.second.size()==0)continue;
            lev.second.clear();
        }
    }
    /*创建LevelGraph*/
    void CreatLevelGraph(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&LevelGraph,VertexPoint*start,VertexPoint*end){
        /*遍历CopysList来创建LevelGrap*/
        /*使用队列来遍历整个CopysList*/
        queue<VertexPoint*>que;
        que.push(start);
        /*使用哈希表来记录已经被遍历过的结点*/
        unordered_map<VertexPoint*,int>flag;
        flag[start]=-1;
        //记录层数
        int i=1;
        while(!que.empty()){
            VertexPoint*vet=que.front();
            que.pop();
            for(auto&copy:CopysList[vet]){
                if(flag.count(copy.first)){//如果当前被遍历结点已经被记录过
                    if(flag[copy.first]<=flag[vet]||copy.second==0)continue;//查询记录情况，若与当前结点在一层，跳回（不做操作）当前路径值为0时不加入这条路
                    LevelGraph[vet].push_back(copy);//如果不是同一层，修改LevelGraph即可，不重复加入队列
                }else {//如果从未被记录过，记录此结点并添加层数
                    if(copy.second==0)continue;//当前路径值为0时不加入这条路径
                    flag[copy.first]=i;
                    LevelGraph[vet].push_back(copy);
                    que.push(copy.first);
                }
            }
            i++;
        }
    }
    /*寻找阻塞流*/
    bool FindTheFLow(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&FLowGraph,VertexPoint*start,VertexPoint*end){
        /*在LevelGraph中寻找阻塞流*/
        unordered_set<VertexPoint*>set;
        vector<VertexPoint*>PathAs;
        GraphDFS(FLowGraph,set,start,end,PathAs);
        if(PathAs.size()==1)return false;
        set.clear();
        /*生成LevelGraph的阻塞流*/
        /*找到最小权值*/
        int MinPath=GetMinPath(FLowGraph,PathAs);
        if(MinPath==0)return false;
        /*生成基于LevelGraph的阻塞流图*/
        SetLevelPath(FLowGraph,PathAs,MinPath);
        FindTheFLow(FLowGraph,start,end);
        return true;
    }
    /*修改流路径*/
    void SetLevelPath(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&FLowGraph,vector<VertexPoint*>PathAs,int MinPath){
        for(int i=0;i<PathAs.size()-1;i++){
            for(auto&lev:FLowGraph[PathAs[i]]){
                if(lev.first!=PathAs[i+1])continue;
                lev.second-=MinPath;
            }
        }
    }
    /*修改LevelGraph图为最终图*/
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
    /*修改CopysList图*/
    void SetCopysListGraph(unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&CopysList,unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>&LevelGraph,vector<VertexPoint*>vertex){
        for(VertexPoint*&vet:vertex){//遍历所有结点来修改CopyList图
            int i=0;
            for(auto&copy:CopysList[vet]){//遍历当前结点下的邻接点
                if(LevelGraph[vet].size()==0)continue;//当LevleGraph中没有邻接点时跳过
                auto&Lev=LevelGraph[vet];
                if(copy.first==nullptr||Lev[i].first==nullptr)continue;//任何一个邻接点为空时跳过
                if(copy.first!=Lev[i].first)continue;//两个邻接点不相等时跳过(也就是这条边在LevelGraph中是没有的，但在CopysList中有，跳过这条边)
                copy.second-=Lev[i].second;
                //用来修改反向路径
                bool flag=0;
                int j=0;
                for(auto&Re:CopysList[copy.first]){//寻找此路径是否已经存在
                    if(Re.first==vet)flag=1;
                    j++;
                }
                if(flag){//存在就直接在原值上加上此值
                    CopysList[copy.first][j-1].second+=Lev[i].second;
                }else{//否则新创建一条边
                    pair<VertexPoint*,int>temp(vet,Lev[i].second);
                    CopysList[copy.first].push_back(temp);
                }
                i++;
            }
        }
    }
    /*打印图*/
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
/*寻找图中的简单路径,传入图、起始终止结点、结果集、哈希表（保证简单路径中不能有回路）基于Edmonds-Karp算法寻找简单路径*/
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
/*打印结点数组*/
void PrintVectorVertex(vector<VertexPoint*>ver){
    for(VertexPoint*&ve:ver){
        cout<<ve->key<<" ";
    }
    cout<<endl;
}



#endif