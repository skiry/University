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

void Graph::bfs( std::unordered_map<int, int>& dist, std::stack<int>& s, std::unordered_map<int, int>& prev ){
    int edge, neighb;

   while( s.size() ){
        edge = s.top();
        s.pop();
        for( auto i : parseOut(edge) ){
            neighb = E.getOut(i);
            if( dist[neighb] == 0 || dist[neighb] > dist[edge] + 1){
                dist[neighb] = dist[edge] + 1;
                prev[neighb] = edge;
                s.push(neighb);
            }
        }
    }
}

void Graph::Tarjan( int& e, std::unordered_map<int, int>& scc, std::unordered_map<int, int>& visited,
 std::unordered_map<int, int>&lowlink, std::unordered_map<int, int>& level, std::stack<int>& s,
  std::unordered_map<int, bool>& onStack, int& index, int& comps ){

        int edge, aux;

        visited[e] = index;
        lowlink[e] = index;
        index++;
        s.push(e);
        onStack[e] = true;

        for( auto i : parseOut(e) ){
            edge = E.getOut(i);
            if( visited[edge] == 0 ){
                Tarjan(edge, scc, visited, lowlink, level, s, onStack, index, comps);
                lowlink[e] = std::min(lowlink[e], lowlink[edge]);
            }
            else if( onStack[edge] == true ){
                lowlink[e] = std::min(lowlink[e], visited[edge]);
            }
        }

        if( lowlink[e] == visited[e] ){
            ++comps;
            do{
                aux = s.top();
                s.pop();
                onStack[aux] = false;
                scc[aux] = comps;

            }while( aux != e);
        }

}

int Graph::Bellman( int& b, std::unordered_map<int, int>& dist, std::unordered_map<int, int>& prev ){
    int len = getNodes().size();

    for( int j = 0; j < len; ++j ){
        for( auto &i : E.getEdges() )
            if( dist[ std::get<1>(i.second) ] > dist[ std::get<0>(i.second) ] + std::get<2>(i.second) ){
                dist[ std::get<1>(i.second) ] = dist[ std::get<0>(i.second) ] + std::get<2>(i.second);
                prev[ std::get<1>(i.second) ] = std::get<0>(i.second);
            }
    }

    for( auto &i : E.getEdges() )
        if( dist[ std::get<1>(i.second) ] > dist[ std::get<0>(i.second) ] + std::get<2>(i.second) )
            return -1;

    return dist[b];
}

void Graph::backT( int& a, int& b, int& minim, int& actualCost,
                  int& counter, std::unordered_map< int, bool >& visited ){
    int edge;

    if( a == b ){
        if( actualCost < minim ){
            minim = actualCost;
            counter = 1;
        }
        else if( actualCost == minim ) ++ counter;
    }
    else{
        for( auto i : parseOut(a) ){

            edge = E.getOut(i);

            if( visited[edge] == false ){

                actualCost += std::get<2>( E.getEdge(i) );
                visited[edge] = true;
                backT(edge, b, minim, actualCost, counter, visited);
                actualCost -= std::get<2>( E.getEdge(i) );
                visited[edge] = false;
            }

        }
    }
}

void Graph::backTDAG( int& a, int& b, int& counter ){
    int edge;

    if( a == b ) ++counter;
    else
        for( auto i : parseOut(a) )
            backTDAG( edge = E.getOut(i), b, counter );
}

