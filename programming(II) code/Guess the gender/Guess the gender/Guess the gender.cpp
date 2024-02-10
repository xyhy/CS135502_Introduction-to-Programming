//
//  Guess the gender.cpp
//  Guess the gender
//
//  Created by 顏浩昀 on 2020/4/30.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "12742.h"

// TODO: Implement your constructor
Graph::Graph(int n){
    this->numberOfVertices = n;
    this->adjacencyList = new Vertex*[n];
    this->vertexInfo = new int[n];
    for(int i = 0; i < n; i ++){
        adjacencyList[i] = new Vertex(i);
        vertexInfo[i] = -1;
    }
}
// TODO: Implement function to add edge from srouce to destination, you can insert Vertex destination at the front of the list of adjacencyList[source]
void Graph::addEdge(int source, int destination){
    Vertex *tmp = this->adjacencyList[source];
    Vertex *target = new Vertex(destination);
    target->nextVertex = tmp->nextVertex;
    tmp->nextVertex = target;
}
// TODO: Implement a depth first search on the graph to solve the problem
//bool Graph::dfs(int vertex){
    
//}
// TODO: Implement your solver function
bool Graph::solver(){
    int n = this->numberOfVertices;
    int *a = this->vertexInfo;
    Vertex **tmp = this->adjacencyList;
    for(int i = 0; i < n; i++){
        Vertex *cur = tmp[i];
        if(a[cur->index] == -1) a[cur->index] = 0;
        while (1) {
            cur = cur->nextVertex;
            if(cur == nullptr)   break;
            if(a[cur->index] == -1) a[cur->index] = !a[tmp[i]->index];
            if(a[cur->index] == a[tmp[i]->index])   return 0;
        }
    }
    return 1;
}
// TODO: Implement the destructor
Graph::~Graph(){}
