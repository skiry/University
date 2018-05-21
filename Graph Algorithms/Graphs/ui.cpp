#include "ui.h"
#include "graph.cpp"
#include <bits/stdc++.h>
#define INF 99999999

UI::UI()
{
    int n, m, in, out, cost, a, nos;

    std::cout << "Activities(1) or a simple directed graph(2)?" << '\n';
    std::cin >> a;

    std::cout << "Filename: ";
    std::cin.ignore();
    std::getline(std::cin, fileName);
    if( a == 2 ){
        if( fileName != "") {
            std::ifstream f(fileName);
            f >> n >> m;
            Graph g = Graph(n);
            this -> G = g;
            for(int i = 0; i < m; ++i){
                f >> in >> out >> cost;
                G.addEdge(in, out, cost);
            }
        }
        else{
            std::cout << "No. of nodes: ";
            std::cin >> n;
            std::cout << "No. of edges: ";
            std::cin >> m;
            Graph g(n);
            this -> G = g;
            for(int i = 0; i < m; ++i){
                std::cout << "From: ";
                std::cin >> in;
                std::cout << "To: ";
                std::cin >> out;
                std::cout << "Cost: ";
                std::cin >> cost;
                G.addEdge(in, out, cost);
            }
        }
    }
    else if( a == 1 ){
        if( fileName != "") {
            std::ifstream f(fileName);
            f >> n;
            std::vector<int> dur;
            for(int i = 0; i < n; ++i){
                f >> cost;
                dur.push_back(cost);
            }
            Graph g = Graph(n+3);
            this -> G = g;
            for(int i = 0; i < n; ++i){
                f >> in >> nos;
                for(int j = 0; j < nos; ++j){
                    f >> out;
                    G.addEdge(out, in, dur[out - 1]);
                }
            }
            for( auto i : G.getNodes() )
                if( G.getIn(i) == 0 && i <= n && i > 0)
                    //edge from n+1 to i
                    G.addEdge(n+1, i, 0);
                else if( G.getOut(i) == 0 && i <= n && i > 0)
                    //edge from i to n+2
                    G.addEdge(i, n+2, dur[i - 1]);
        }
        else{
            std::cout << "No. of activities: ";
            std::cin >> n;
            std::vector<int> dur;
            for(int i = 0; i < n; ++i){
                std::cout << "Duration for activity " << i + 1<< ": ";
                std::cin >> cost;
                dur.push_back(cost);
            }
            Graph g(n+3);

            //from n+1 to all nodes without inbound neighbours
            //from all nodes without outbound neighbours to n+2
            this -> G = g;
            for(int i = 0; i < n; ++i){
                std::cout << "Activity number: ";
                std::cin >> in;
                std::cout << "No. of prerequisites: ";
                std::cin >> nos;
                for(int j = 0; j < nos; ++j){
                    std::cout << "Prerequisite number " << j + 1 <<": ";
                    std::cin >> out;
                    G.addEdge(out, in, dur[out - 1]);
                }
                std::cout << '\n';
            }
            for( auto i : G.getNodes() )
                if( G.getIn(i) == 0 && i <= n && i > 0){
                    //edge from n+1 to i
                    G.addEdge(n+1, i, 0);}
                else if( G.getOut(i) == 0 && i <= n && i > 0){
                    //edge from i to n+2
                    G.addEdge(i, n+2, dur[i - 1]);}
        }
    }
}

void UI::run(){
    int command;
    while(true){
        printMenu();
        std::cin >> command;
        if( command == 0 ) {
            std::cout << "Have a great day !" << '\n';
            break;
        }
        else if( command == 1 )
            run1();
        else if( command == 2 )
            run2();
    }

}

void UI::run1(){
    int command;
    while(true){
        printMenu1();
        std::cin >> command;
        if( command == 0 ) {
            break;
        }
        else if( command == 1 )
            std::cout << "The number of vertices in the graph is " << getNoOfVertices() << '\n';
        else if( command == 2 )
            checkEdge();
        else if( command == 3 )
            getIn();
        else if( command == 4 )
            getOut();
        else if( command == 5 )
            gIn();
        else if( command == 6 )
            gOut();
        else if( command == 7 )
            byEdge();
        else if( command == 8 )
            updEdge();
        else if( command == 9 )
            addEdge();
        else if( command == 10 )
            delEdge();
        else if( command == 11 )
            addVertex();
        else if( command == 12 )
            delVertex();
    }

}

void UI::run2(){
    int command;
    while(true){
        printMenu2();
        std::cin >> command;
        if( command == 0 ) {
            break;
        }

        else if( command == 1 )
            bfs();
        else if( command == 2 )
            Tarjan();
        else if( command == 3 )
            Bellman();
        else if( command == 4 )
            noOfWalks();
        else if( command == 5 )
            noOfWalksDAG();
        else if( command == 6 )
            DAGtsort();
        else if( command == 7 )
            times();
        else if( command == 8 )
            b2();
        else if( command == 9 )
            b3();
        else if( command == 10 )
            backPath();
    }

}

int UI::getNoOfVertices(){
    return G.noOfVertices();
}

void UI::printMenu1(){
    std::cout << "0. Back" << '\n';
    std::cout << "1. Show the number of vertices." << '\n';
    std::cout << "2. Check edge." << '\n';
    std::cout << "3. Get the IN degree." << '\n';
    std::cout << "4. Get the OUT degree." << '\n';
    std::cout << "5. Iterate IN." << '\n';
    std::cout << "6. Iterate OUT." << '\n';
    std::cout << "7. Show edges by edge id." << '\n';
    std::cout << "8. Modify the information of an edge." << '\n';
    std::cout << "9. Add Edge." << '\n';
    std::cout << "10. Delete Edge." << '\n';
    std::cout << "11. Add Vertex." << '\n';
    std::cout << "12. Delete Vertex." << '\n';
}

void UI::printMenu2(){
    std::cout << "0. Back" << '\n';
    std::cout << "1. FWD BFS." << '\n';
    std::cout << "2. Print the strongly connected components." << '\n';
    std::cout << "3. Bellman-Ford." << '\n';
    std::cout << "4. The no of distinct walks of min cost from a graph with costs, having no negative cost cycles." << '\n';
    std::cout << "5. The no of distinct walks from a directed acyclic graph." << '\n';
    std::cout << "6. Verify DAG and compute a topological sorting." << '\n';
    std::cout << "7. Earliest and latest starting times and the critical activities." << '\n';
    std::cout << "8. Bonus 2." << '\n';
    std::cout << "9. Bonus 3." << '\n';
    std::cout << "10. Given a digraph with costs and two vertices, find a minimum cost path between them (negative cost cycles may exist in the graph). " << '\n';

}

void UI::printMenu(){
    std::cout << "0. Exit" << '\n';
    std::cout << "1. Work 1." << '\n';
    std::cout << "2. Work 2." << '\n';
}

void UI::checkEdge(){
    int x, y;

    std::cout << "In: ";
    std::cin >> x;
    std::cout << "Out: ";
    std::cin >> y;

    if( G.isEdge(x, y) == true ) std::cout << "The edge "
                                       "exists and has the edge id " << G.gimmeEid(x, y) << '\n';
    else std::cout << "The edge does not exist" << '\n';
}

void UI::getIn(){
    int vertex;

    std::cout << "Vertex: ";
    std::cin >> vertex;

    std::cout << "The number of in vertices of the vertex " << vertex << " is " << G.getIn(vertex) << '\n';
}

void UI::getOut(){
    int vertex;

    std::cout << "Vertex: ";
    std::cin >> vertex;

    std::cout << "The number of out vertices from the vertex " << vertex << " is " << G.getOut(vertex) << '\n';
}

void UI::gIn(){
    int vertex;

    std::cout << "Vertex: ";
    std::cin >> vertex;

    for( auto it: G.parseIn(vertex) ) std::cout << it << " ";
    std::cout << '\n';
}

void UI::gOut(){
    int vertex;

    std::cout << "Vertex: ";
    std::cin >> vertex;

    for( auto it: G.parseOut(vertex) ) std::cout << it << " ";
    std::cout << '\n';
}

void UI::byEdge(){
    int vertex, in, out, cost;

    std::cout << "Vertex: ";
    std::cin >> vertex;

    std::tie(in, out, cost) = G.getEdge(vertex);
    if(!( in == out && in == 0) ) std::cout << "The end points of " << vertex << " are " << in << " and " <<
                 out << " with the cost " << cost << '\n';
    else std::cout << "Edge inexistent." << '\n';
}

void UI::updEdge(){
    int vertex, cost;

    std::cout << "Vertex: ";
    std::cin >> vertex;

    std::cout << "New cost: ";
    std::cin >> cost;

    if( G.changeCost(vertex, cost) )
            std::cout << "The vertex " << vertex << " has been updated "
                                             " with the cost " << cost << '\n';
    else std::cout << "Vertex is inexistent." << '\n';
}

void UI::addEdge(){
    int in, out, cost;

    std::cout << "Source: ";
    std::cin >> in;

    std::cout << "Destination: ";
    std::cin >> out;

    std::cout << "Cost: ";
    std::cin >> cost;

    if( G.addEdge(in, out, cost) )
            std::cout << "The edge has been added " << '\n';
    else std::cout << "Edge could not be added." << '\n';
}

void UI::delEdge(){
    int in, out;

    std::cout << "Source: ";
    std::cin >> in;

    std::cout << "Destination: ";
    std::cin >> out;

    if( G.deleteEdge(in, out) )
            std::cout << "The edge has been deleted " << '\n';
    else std::cout << "The edge could not be deleted." << '\n';
}

void UI::addVertex(){
    int id;

    std::cout << "Vertex id: ";
    std::cin >> id;

    if( G.addVertex(id) )
            std::cout << "The vertex has been added " << '\n';
    else std::cout << "The vertex already exists." << '\n';
}

void UI::delVertex(){
    int id;

    std::cout << "Vertex id: ";
    std::cin >> id;

    if( G.delVertex(id) )
            std::cout << "The vertex has been deleted " << '\n';
    else std::cout << "The vertex does not exist." << '\n';
}

void UI::bfs(){
    int id1, id2, nr, now;
    std::unordered_map<int, int> dist, prev;
    std::stack<int> s, res;

    std::cout << "From: ";
    std::cin >> id1;

    std::cout << "To: ";
    std::cin >> id2;

    dist[id1] = 1;
    s.push(id1);
    G.bfs(dist, s, prev);

    if( dist[id2] != 0 ){
            std::cout << "The distance between " << id1 << " and " << id2 << " is " << dist[id2] - 1<< '\n';
            nr = dist[id2] - 1;
            now = id2;
            std::cout << "The path is: ";
            while( nr >= 0 ){
                --nr;
                res.push(now);
                now = prev[now];
                }
            while( res.size() ){
                std::cout << res.top() << " ";
                res.pop();
                }
                std::cout << '\n';
        }
    else
        std::cout << "There is no path between them." << '\n';
}

void UI::Tarjan(){
    std::unordered_map<int, int> scc, visited, lowlink, level;
    std::stack<int> s;
    std::unordered_map<int, bool> onStack;
    int index = 0, comps = 0;

    for( auto i : G.getNodes() )
        if( visited[i] == 0 )
            G.Tarjan(i, scc, visited, lowlink, level, s, onStack, index, comps);

    for( auto i : scc ){
        if( level[i.first] == 0 ){
            std::cout << "The strongly connected component " << i.second << " is made of: ";
            for( auto j : scc )
                if( i.second == j.second ){
                    level[j.first] = 1;
                    std::cout << j.first << " ";
                }
            std::cout << '\n';
        }
    }
}

void UI::Bellman(){
    int id1, id2, ress , now;
    std::unordered_map< int, int > dist, prev;
    std::stack<int> res;

    std::cout << "From: ";
    std::cin >> id1;

    std::cout << "To: ";
    std::cin >> id2;

    for( auto i : G.getNodes() )
        dist[i] = INF, prev[i] = -1;

    dist[id1] = 0;

    ress = G.Bellman( id2, dist, prev );
    if( ress == -1 )
        std::cout << "There is a negative cost cycle." << '\n';
    else if( ress == INF ) std::cout << "There is no path.\n";
    else{
        std::cout << "The minimum distance between " << id1 << " and " << id2 << " is " << ress << '\n';

    now = id2;
    while( now != id1 ){
        res.push(now);
        now = prev[now];
        }
    res.push(now);
    now = prev[now];

    while( res.size() ){
        std::cout << res.top() << " ";
        res.pop();
        }
        std::cout << '\n';}

}

void UI::noOfWalks(){
    int id1, id2, res = 0, minim = INF, actualCost = 0;
    std::unordered_map< int, bool > visited;
std::unordered_map< int, int > dist, prev, walks;
    std::cout << "From: ";
    std::cin >> id1;

    std::cout << "To: ";
    std::cin >> id2;

    G.backT( id1, id2, minim, actualCost, res, visited );

    for( auto i : G.getNodes() )
        dist[i] = INF, prev[i] = -1;

    dist[id1] = 0;

    std::cout << "The number of minimum cost walks between " << id1 << " and " << id2 << " is "
              << G.difWalksOfMinCost( id1, id2, dist, prev, walks) << '\n';

}

void UI::noOfWalksDAG(){
    int id1, id2, res = 0;

    std::cout << "From: ";
    std::cin >> id1;

    std::cout << "To: ";
    std::cin >> id2;

    G.backTDAG( id1, id2, res );

    std::cout << "The number of distinct walks between " << id1 << " and " << id2 << " is " << res << '\n';

}

void UI::DAGtsort(){
    if( G.isDAG() ){
        std::cout << "It is a directed acyclic graph." << '\n';
        std::vector<int> ts = G.TOPsort();

        std::cout << "Topological Sorting: ";
        for( auto i : ts )
            std::cout << i << " ";
        std::cout << '\n';

    }
    else
        std::cout << "It is not a directed acyclic graph." << '\n';
}

void UI::times(){
    int c1, c2, cnt = -1, val;
    std::vector< std::tuple< int, int > > ts = G.times();

    for( auto [ c1, c2 ] : ts ){
        std::cout << "The earliest starting time for vertex " << ++cnt << " is " << c1 <<
                     " and the latest is " << c2 << '\n';
        val = c2;
    }
    std::cout << '\n' << "The total time needed is: " << val << '\n';

    std::cout << '\n' << "The critical activities are: ";
    cnt = -1;
    for( auto [ c1, c2 ] : ts )
        if( c2 - c1 == 0 )
            std::cout << ++cnt << " ";
        else ++cnt;
    std::cout << '\n';
}

void UI::b2(){
    int a, b, res;
    /*std::vector<int> tSort;
    std::unordered_map<int, bool> vis;
    G.DFS(a=1, vis, tSort);
    std::reverse(tSort.begin(), tSort.end());
    std::cout << "Topological sorting: ";
    for(auto i : tSort)
        std::cout << i << " ";*/

    DAGtsort();
    std::cout << "\nFrom: ";
    std::cin >> a;

    std::cout << "To: ";
    std::cin >> b;
    G.backTDAG(a, b, res);

    std::cout << "The number of distinct paths is " << res << '\n';
}

void UI::b3(){
    int a, b, res;
    /*std::vector<int> tSort;
    std::unordered_map<int, bool> vis;
    G.DFS(a=1, vis, tSort);
    std::reverse(tSort.begin(), tSort.end());
    std::cout << "Topological sorting: ";
    for(auto i : tSort)
        std::cout << i << " ";*/

    DAGtsort();
    std::cout << "\nFrom: ";
    std::cin >> a;

    std::cout << "To: ";
    std::cin >> b;
    G.totMinCost(a, b, res);

    std::cout << "The number of distinct paths of min cost is " << res << '\n';
}

void UI::backPath(){
    int id1, id2, res = 0, min = 99999;
    std::unordered_map<int, int> vis;
    std::stack<int> par;
    std::vector<int> els;

    std::cout << "From: ";
    std::cin >> id1;

    std::cout << "To: ";
    std::cin >> id2;

    G.backPath( id1, id2, res, vis, par, min, els );

    std::cout << "The minimum cost path between " << id1 << " and " << id2 << " is " << min << '\n';
    std::reverse( els.begin(), els.end() );
    std::cout << "The path is: " << id1 << " ";
    for( const auto& i : els )
        std::cout << i << " ";
    std::cout << '\n';
}
