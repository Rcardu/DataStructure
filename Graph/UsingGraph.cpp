#ifndef USINGGRAPH_H
#define USINGGRAPH_H
#include "..//utils//common.hpp"
#include "GraphAdjacency//GraphAdjacencyMatrix.h"
#include "GraphAdjacencyList//GraphAdjacencyList.h"
#include "GraphAdjacencyList//GraphAdjacencyListpoint.h"
#include "DirectedUnweightedGraph\DriectedUnweighitedGraph.h"
#include "DirectedUnweightedGraph\VertexPiont.h"
void UsMatrixFormat();
void UsGraphAdjacencyListFormat();
void UsDriectedUnweightedGraphFormat();

void UsMatrixFormat(){
    vector<int>vertiecs={1,2,3,4,5};
    vector<vector<int>>adjMat={{0,1},{0,3},{1,2},{2,3},{2,4},{3,4}};
    GraphMatrix<int>obj(vertiecs,adjMat);
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
void UsGraphAdjacencyListFormat(){
    /*��������*/
    vector<Vertex*>v=valsToVets(vector<int>{1,3,2,5,4});//��int����ת����vector<Vertex*>����
    vector<vector<Vertex*>>edges={{v[0],v[1]},{v[0],v[3]},{v[1],v[2]},
                                    {v[2],v[3]},{v[2],v[4]},{v[3],v[4]}};
    GraphAdjacencyListpoint<int>graph(edges);
    cout<<"\n����ٽ�����"<<endl;
    graph.print();
    graph.addEdge(v[0],v[2]);
    cout<<"\n��ӱ�1-2��ͼΪ:";
    graph.print();

    vector<Vertex*>vet=graph.graphBFS(graph,v[0]);
    cout<<"�������˳��Ϊ:"<<endl;
    printVector(vetsToVals(vet));

    vector<Vertex*>ves=graph.graphDFS(graph,v[0]);
    cout<<"������ȱ�����Ϊ:"<<endl;
    printVector(vetsToVals(ves));

    graph.removeEdge(v[0],v[1]);
    cout<<"\nɾ����1-3��ͼΪ:";
    graph.print();

    Vertex*v5=new Vertex(6);
    graph.addVertex(v5);
    cout<<"\n��Ӷ���6��ͼΪ:";
    graph.print();

    graph.removeVertex(v[1]);
    cout<<"\nɾ������3��ͼΪ:";
    graph.print();        


    for(auto vet:v){
        delete vet;
    }                       
}
void DriectedUnweightedGraphFormat(){
    vector<VertexPoint*>v=valsToVetsl(vector<vector<int>>{{1,1},{2,5},{3,2},{4,1},{5,3}});
    vector<vector<VertexPoint*>>edgesl={{v[0],v[1]},{v[0],v[3]},{v[0],v[4]},{v[1],v[2]},{v[2],v[3]},{v[2],v[4]},{v[3],v[4]}};
    DriectedUnweightedGraph<int>graph(edgesl);
    graph.prints();
    graph.addEdges(v[4],v[1]);
    cout<<endl;
    cout<<"��ӱ�5-2����ͼΪ��";
    graph.prints();
}
int main(){
    //UsMatrixFormat();
    //UsGraphAdjacencyListFormat();
    DriectedUnweightedGraphFormat();

    while(getchar()!='\n')
    continue;
    getchar();
    return 0;
}

#endif