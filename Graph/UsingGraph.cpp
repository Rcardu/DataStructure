#ifndef USINGGRAPH_H
#define USINGGRAPH_H
#include "../utils/common.hpp"
#include "UnWeightedGraph/UnDriectedUnWeightedGraph.h"
#include "UnWeightedGraph/UnDriectedUnWeightedGraphShortPath.h"
#include "UnWeightedGraph/UnDriectedUnWeightedGraphMatrix.h"
#include "UnWeightedGraph/DriectedUnWeightedGraph.h"
#include "UnWeightedGraph/DricetedUnWeightedGraphMatrix.h"

#include "WeightedGraph/UnDriectedWeightedGraph.h"
#include "WeightedGraph/DirectedWeightedGraphMatrix.h"
#include "WeightedGraph/DriectedWeighitedGraph.h"
#include "WeightedGraph/DriectedWeightedGraphPath.h"
#include "WeightedGraph/NetWorkFlowProbl.h"
using namespace std;
void UnDriectedUnWeightGraphForamt();//无向无权图邻接表
void UnDriectedUnWeightedGraphMatrixFormat();//无向无权图的邻接矩阵
void DriectedUnWeightedGraphFormat();//有向无权图
void DricetedUnWeightedGraphMatrixformat();//有向无权图的邻接矩阵

void UnDriectedWeightedGraphFormat();//无向有权图的邻接表
void DriectedweightedGraphFormat();//有向有权图的邻接表
void DriectedWeightedGraphMatForamt();//有向有权图的邻接矩阵

//无向无权图的操作
void UnDriectedUnWeightGraphForamt(){
    vector<Vertex*>v=valsToVets(vector<int>{1,2,3,4,5,6,7});//将int类型转换成vector<Vertex*>类型
    vector<vector<Vertex*>>edges={{v[0],v[1]},{v[0],v[2]},{v[0],v[3]},
                                    {v[1],v[3]},{v[1],v[4]},
                                    {v[2],v[3]},{v[2],v[5]},
                                    {v[3],v[4]},
                                    {v[4],v[6]},{v[5],v[6]}};
    UnDriectedUnWeightedGraph<int>graph(edges);
    cout<<"\n后的临界链表"<<endl;
    graph.print();

    UnDriectedUnWeightedGraphShortPath<int>gradh(v);
    vector<int>vec=gradh.ShortestPath(graph,v[2],v[4]);
    gradh.print();
    cout<<endl;
    for(int v:vec){
        cout<<v<<" ";
    }
    graph.addEdge(v[0],v[2]);
    cout<<"\n添加边1-2后，图为:";
    graph.print();

    vector<Vertex*>vet=graph.graphBFS(graph,v[0]);
    cout<<"遍历后的顺序为:"<<endl;
    printVector(vetsToVals(vet));

    vector<Vertex*>ves=graph.graphDFS(graph,v[0]);
    cout<<"深度优先遍历后为:"<<endl;
    printVector(vetsToVals(ves));

    graph.removeEdge(v[0],v[1]);
    cout<<"\n删除边1-3后，图为:";
    graph.print();

    Vertex*v5=new Vertex(6);
    graph.addVertex(v5);
    cout<<"\n添加顶点6后图为:";
    graph.print();

    graph.removeVertex(v[1]);
    cout<<"\n删除顶点3后图为:";
    graph.print();        
    for(auto vet:v){
        delete vet;
    }                       
}
//无向无权图的邻接矩阵
void UnDriectedUnWeightedGraphMatrixFormat(){
    vector<int>vertiecs={1,2,3,4,5};
    vector<vector<int>>adjMat={{0,1},{0,3},{1,2},{2,3},{2,4},{3,4}};
    UnDriectedUnWeightedGraphMatrix<int>obj(vertiecs,adjMat);
    obj.addEdge(0,2);
    obj.print();
    cout<<endl;
    obj.removeEdge(0,4);
    obj.print();
    cout<<endl;
    obj.addVertex(3);
    obj.print();
    cout<<endl;
    obj.removeVertex(2);   
    cout<<endl;   
}
//有向无权图的操作
void DriectedUnWeightedGraphFormat(){
    vector<Vertex*>v=valsToVets(vector<int>{1,2,3,4,5,6,7});//将int类型转换成vector<Vertex*>类型
    vector<vector<Vertex*>>edges={{v[0],v[1]},{v[0],v[2]},{v[0],v[3]},
                                    {v[1],v[3]},{v[1],v[4]},
                                    {v[2],v[3]},{v[2],v[5]},
                                    {v[3],v[4]},
                                    {v[4],v[6]},{v[5],v[6]}};
    DriectedUnWeightedGraph<int>graph(edges);
    graph.print();
    printVector(graph.DriectedUnWeightedGraphBFSIn(graph,v[0]));
    printVector(graph.DriectedUnWeightedGraphDFSIn(graph,v[0]));
}
void DricetedUnWeightedGraphMatrixformat(){
    vector<int>vertiecs={1,2,3,4,5};
    vector<vector<int>>adjMat={{0,1},{0,3},{1,2},{2,3},{2,4},{3,4}};
    DriectedUnWeightedGraphMatrix<int>obj(vertiecs,adjMat);
    obj.addEdge(0,2);
    obj.print();
    cout<<endl;
    obj.removeEdge(0,4);
    obj.print();
    cout<<endl;
    obj.addVertex(3);
    obj.print();
    cout<<endl;
    obj.removeVertex(2);   
    cout<<endl;  
}
//无向有权图
void UnDriectedWeightedGraphFormat(){
    vector<VertexPoint*>v=valsToVetsl(vector<vector<int>>{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}});
    vector<pair<pair<VertexPoint*,VertexPoint*>,int>>edgesl={{{v[0],v[1]},2},{{v[0],v[2]},4},{{v[0],v[3]},1},
                                                    {{v[1],v[3]},3},{{v[1],v[4]},10},
                                                    {{v[2],v[3]},2},{{v[2],v[5]},5},
                                                    {{v[3],v[5]},8},{{v[3],v[6]},4},{{v[3],v[4]},7},
                                                    {{v[4],v[6]},6},{{v[5],v[6]},1}};
    UnDriectedWeightedGraph<int>graph(edgesl);
    graph.print();
    graph.KruskalMinimumTreeIn(graph,v);
}
//有向有权图
void DriectedweightedGraphFormat(){
    /*vector<VertexPoint*>v=valsToVetsl(vector<vector<int>>{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}});
    vector<pair<pair<VertexPoint*,VertexPoint*>,int>>edgesl={
                                                    {{v[0],v[1]},2},{{v[0],v[3]},1},
                                                    {{v[1],v[3]},3},{{v[1],v[4]},10},
                                                    {{v[2],v[0]},4},{{v[2],v[5]},5},
                                                    {{v[3],v[2]},2},{{v[3],v[4]},2},{{v[3],v[5]},8},{{v[3],v[6]},4},
                                                    {{v[4],v[6]},1},
                                                    {{v[6],v[5]},1}};*/
    vector<VertexPoint*>v=valsToVetsl(vector<vector<int>>{{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7}});
    vector<pair<pair<VertexPoint*,VertexPoint*>,int>>edgesl={
                                                    {{v[0],v[1]},4},{{v[0],v[2]},2},
                                                    {{v[1],v[2]},1},{{v[1],v[3]},2},{{v[1],v[4]},4},
                                                    {{v[2],v[4]},2},
                                                    {{v[3],v[5]},3},
                                                    {{v[4],v[5]},3}};                                     
    DriectedWeightedGraph<int>graph(edgesl);
    graph.prints();
    for(auto vec:graph.GraphBFSIn(graph,v[0])){
        cout<<"("<<vec[0]<<" , "<<vec[1]<<")  ";
    }
    cout<<endl;
    NetWorkFlowProbl Net;
    unordered_map<VertexPoint*,vector<pair<VertexPoint*,int>>>CopysList=graph.duList;
    Net.NetWorkPro(graph,CopysList,v[0],v[5],v);
    Net.print();
    Net.NetWorkValue(v[0]);
}
//有向有权图的邻接矩阵
void DriectedWeightedGraphMatForamt(){
    vector<int>Adj={1,2,3,4,5,6,7};
    vector<vector<int>>Mat={{0,1,2},{0,3,1},
                            {1,3,3},{1,4,10},
                            {2,0,4},{2,5,5},
                            {3,2,2},{3,4,2},{3,5,8},{3,6,4},
                            {4,6,1},
                            {6,5,1}};
    DriectedWeightedGraphMatrix<int>Graph(Adj,Mat);
    cout<<"构造后的邻接矩阵 : "<<endl;
    Graph.print();
    cout<<"广度优先遍历"<<endl;
    for(int vec:Graph.GraphBFSMat(Graph,0)){
        cout<<" "<<vec<<" ";
    }
    cout<<endl;
    cout<<"深度优先遍历"<<endl;
    for(int vet:Graph.GraphDFSMat(Graph,0)){
        cout<<" "<<vet<<" ";
    }
    cout<<endl;
}
int main(){
    //UnDriectedUnWeightGraphForamt();
    //UnDriectedUnWeightedGraphMatrixFormat();
    //DriectedUnWeightedGraphFormat();
    //DricetedUnWeightedGraphMatrixformat();
    //UnDriectedWeightedGraphFormat();
    DriectedweightedGraphFormat();
    //DriectedWeightedGraphMatForamt();

    while(getchar()!='\n')
    continue;
    getchar();
    return 0;
}

#endif