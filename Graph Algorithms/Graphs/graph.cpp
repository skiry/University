#include "graph.h"
#include <bits/stdc++.h>

Graph::Graph(int n){
    for(int i = 0; i < n; i++)
        Nodes.insert(i);
    Edge_id = 1;
}

bool Graph::addEdge(int in, int out, int cost){
    if(! isValid(in, out)) return false;
    Gout[in][out] = Edge_id;
    Gin[out][in] = Edge_id;
    E.addEdge(Edge_id++, in, out, cost);
    return true;
}

bool Graph::isValid(int in, int out){
    auto it = Gout[in].find(out);
    if( it != Gout[in].end() ) return false;
    if( Nodes.find(in) == Nodes.end() ) return false;
    if( Nodes.find(out) == Nodes.end() ) return false;
    return true;
}

bool Graph::isEdge(int in, int out){
    auto it = Gout[in].find(out);
    if( it != Gout[in].end() ) return true;

    return false;
}

template <typename T>
void Edge<T>::addEdge(int Eid, int in, int out, T cost){
    E[Eid] ={in, out, cost};
}

Graph& Graph::operator=(const Graph& g){
    Nodes = g.getNodes();
    Gin = g.getGin();
    Gout = g.getGout();
    E = g.getE();
    Edge_id = g.getEdgeId();
    return *this;
}

Graph::Graph(const Graph& g){
    Nodes = g.getNodes();
    Gin = g.getGin();
    Gout = g.getGout();
    E = g.getE();
    Edge_id = g.getEdgeId();
}

bool Graph::deleteEdge(int in, int out){
    if( !isEdge(in, out) ) return false;

    E.deleteEdge(Gin[out][in]);

    auto it = Gin[out].find(in);
    Gin[out].erase(it);

    auto it2 = Gout[in].find(out);
    Gout[in].erase(it2);

    return true;
}


bool Graph::changeCost(int edge,int cost){
    if( !E.validEdge(edge) ) return false;
    if( !isEdge(E.getIn(edge), E.getOut(edge)) ) return false;

    E.changeCost(edge, cost);

    return true;
}


std::vector<int> Graph::parseIn(int v){
    std::vector<int> da;

    for( auto it : Gin[v] )
        da.push_back(it.second);

    return da;
}

std::vector<int> Graph::parseOut(int v){
    std::vector<int> da;

    for( auto it : Gout[v] )
        da.push_back(it.second);

    return da;
}

bool Graph::addVertex(int id){
    if( Nodes.find(id) != Nodes.end() ) return false;

    Nodes.insert(id);
    return true;
}

bool Graph::delVertex(int id){
    if( Nodes.find(id) == Nodes.end() ) return false;

    Nodes.erase(id);

    for( auto it : Gout[id] ){
        E.deleteEdge(it.second);
        Gin[it.first].erase(id);
    }
    Gout.erase(id);

    for( auto it : Gin[id] ){
        E.deleteEdge(it.second);
        Gout[it.first].erase(id);
    }
    Gin.erase(id);

    return true;
}






