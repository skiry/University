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

    void run1();
    //the main program of work 1

    void run2();
    //the main program of work 2

    int getNoOfVertices();
    //noOfVertices caller

    void printMenu();
    //print the main options

    void printMenu1();
    //print the options from work 1

    void printMenu2();
    //print the options from work 2

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

    void Bellman();
    //compute the min dist between 2 vertices/print if negative cycles exist

    void noOfWalks();
    //compute the number of distinct walks of minimum cost between two vertices

    void noOfWalksDAG();
    //compute the number of distinct walks between two vertices
};

#endif // UI_H
