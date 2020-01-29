#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <chrono>
#include <queue>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define NUMBER_OF_THREADS 2

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

int n1, m1, matrix1[MAX_HEIGHT][MAX_WIDTH];
int n2, m2, matrix2[MAX_HEIGHT][MAX_WIDTH];
int n3, m3, matrix3[MAX_HEIGHT][MAX_WIDTH];
int lines[MAX_HEIGHT], computed_cells;
int productResult1[MAX_HEIGHT][MAX_WIDTH];
int productResult2[MAX_HEIGHT][MAX_WIDTH];
int numberOfThreads = NUMBER_OF_THREADS;
thread threads1[NUMBER_OF_THREADS];
thread threads2[NUMBER_OF_THREADS];

template<typename T>
class ProducerConsumerQueue {
public:
    void enqueue(T val) {
        unique_lock<mutex> lock(mtx);
        q.push(val);
        cv.notify_one();
    }
    bool deque(T& val) {
        unique_lock<mutex> lock(mtx);
        while (true) {
            if (!q.empty()) {
                val = q.front();
                q.pop();
                return true;
            }
            if (isClosed) {
                return false;
            }
            cv.wait(lock);
        }
    }
    void close() {
        unique_lock<mutex> lock(mtx);
        isClosed = true;
        cv.notify_all();
    }
private:
    queue<T> q;
    mutex mtx;
    condition_variable cv;
    bool isClosed = false;
};

mutex m;
ProducerConsumerQueue<pair<int, int>> pc1, pc2;

void product1(int threadNumber) {
    pair<int, int> cell;
    while (pc1.deque(cell)) {
        int result = 0;
        for (int k = 0; k < m2; ++k)
            result += matrix1[cell.first][k] * matrix2[k][cell.second];
        productResult1[cell.first][cell.second] = result;
        m.lock();
        ++computed_cells;
        ++lines[cell.first];
        if (lines[cell.first] == m2) {
            m.unlock();
            for (int i = 0; i < m2; ++i) {
                pc2.enqueue(make_pair(cell.first, i));
            }
        }
        else {
            m.unlock();
        }

        if (computed_cells == n1 * m2) {
            pc2.close();
        }

    }
}

void product2(int threadNumber) {
    pair<int, int> cell;
    while (pc2.deque(cell)) {
        int result = 0;
        for (int k = 0; k < m3; ++k)
            result += productResult1[cell.first][k] * matrix3[k][cell.second];
        productResult2[cell.first][cell.second] = result;
    }
}

void readMatrices() {
    f >> n1 >> m1;

    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m1; ++j) {
            f >> matrix1[i][j];
        }
    }

    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m1; ++j) {
            cout << matrix1[i][j] << " ";
        }
        cout << endl;
    }

    f >> n2 >> m2;

    for (int i = 0; i < n2; ++i) {
        for (int j = 0; j < m2; ++j) {
            f >> matrix2[i][j];
        }
    }

    for (int i = 0; i < n2; ++i) {
        for (int j = 0; j < m2; ++j) {
            cout << matrix2[i][j] << " ";
        }
        cout << endl;
    }

    f >> n3 >> m3;

    for (int i = 0; i < n3; ++i) {
        for (int j = 0; j < m3; ++j) {
            f >> matrix3[i][j];
        }
    }

    for (int i = 0; i < n3; ++i) {
        for (int j = 0; j < m3; ++j) {
            cout << matrix3[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    
    readMatrices();
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numberOfThreads; ++i) {
        threads1[i] = thread(product1, i);
    }
    for (int i = 0; i < numberOfThreads; ++i) {
        threads2[i] = thread(product2, i);
    }

    for (int i = 0; i < n1; ++i)
        for (int j = 0; j < m2; ++j) {
            pc1.enqueue(make_pair(i, j));
        }

    pc1.close();

    for (int i = 0; i < numberOfThreads; ++i) {
        threads1[i].join();
    }
    for (int i = 0; i < numberOfThreads; ++i) {
        threads2[i].join();
    }
    
    cout << "Resuled product from the result of the first 2 matrices is:" << endl;

    for (int k = 0; k < n1; ++k) {
        for (int l = 0; l < m2; ++l)
            cout << productResult1[k][l] << " ";
        cout << endl;
    }

    cout << "Resuled product from the result of the first 2 matrices and the third matrix is: " << endl;

    for (int k = 0; k < n1; ++k) {
        for (int l = 0; l < m3; ++l)
            cout << productResult2[k][l] << " ";
        cout << endl;
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(end2 - start).count();

    cout << "Time taken: " << duration * 0.0000001;


    return 0;
}