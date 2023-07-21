/*无向有权图邻接表*/
#ifndef UNDRIECTEDWEIGHTEDGRAPH_H
#define UNDRIECTEDWEIGHTEDGRAPH_H
#include"..//..//utils//common.hpp"
#include"VertexPiont.h"

//优先队列判断条件
bool cmp(pair<VertexPoint*,int>&a,pair<VertexPoint*,int>&b){
    return a.second>b.second;
}

template<typename T>
class UnDriectedWeightedGraph
{
private:
public:
    //邻接表，key：顶点，value：该顶点的所有邻接点
    unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>adjList;
    /*在vector中删除指定结点*/
    void remove(vector<VertexPoint*>&vec,VertexPoint*vet){
        for(int i=0;i<vec.size();i++){//遍历邻接点数组
            if(vec[i]==vet){//找到对应邻接点，就删除
                vec.erase(vec.begin()+i);
                break;
            }
        }
    }
    /*构造方法*/
    UnDriectedWeightedGraph(const vector<pair<pair<VertexPoint*,VertexPoint*>,int>>&edges){
        for(const auto&edge:edges){
            addVertex(edge.first.first);
            addVertex(edge.first.second);
            pair<VertexPoint*,int>vecs(edge.first.second,edge.second);
            addEdge(edge.first.first,vecs);
        }
    }
    /*添加边*/
    void addEdge(VertexPoint*v1,pair<VertexPoint*,int>vecs){
        if(!adjList.count(v1)||!adjList.count(vecs.first)||v1==vecs.first)
            throw out_of_range("不存在此结点");
        //添加边vet1，vet2
        adjList[v1].push_back(vecs);
        pair<VertexPoint*,int>As(v1,vecs.second);
        adjList[vecs.first].push_back(As);
    }
    //删除边
    void removeEdge(VertexPoint*v1,VertexPoint*v2){
        if(!adjList.count(v1)||!adjList.count(v2)||v2==v1)
            throw out_of_range("不存在此顶点");
        remove(adjList[v1],v2);
        remove(adjList[v2],v1);
    }
    /*添加顶点*/
    void addVertex(VertexPoint*vet){
        if(adjList.count(vet))return;
        adjList[vet]=vector<pair<VertexPoint*,int>>();
    }
    /*删除顶点*/
    void removeVertex(VertexPoint*vet){
        if(!adjList.count(vet))
            throw out_of_range("不存在此顶点");
        adjList.erase(vet);
        for(auto&adj:adjList){
            remove(adj.first,vet);
        }
    }
    /*打印邻接表*/
    void print(){
        cout<<"邻接表 = "<<endl;
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
    /*无向图的广度优先遍历*//*传入邻接链表对象和顶点起始点*/
    vector<VertexPoint*>UnDriectedWeightedGraphBFS(UnDriectedWeightedGraph&graph,VertexPoint*strat){
         /*使用队列来进行广度优先遍历，使用哈希set来防止重复遍历*/
        vector<VertexPoint*>res;
        queue<VertexPoint*>que;
        que.push(strat);
        unordered_set<VertexPoint*>visited={strat};//进队，记录此顶点
        while(!que.empty()){
            VertexPoint*vet=que.front();
            que.pop();//队首顶点出队
            res.push_back(vet);//记录访问结点
            for(auto adjVet:graph.adjList[vet]){//遍历adjList[vet]顶点的每个数组元素
                if(visited.count(adjVet.first))//如果已经遍历过，就跳过此顶点
                continue;
                que.push(adjVet.first);//将此顶点入队
                visited.emplace(adjVet.first);//记录此顶点
            }
        }
        //返回顶点序列
        return res;
    }
    /*无向图的深度优先遍历,递归*/
    void UnDriectedWeightedGraphDFS(UnDriectedWeightedGraph&graph,unordered_set<VertexPoint*>&visited,vector<VertexPoint*>&res,VertexPoint*vet){
        res.push_back(vet);//记录访问顶点
        visited.emplace(vet);//标记已访问
        //遍历该顶点的所有邻接顶点
        for(auto adjMat:graph.adjList[vet]){
            if(visited.count(adjMat.first))
            continue;//跳过已被访问的顶点
            UnDriectedWeightedGraphDFS(graph,visited,res,adjMat.first);
        }
    }
    struct cmp1{
        bool operator()(pair<VertexPoint*,pair<VertexPoint*,int>>&a,pair<VertexPoint*,pair<VertexPoint*,int>>&b){
            return a.second.second>b.second.second;
        }
    };
    /*最小生成树*/
    /*种一棵树，让树从一个节点增长到n个节点*/
    /*初始的时候数只有一个节点，每轮循环找出一个节点和一条边，将其接在树上*/
    /*保证：1.树是联通图
            2.没有回路*/
    /*算法循环次数等于节点的数量*/

    /*选入第一个节点，从次结点开始遍历邻接节点，并将此节点放入哈希表中*/
    /*取出节点中最小的一条边与其对应的节点加入树中，并用哈希表记录*/
    vector<pair<VertexPoint*,VertexPoint*>>PrimMinimumTree(UnDriectedWeightedGraph&graph,VertexPoint*start){
        //记录边
        vector<pair<VertexPoint*,VertexPoint*>>Edge;
        //优先级队列，用来存放边，每轮循环取出优先级最低的一条边
        priority_queue<pair<VertexPoint*,pair<VertexPoint*,int>>,vector<pair<VertexPoint*,pair<VertexPoint*,int>>>,cmp1>que;
        //保证每个节点只能被到达一次
        unordered_set<VertexPoint*>set;
        //用来遍历节点
        queue<VertexPoint*>ques;
        //初始节点入队
        ques.push(start);
        //初始节点不用被到达
        set.emplace(start);
        while(!ques.empty()){
            VertexPoint*ptr=ques.front();
            ques.pop();
            //获取边
            pair<VertexPoint*,pair<VertexPoint*,int>>temp;
            //获取边的起始点
            temp.first=ptr;
            for(auto&Gra:graph.adjList[ptr]){//遍历当前顶点的所有邻接点
                if(set.count(Gra.first))//如果当前邻接点已经被到达过，就不用再遍历了
                continue;
                temp.second.first=Gra.first;
                temp.second.second=Gra.second;
                que.push(temp);
            }
            //如果边数已经是节点总数-1，那么证明找完了，退出即可
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
    /*Kruskal算法寻找最小生成树
    传入图，将图的所有边压入优先队列
    取出优先级最低的那条边，判断两个结点是否属于同一森林
    若在同一森林就直接删除这条边，否则将这条边的两个结点合并为一个森林中*/
    vector<pair<VertexPoint*,VertexPoint*>>KruskalMinimumTree(UnDriectedWeightedGraph&graph,vector<VertexPoint*>vertex){
        vector<pair<VertexPoint*,VertexPoint*>>res;//结果集
        unordered_map<VertexPoint*,int>flag;//使用标记，初始时每个点的标记都不一样
        int i=1;
        for(auto&ver:vertex){
            flag[ver]=i;
            i++;
        }
        //优先队列，存入所有的边
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
    /*无向有权图的广度优先遍历*/
    vector<vector<int>>UnDriectedWeightedGraphBFSIn(UnDriectedWeightedGraph&graph,VertexPoint*start){
        return vetsTovalsl(UnDriectedWeightedGraphBFS(graph,start));
    }
    /*无向有权图的深度优先遍历*/
    vector<vector<int>>UnDriectedWeightedGraphDFSIn(UnDriectedWeightedGraph&graph,VertexPoint*start){
        vector<VertexPoint*>res;
        unordered_set<VertexPoint*>visited;
        UnDriectedWeightedGraphDFS(graph,visited,res,start);
        return vetsTovalsl(res);
    }
    //Prim算法寻找最小生成树
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