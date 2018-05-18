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

void Graph::DFS(int & node, std::unordered_map< int, bool >& vis, std::vector<int>& tSort){
    int var;
    vis[node] = true;
    for( auto i : parseOut(node) )
        if(vis[E.getOut(i)] == false)
            DFS(var = E.getOut(i), vis, tSort);

    tSort.push_back(node);
}

int Graph::difWalksOfMinCost( int& a, int& b, std::unordered_map<int, int>& dist,
                    std::unordered_map<int, int>& prev,  std::unordered_map<int, int>& walks){

    std::vector<int> tSort;
    std::unordered_map<int, bool> vis;

    int len = getNodes().size();

    for( int j = 0; j < len; ++j ){
        for( auto &i : E.getEdges() )
            if( dist[ std::get<1>(i.second) ] > dist[ std::get<0>(i.second) ] + std::get<2>(i.second) ){
                dist[ std::get<1>(i.second) ] = dist[ std::get<0>(i.second) ] + std::get<2>(i.second);
                prev[ std::get<1>(i.second) ] = std::get<0>(i.second);
            }
    }
    DFS(a,vis,tSort);
    std::reverse(tSort.begin(), tSort.end());
    for(auto i : tSort) walks[i] = 0;
    walks[a]=1;
    for(auto i : tSort){
        for( auto j : parseOut(i) )
            if( dist[ E.getOut(j) ] == dist[i] + E.getCost(j) )
                walks[E.getOut(j)] += walks[i];
    }
    return walks[b];
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


    std::vector<int> tSort;
    std::unordered_map<int, bool> vis;
    std::unordered_map<int, int> walks;

    DFS(a,vis,tSort);
    std::reverse(tSort.begin(), tSort.end());
    for(auto i : tSort) walks[i] = 0;
    walks[a] = 1;
    for( auto i : tSort )
        for( auto j : parseOut(i) )
            walks[ E.getOut(j) ] += walks[i];
    counter = walks[b];
}

bool Graph::isDAG(){
    std::unordered_map<int, int> vis;
    std::queue<int> q;
    int node, edge;

    q.push(1);
    //start from the first vertex

    while( q.size() ){
        node = q.front();
        q.pop();
        vis[ node ] = 1;
        for( auto i : parseOut( node ) ){
            edge = E.getOut(i);
            for( auto j : parseOut( edge ) )
                if( vis[ E.getOut(j) ] == 1 )
                    return false;
            if( vis[ edge ] == 0 )
                q.push(edge);
        }
    }

    return true;
}

std::vector<int> Graph::TOPsort(){
    std::queue<int> q;
    std::vector<int> res;
    std::unordered_map<int, int> deg;
    int node, x = (int)(getNodes().size() - 1 ), y = (int)(getNodes().size() - 2 );

    for( auto i : getNodes() )
        deg[i] = getOut(i);
    q.push( getNodes().size() - 1 );
    //start from the hard-coded 'finish' vertex

    while( q.size() ){
        node = q.front();
        q.pop();
        if( node != x && node != y )
            //exclude the hard-coded 'start' and 'finish' vertices
            res.push_back(node);
        for( auto i : parseIn(node) ){
            if( !(--deg[ E.getIn(i) ]) )
                q.push( E.getIn(i) );
        }
    }
    return res;
}

std::vector< std::tuple<int, int> > Graph::times(){
    std::vector< std::tuple<int, int> > ts;
    std::unordered_map< int, int > earl, lat, vis;
    std::queue< int > q;
    int node, firstOnes = 1;

    q.push( getNodes().size() - 2 );
    //the starting vertex
    earl[ getNodes().size() - 2 ] = 0;

    while( q.size() ){
        node = q.front();
        q.pop();
        vis[ node ] = 1;
        if( firstOnes ) --firstOnes;

        for( auto i : parseOut( node ) ){
            if( !firstOnes )
                earl[ E.getOut(i) ] = std::max( earl[ E.getOut(i) ], earl[ node ] + E.getCost(i) );
            else{
                earl[ E.getOut(i) ] = E.getCost( gimmeEid( E.getOut(i), E.getOut(parseOut( E.getOut(i) )[0] ) ));
            }
            if( vis[ E.getOut(i) ] == 0 )
                q.push( E.getOut(i) );
        }
    }

    q.push( getNodes().size() - 1 );
    //the ending vertex

    for( auto i : getNodes() )//reset the visited array
        vis[i] = lat[i] = 0;

    lat[ getNodes().size() - 1 ] = earl[ getNodes().size() - 1 ];

    while( q.size() ){
        node = q.front();
        q.pop();
        vis[ node ] = 1;
        for( auto i : parseIn( node ) ){
            if( lat[ E.getIn(i) ] == 0 ){
                //std::cout << E.getIn(i) << "->" << E.getOut(i) << "=" << lat[ E.getOut(i) ] <<'\n';//<< " / " << lat[ E.getOut(i) ] - E.getCost(i) << '\n';
                lat[ E.getIn(i) ] = lat[ E.getOut(i) ] - E.getCost(i);
            }
            else{
                lat[ E.getIn(i) ] = std::min( lat[ E.getIn(i) ], lat[ E.getOut(i) ] - E.getCost(i) );
                //std::cout << E.getIn(i) << "->" << E.getOut(i) << "=" << lat[ E.getIn(i) ]<< " / " << lat[ E.getOut(i) ] - E.getCost(i) << '\n';
    }
            if( vis[ E.getIn(i) ] == 0 )
                q.push( E.getIn(i) );
        }
    }

    q.push( getNodes().size() - 1 );
    //the ending vertex

    for( auto i : getNodes() )//reset the visited array
        vis[i] = 0;

    while( q.size() ){
        node = q.front();
        q.pop();
        vis[ node ] = 1;
        for( auto i : parseIn( node ) ){
                lat[ E.getIn(i) ] = std::min( lat[ E.getIn(i) ], lat[ E.getOut(i) ] - E.getCost(i) );
                //std::cout << E.getIn(i) << "->" << E.getOut(i) << "=" << lat[ E.getIn(i) ]<< " / " << lat[ E.getOut(i) ] - E.getCost(i) << '\n';

            if( vis[ E.getIn(i) ] == 0 )
                q.push( E.getIn(i) );}
    }
    std::unordered_set<int> nodes = getNodes();
    std::vector<int> sortedNodes;
    for( auto i : nodes )
        sortedNodes.push_back(i);
    std::sort(sortedNodes.begin(), sortedNodes.end() );
    for( auto i : sortedNodes ){
        //std::cout<<"i:"<<i<<" "<<earl[i]<<" "<<lat[i]<<'\n';
        ts.push_back( std::make_tuple( earl[i], lat[i] ) );
    }

    return ts;

}

void Graph::totMinCost( int& a, int& b, int& counter ){
        std::vector<int> tSort;
        std::unordered_map<int, bool> vis;
        std::unordered_map<int, int> walks, cost;

        DFS(a,vis,tSort);
        std::reverse(tSort.begin(), tSort.end());
        for(auto i : tSort) walks[i] = 0, cost[i] = 999999;
        walks[a] = 1;
        cost[a] = 0;
        for( auto i : tSort )
            for( auto j : parseOut(i) )
                if( cost[ E.getOut(j) ] == cost[i] + E.getCost(j) ){
                    walks[ E.getOut(j) ] += walks[i];
                }
                else if( cost[ E.getOut(j) ] > cost[i] + E.getCost(j) ){
                    cost[ E.getOut(j) ] = cost[i] + E.getCost(j);
                    walks[ E.getOut(j) ] = walks[i];
                }
        counter = walks[b];
}
