#include "ui.h"
#include "graph.cpp"
#include <bits/stdc++.h>

UI::UI()
{
    int n, m, in, out, cost;
    std::cout << "Filename: ";
    std::getline(std::cin, fileName);
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
        std::cin >> n >> m;
        Graph g(n);
        this -> G = g;
        for(int i = 0; i < m; ++i){
            std::cin >> in >> out >> cost;
            G.addEdge(in, out, cost);
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
        // = \+ ()
    }

}

int UI::getNoOfVertices(){
    return G.noOfVertices();
}

void UI::printMenu(){
    std::cout << "0. Exit" << '\n';
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
    int vertex, in, out, cost;

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
