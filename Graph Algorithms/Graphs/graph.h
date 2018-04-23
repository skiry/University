#ifndef GRAPH_H
#define GRAPH_H
#pragma once
#include <bits/stdc++.h>

template <typename T>
class Edge{
private:
    std::unordered_map< int, std::tuple< int, int, T > > E;
    //{ edge id, (source, destination, cost) }
public:
    Edge() {}
    void addEdge(int, int, int, T);
    //add an edge to the map

    std::tuple< int, int, T > getEdge(int in) {
        //get the edge with id in
        //if not existent, return sth with in and out 0 for identifying
        if( E.find(in) != E.end() )
                return E[in];
        std::tuple< int, int, T > sth{0, 0, std::get<2>(E.begin() -> second)};
        return sth;
    };
    void deleteEdge(int edge) { if(validEdge(edge)) E.erase(E.find(edge)); };
    //delete the edge with id edge

    void changeCost(int edge, int cost) {
        //update the cost for the edge with id edge
        std::tuple< int, int, T >
                nou{ std::get<0>(E[edge]),
                    std::get<1>(E[edge]), cost};
        E[edge] = nou;
    };

    bool validEdge(int edge) { if( E.find(edge) == E.end() ) return false; return true; }
    //true if edge is in E, false otherwise

    int getIn(int in) const { return std::get<0>(E.find(in) -> second); };
    //source no getter

    int getOut(int out) const { return std::get<1>(E.find(out) -> second); };
    //destination no getter

    ~Edge() {}
};

class Graph
{
public:
    std::unordered_set< int > Nodes;
    //the set of vertices
    std::unordered_map< int, std::unordered_map< int, int > > Gout;
    //the map of out edges from a vertex
    std::unordered_map< int, std::unordered_map< int, int > > Gin;
    //the map of in edges from a vertex
    Edge<int> E;
    int Edge_id;
public:
    Graph(int);
    Graph(const Graph& g);
    Graph() {}

    bool addEdge(int in,int out, int cost);
    //add the edge from in to out with the value cost

    bool deleteEdge(int in, int out);
    //delete the edge from in to out

    bool changeCost(int edge,int cost);
    //change the cost from in to out with cost

    bool isValid(int, int);
    //false is edge already exists/a vertex does not exist; true otherwise

    bool isEdge(int, int);
    //false is edge does not exist; true otherwise

    std::tuple< int, int, int > getEdge(int in) {
        //edge by id getter
        return E.getEdge(in);
    }

    int gimmeEid(int in, int out) { return Gout[in][out]; }
    //get the edge id of the edge from in to out

    std::unordered_set< int > getNodes() const { return this -> Nodes; }
    //nodes getter

    std::unordered_map< int, std::unordered_map< int, int > > getGout() const {
        return this -> Gout;
    }
    //gOut getter

    std::unordered_map< int, std::unordered_map< int, int > > getGin() const {
        return this -> Gin;
    }
    //gOut getter

    Edge<int> getE() const { return this -> E; }
    //edge getter

    int getEdgeId() const { return this -> Edge_id; }
    //edge id getter

    Graph& operator=(const Graph& g);
    //operator = overriding

    int noOfVertices() const { return Nodes.size(); }
    //return the number of vertices

    int getIn(int v) { return Gin[v].size(); }
    //get the number of in edges of v

    int getOut(int v) { return Gout[v].size(); }
    //get the number of out edges from v

    std::vector<int> parseIn(int);
    //get the edge id from the in edges of vertex

    std::vector<int> parseOut(int);
    //get the edge id from the out edges from vertex

    bool addVertex(int id);
    //true if vertex is not existent -> add vertex, false otherwise

    bool delVertex(int id);
    //true if vertex is existent -> delete vertex, false otherwise

    void bfs(std::unordered_map<int, int>&, std::stack<int>&, std::unordered_map<int, int>&);
    //compute the min. distance between 2 vertices
    
    void Tarjan(int&, std::unordered_map<int, int>&, std::unordered_map<int, int>&, std::unordered_map<int, int>&, 
        std::unordered_map<int, int>&, std::stack<int>&, std::unordered_map<int, bool>&, int&, int&);
    //compute the strongly connected components in O(n+m)
    
    ~Graph() {}

};

#endif // GRAPH_H
