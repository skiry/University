#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <Windows.h>
#include <chrono>
#include <algorithm>
#include <future>
#include <stack>

#define NODES_NUMBER 5
#define THREADS_NUMBER NODES_NUMBER
using namespace std;

vector<vector<int>> adjacency_matrix;
stack<int> path;
vector<stack<int>> paths;
thread threads[THREADS_NUMBER];
mutex m;

void print(vector<vector<int>> a) {
    for (int i = 0; i < NODES_NUMBER; ++i) {
        for (int j = 0; j < NODES_NUMBER; ++j) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void bkt(int node, vector<vector<int>> adjacency_matrix, int vertices, int startingPoint, stack<int> path) {
    path.push(node);
    if (!vertices and node == startingPoint) {
        m.lock();
        paths.push_back(path);
        m.unlock();
    }
    for (int i = 0; i < NODES_NUMBER; ++i) {
        if (adjacency_matrix[node][i] == 1) {
            adjacency_matrix[node][i] = 0;
            bkt(i, adjacency_matrix, vertices - 1, startingPoint, path);
            adjacency_matrix[node][i] = 1;
        }
    }
    path.pop();
}

int my_rand() {
    return rand() % 2;
}

int main() {
    cout << "The random adjacency matrix generated: " << endl;
    int vertices = 0;
    for (int i = 0; i < NODES_NUMBER; ++i) {
        vector<int> result;
        adjacency_matrix.push_back(result);
        for (int j = 0; j < NODES_NUMBER; ++j) {
            adjacency_matrix[i].push_back(my_rand());
            if (adjacency_matrix[i][j]) {
                ++vertices;
            }
            cout << adjacency_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Number of vertices: " << vertices << endl;
    /*
    vertices = 6;
    for (int i = 0; i < NODES_NUMBER; ++i) {
        for (int j = 0; j < NODES_NUMBER; ++j) {
            adjacency_matrix[i][j] = 0;
        }
    }
    adjacency_matrix[0][2] = 1;
    adjacency_matrix[2][1] = 1;
    adjacency_matrix[1][3] = 1;
    adjacency_matrix[3][1] = 1;
    adjacency_matrix[1][4] = 1;
    adjacency_matrix[4][0] = 1;
    // make it non hamiltonian
    //adjacency_matrix[2][4] = 1; vertices++;
    */

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < THREADS_NUMBER; ++i) {
        threads[i] = thread(bkt, i, adjacency_matrix, vertices, i, path);
    }

    for (int i = 0; i < THREADS_NUMBER; ++i) {
        threads[i].join();
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(end2 - start).count();

    cout << "Time taken: " << duration * 0.0000001;

    if (paths.size()) {
        cout << "\nThere exists a hamiltonian cycle and the path is the following: \n";
        stack<int> toReverse;
        for (auto path : paths) {
            while (path.size()) {
                toReverse.push(path.top());
                path.pop();
            }
            while (toReverse.size()) {
                cout << toReverse.top() << " ";
                toReverse.pop();
            }
            cout << endl;
        }
    }
    else {
        cout << "\nThere does not exist a hamiltonian cycle.";
    }
start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < THREADS_NUMBER; ++i) {
        bkt(i, adjacency_matrix, vertices, i, path);
    }


     end2 = std::chrono::high_resolution_clock::now();
   duration = chrono::duration_cast<std::chrono::microseconds>(end2 - start).count();

    cout << "Time taken: " << duration * 0.0000001;


    return 0;
}