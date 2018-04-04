#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <random> //random
#include <functional> //bind

class Graph{
	public:
		Graph(int vertices) : in(vertices), out(vertices) {};
		bool addEdge(int v1, int v2){
			if(isEdge(v1, v2) == true)
				return false;
			else{
				in[v2].push_back(v1);
				out[v1].push_back(v2);
				return true;
			}
		}
		std::vector<int> parseX() const {
			std::vector<int> retV(in.size());
			for(int i = 0; i < in.size(); ++i)
				retV[i] = i;
			return retV;
		}
		std::vector<int> parseNin(int v) const { return in[v]; }
		std::vector<int> parseNout(int v) const { return out[v]; }
		bool isEdge(int v1, int v2){
			return std::find(out[v1].begin(), out[v1].end(), v2) != out[v1].end();
		}
	private:
		std::vector<std::vector<int>> in;
		std::vector<std::vector<int>> out;

};

void printGraph(const Graph& g){
	for (int i : g.parseX()) {
		std::cout << "Vertex " << i << " has inbound : ";
		for(int j : g.parseNin(i))
			std::cout << j << " ";
		std::cout << "\n and outbound : ";
		for(int j : g.parseNout(i))
			std::cout << j << " ";
		std::cout << "\n";
	}
}

void smallTest(){
	Graph g(4);
	g.addEdge(1,2);
	g.addEdge(3,1);
	g.addEdge(2,3);
	assert(g.addEdge(2,3) == false);
	g.addEdge(2,1);
	printGraph(g);
}

void bigTest(){
	int n = 10, m = 20;
	Graph g(n);

	std::chrono::high_resolution_clock::time_point
		start = std::chrono::high_resolution_clock::now();
	
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, n-1);
	int dice_roll = distribution (generator); // generates number in range 0..n-1
	
	auto randomVertex = std::bind (distribution, generator);

	for(int i = 0; i < m; ++i)
	{
		while(g.addEdge(randomVertex(), randomVertex()) == false);
	}

	std::chrono::high_resolution_clock::time_point
		end = std::chrono::high_resolution_clock::now();
	
	std::cout << std::chrono::duration_cast<std::chrono::microseconds(end-start).count() << '\n';
	printGraph(g);

	std::chrono::high_resolution_clock::time_point
		begin = std::chrono::high_resolution_clock::now();

	for(int i : g.parseX()) {
		for(int j : g.parseNin(i))
			;
	}
	std::chrono::high_resolution_clock::time_point
		after = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::microseconds(after-begin).count() << '\n';
}

int main(){
	/*
	Graph g = Graph(10);
	if(g.addEdge(1,2) == false) std::cout << "\nAlready existing...";
	else std::cout << "\nAdded!";
	if(g.addEdge(1,2) == false) std::cout << "\nAlready existing...";
	else std::cout << "\nAdded!";
	printGraph(g);*/
	bigTest();
	return 0;
}
