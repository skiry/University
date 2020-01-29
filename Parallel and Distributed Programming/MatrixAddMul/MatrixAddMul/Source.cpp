#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <chrono>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define NUMBER_OF_THREADS 9

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

int n1, m1, matrix1[MAX_HEIGHT][MAX_WIDTH];
int n2, m2, matrix2[MAX_HEIGHT][MAX_WIDTH];
int matrix1copy[MAX_HEIGHT][MAX_WIDTH];
int productResult[MAX_HEIGHT][MAX_WIDTH];
int numberOfThreads = NUMBER_OF_THREADS;
thread threads[NUMBER_OF_THREADS];

void sum(int threadNumber) {
    int from = threadNumber * ((int)(n1 * m1) / numberOfThreads);
    int to = from + ((int)(n1 * m1) / numberOfThreads) - 1;
    int line, column;
    for (int j = from; j <= to; ++j) {
        line = (int)j / m1;
        column = j % m1;
        matrix1[line][column] += matrix2[line][column];
    }
}

void product(int threadNumber) {
    int from = threadNumber * ((int)(n1 * m2) / numberOfThreads);
    int to = from + ((int)(n1 * m2) / numberOfThreads) - 1;
    int line, column, result;
    
    for (int j = from; j <= to; ++j) {
        line = (int)j / m2;
        column = j % m2;
        result = 0;
        for (int k = 0; k < m1; ++k)
            result += matrix1copy[line][k] * matrix2[k][column];
        productResult[line][column] = result;
    }
}
int main() {
    f >> n1 >> m1;

    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m1; ++j) {
            f >> matrix1[i][j];
            matrix1copy[i][j] = matrix1[i][j];
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

    for (int i = 0; i < numberOfThreads; ++i) {
        threads[i] = thread(sum, i);
    }
    for (int i = 0; i < numberOfThreads; ++i) {
        threads[i].join();
    }

    int remainingFrom = (numberOfThreads - 1) * ((int)(n1 * m1) / numberOfThreads) + ((int)(n1 * m1) / numberOfThreads);
    int line, column, result;

    for (int j = remainingFrom; j < n1 * m1; ++j) {
        line = (int)j / m1;
        column = j % m1;
        matrix1[line][column] += matrix2[line][column];
    }

    cout << "Resuled sum matrix is: " << endl;

    for (int k = 0; k < n2; ++k){
        for (int l = 0; l < m2; ++l)
            cout << matrix1[k][l] << " ";
        cout << endl;
    }

    for (int i = 0; i < numberOfThreads; ++i) {
        threads[i] = thread(product, i);
    }
    for (int i = 0; i < numberOfThreads; ++i) {
        threads[i].join();
    }

    remainingFrom = (numberOfThreads - 1) * ((int)(n1 * m2) / numberOfThreads) + ((int)(n1 * m2) / numberOfThreads);

    for (int j = remainingFrom; j < n1 * m2; ++j) {
        line = (int)j / m2;
        column = j % m2;
        result = 0;
        for (int k = 0; k < m1; ++k)
            result += matrix1copy[line][k] * matrix2[k][column];
        productResult[line][column] = result;
    }

    cout << "Resuled product matrix is: " << endl;

    for (int k = 0; k < n1; ++k) {
        for (int l = 0; l < m2; ++l)
            cout << productResult[k][l] << " ";
        cout << endl;
    }

    return 0;
}