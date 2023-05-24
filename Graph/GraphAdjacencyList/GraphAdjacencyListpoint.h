#ifndef GRAPHADJACENCYLISTPOINT_H
#define GRAPHADJACENCYLISTPOINT_H
#include"..//..//utils//common.hpp"
template<typename T>
class GraphAdjacencyListpoint
{
private:
public:
    //邻接表，key：顶点，value：该顶点的所有邻接点
    unordered_map<Vertex*,vector<Vertex*>>adjList;
    /*在vector中删除指定结点*/
    void remove(vector<Vertex*>&vec,Vertex*vet){
        //鍦╲ec鏁扮粍涓?鍒犻櫎椤剁偣vet
        for(int i=0;i<vec.size();i++){//遍历邻接点数组
            if(vec[i]==vet){//找到对应邻接点，就删除
                vec.erase(vec.begin()+i);
                break;
            }
        }
    }
    /*构造方法*/
    GraphAdjacencyListpoint(const vector<vector<Vertex*>>&edges){
        for(const auto&edge:edges){
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0],edge[1]);
        }
    }
    /*添加边*/
    void addEdge(Vertex*v1,Vertex*v2){
        if(!adjList.count(v1)||!adjList.count(v2)||v1==v2)
            throw out_of_range("不存在此结点");
        //添加边vet1，vet2
        adjList[v1].push_back(v2);
    }
    //删除边
    void removeEdge(Vertex*v1,Vertex*v2){
        if(!adjList.count(v1)||!adjList.count(v2)||v2==v1)
            throw out_of_range("不存在此顶点");
        remove(adjList[v1],v2);
    }
    /*添加顶点*/
    void addVertex(Vertex*vet){
        if(adjList.count(vet))return;
        adjList[vet]=vector<Vertex*>();
    }
    /*删除顶点*/
    void removeVertex(Vertex*vet){
        if(!adjList.count(vet))
            throw out_of_range("不存在此顶点");
        adjList.erase(vet);
        for(auto&adj:adjList){
            remove(adj.second,vet);
        }
    }
    /*打印邻接表*/
    void print(){
        cout<<"邻接表 = "<<endl;
        for(auto&adj:adjList){
            const auto&key=adj.first;
            const auto&vec=adj.second;
            cout<<key->val<<": ";
            printVector(vetsToVals(vec));
        }
    }
    /*无向图的广度优先遍历*//*传入邻接链表对象和顶点起始点*/
    vector<Vertex*>graphBFS(GraphAdjacencyListpoint&graph,Vertex*strat){
         /*使用队列来进行广度优先遍历，使用哈希set来防止重复遍历*/
        vector<Vertex*>res;
        queue<Vertex*>que;
        que.push(strat);
        unordered_set<Vertex*>visited={strat};//进队，记录此顶点
        while(!que.empty()){
            Vertex*vet=que.front();
            que.pop();//队首顶点出队
            res.push_back(vet);//记录访问结点
            for(auto adjVet:graph.adjList[vet]){//遍历adjList[vet]顶点的每个数组元素
                if(visited.count(adjVet))//如果已经遍历过，就跳过此顶点
                continue;
                que.push(adjVet);//将此顶点入队
                visited.emplace(adjVet);//记录此顶点
            }
        }
        //返回顶点序列
        return res;
    }
    /*无向图的深度优先遍历,递归*/
    void dfs(GraphAdjacencyListpoint&graph,unordered_set<Vertex*>&visited,vector<Vertex*>&res,Vertex*vet){
        res.push_back(vet);//记录访问顶点
        visited.emplace(vet);//标记已访问
        //遍历该顶点的所有邻接顶点
        for(auto adjMat:graph.adjList[vet]){
            if(visited.count(adjMat))
            continue;//跳过已被访问的顶点
            dfs(graph,visited,res,adjMat);
        }
    }
    /*辅助函数，传入参数*/
    vector<Vertex*>graphDFS(GraphAdjacencyListpoint&graph,Vertex*start){
        vector<Vertex*>res;
        unordered_set<Vertex*>visited;
        dfs(graph,visited,res,start);
        return res;
    }
};






#endif 