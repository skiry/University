#include <bits/stdc++.h>
//#include "graph.cpp"
#include "ui.cpp"

using namespace std;

void smallTest(){
    int in, out, cost;
    Graph g = Graph(10);
    g.addEdge(1,2,100);
    std::tie(in, out, cost) = g.getEdge(1);

    UI ui;
    ui.run();
}
int main()
{
    smallTest();

    return 0;
}
