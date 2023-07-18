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
    vector<VertexPoint*>v=valsToVetsl(vector<vector<int>>{{1,1},{2,5},{3,2},{4,1},{5,3}});
    vector<vector<VertexPoint*>>edgesl={{v[0],v[1]},{v[0],v[3]},{v[0],v[4]},{v[1],v[2]},{v[2],v[3]},{v[2],v[4]},{v[3],v[4]}};
    UnDriectedWeightedGraph<int>graph(edgesl);
    graph.print();
    graph.addEdge(v[4],v[1]);
    cout<<endl;
    cout<<"添加边5-2，后图为：";
    graph.print();
    for(auto vec:graph.UnDriectedWeightedGraphBFSIn(graph,v[0])){
        cout<<"("<<vec[0]<<" , "<<vec[1]<<")";
        cout<<" ---> ";
    }
    cout<<endl;
    cout<<"深度优先遍历："<<endl;
    for(auto vec:graph.UnDriectedWeightedGraphDFSIn(graph,v[0])){
        cout<<"("<<vec[0]<<" , "<<vec[1]<<")";
        cout<<" ---> ";
    }
}
//有向有权图
void DriectedweightedGraphFormat(){
    vector<VertexPoint*>v=valsToVetsl(vector<vector<int>>{{1,1},{2,5},{3,2},{4,1},{5,3}});
    vector<vector<VertexPoint*>>edgesl={{v[0],v[1]},{v[0],v[3]},{v[0],v[4]},{v[1],v[2]},{v[2],v[3]},{v[2],v[4]},{v[3],v[4]}};
    DriectedWeightedGraph<int>graph(edgesl);
    graph.prints();
    graph.addEdges(v[4],v[1]);
    cout<<endl;
    cout<<"添加边5-2，后图为：";
    graph.prints();
    for(auto vec:graph.GraphBFSIn(graph,v[0])){
        cout<<"("<<vec[0]<<" , "<<vec[1]<<")";
        cout<<" ---> ";
    }
    cout<<endl;
    cout<<"深度优先遍历："<<endl;
    for(auto vec:graph.GraphDFSIn(graph,v[0])){
        cout<<"("<<vec[0]<<" , "<<vec[1]<<")";
        cout<<" ---> ";
    }
}
//有向有权图的邻接矩阵
void DriectedWeightedGraphMatForamt(){
    vector<int>Adj={7,2,9,1,5};
    vector<vector<int>>Mat={{0,1,1},{0,3,1},{1,2,1},{2,3,1},{2,4,1},{3,4,1},{4,2,1},{3,0,1}};
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
    //DriectedweightedGraphFormat();
    DriectedWeightedGraphMatForamt();

    while(getchar()!='\n')
    continue;
    getchar();
    return 0;
}

#endif