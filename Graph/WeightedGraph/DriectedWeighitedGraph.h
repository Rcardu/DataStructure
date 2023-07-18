/*有向有权图*/
#ifndef DIRECTEDWEIGHTITEDGRAPH_H
#define DIRECTEDWEIGHTITEDGRAPH_H
#include"../../utils/common.hpp"
#include"VertexPiont.h"
template<typename T>
class DriectedWeightedGraph{
public:
    //创建一个有向邻接表，使用map来存放顶点以及邻接顶点集合与其对应的权
    unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>duList;
        /*有向图的广度优先遍历*/
    /*传入有向图的邻接表和起始顶点*/
    /*使用队列来进行广度优先遍历
    例如:1 --> 2,4,5
        2 --> 3,4
        3 --> 4,5
        4 --> 5
        首先将1入队并用哈希表记录此顶点，然后再将起始顶点放入遍历数组中的并出队
        使用循环来遍历顶点一的邻接顶点，并依次入队同时判断当前顶点是否已经完成遍历
        入堆后使用哈希表记录此顶点
        遍历结果
        1 2 4 5 3 
         */
    vector<VertexPoint*>GraphBFS(DriectedWeightedGraph&graph,VertexPoint*start){
        queue<VertexPoint*>que;//遍历顺序
        vector<VertexPoint*>res;//遍历结果
        que.push(start);//将起始顶点入队
        unordered_set<VertexPoint*>visited={start};//记录当前入队的节点
        while(!que.empty()){
            VertexPoint*vet=que.front();//选取队列中的第一个节点
            que.pop();//出队
            res.push_back(vet);//记录结果
            for(auto dulists:graph.duList[vet]){
                if(visited.count(dulists.first))//当前节点已被遍历过，就跳过
                continue;
                que.push(dulists.first);
                visited.emplace(dulists.first);//将此节点入队并记录到邻接表中
            }
        }
        return res;//返回结果集
    }
    /*深度优先遍历*/
    /*传入邻接表、哈希表（防止重复遍历）、起始节点、结果集*/
    /*首先将起始节点放入结果集，再将起始节点记录
    使用循环来遍历当前节点的每个邻接节点
    当当前节点已被遍历时跳过
    如果当前节点没有被遍历就将当前节点递归深度遍历
    表示为节点1-->2（当节点2未被遍历，开始以2为顶点遍历）-->3
    依次类推*/
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
    //在vector中删除指定节点
    /*要删除一个表中指定的节点*/
    void removes(vector<pair<VertexPoint*,int>>&vec,VertexPoint*vet){
        for(int i=0;i<vec.size();i++){//遍历整个表
            if(vec[i].first==vet){//在表中找到要删除节点的索引
                vec.erase(vec.begin()+i);//使用索引删除这个节点
                break;
            }
        }
    }
    /*添加顶点*/
    void addVertexs(VertexPoint*vet){
        if(duList.count(vet))return;//此顶点已存在
        //在邻接表中新加入一个新链表
        duList[vet]=vector<pair<VertexPoint*,int>>();
    }
    /*删除顶点*/
    void removeVertexs(VertexPoint*vet){
        if(!duList.count(vet))
            throw out_of_range("不存在此顶点");
        //在邻接表中删除顶点vet对应的链表
        duList.erase(vet);
        //遍历其他顶点的链表，并删除此顶点
        for(auto&dul:duList){
            removes(dul.first,vet);
        }
    }
    /*添加边*/
    void addEdges(VertexPoint*vet1,pair<VertexPoint*,int>vecs){
        if(!duList.count(vet1)||!duList.count(vecs.first)||vet1==vecs.first){
            throw out_of_range("不存在此顶点或边错误");
        }
        duList[vet1].push_back(vecs);//有向图，只给当前顶点添加边与权
    }
    /*删除边,删除指定顶点的邻接顶点*/
    void removeEdges(VertexPoint*vet1,VertexPoint*vet2){
        if(!duList.count(vet1)||!duList.count(vet2)||vet1==vet2){
            throw out_of_range("不存在此顶点或边错误");
        }
        removes(duList[vet1],vet2);//删除此顶点中的邻接顶点即可
    }
public:
    /*构造方法*/
    DriectedWeightedGraph(const vector<pair<pair<VertexPoint*,VertexPoint*>,int>>&edges){
        //添加所有顶点和边
        for(const auto&edge:edges){
            addVertexs(edge.first.first);//添加此顶点
            addVertexs(edge.first.second);//添加此顶点对应的邻接顶点
            /*如果有顶点被重复加入回直接返回*/
            pair<VertexPoint*,int>vecs(edge.first.second,edge.second);
            addEdges(edge.first.first,vecs);
        }
    }
    /*获取顶点数量*/
    int sizes(){return duList.size();};
    /*打印邻接表*/
    void prints(){
        for(auto dul:duList){
            const auto&key1=dul.first;
            const auto&val=dul.second;
            cout<<"邻接表 = ";
            cout<<key1->key<<"->";
            for(auto v:val){
                const auto&key2=v.first;
                const auto&vals=v.second;
                cout<<"("<<key2->key<<" , "<<vals<<")   ";
            }
            cout<<endl;
        }
    }
    /*广度优先遍历*/
    vector<vector<int>>GraphBFSIn(DriectedWeightedGraph&graph,VertexPoint*start){
        return vetsTovalsl(GraphBFS(graph,start));
    }
    /*深度优先遍历*/
    vector<vector<int>>GraphDFSIn(DriectedWeightedGraph&graph,VertexPoint*start){
        vector<VertexPoint*>res;
        unordered_set<VertexPoint*>visits;
        GraphDFS(graph,visits,start,res);
        return vetsTovalsl(res);
    }
};







#endif