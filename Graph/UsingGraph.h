#ifndef USINGGRAPH_H
#define USINGGRAPH_H
#include "..//utils//common.hpp"
#include "GraphAdjacency//GraphAdjacencyMatrix.h"
void UsMatrixFormat();

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

#endif