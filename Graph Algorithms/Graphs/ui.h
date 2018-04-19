#ifndef UI_H
#define UI_H
#pragma once
#include <bits/stdc++.h>
#include "graph.h"

class UI
{
private:
    std::string fileName = "";
    Graph G;
public:
    UI();
    //the constructer; read the filename

    void run();
    //the main program

    int getNoOfVertices();
    //noOfVertices caller

    void printMenu();
    //print the options

    void checkEdge();
    //print the options

    void getIn();
    //get the in degree of vertex

    void getOut();
    //get the out degree of vertex

    void gIn();
    //iterate in

    void gOut();
    //iterate out

    void byEdge();
    //show the end points of the given edge id

    void updEdge();
    //update the information of the given edge id

    void addEdge();
    //add an edge

    void delEdge();
    //delete an edge

    void addVertex();
    //add a vertex

    void delVertex();
    //delete a vertex
    
    void bfs();
    //compute forward bfs
    
    void Tarjan();
    //compute sccs
};

#endif // UI_H
