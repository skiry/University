#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <chrono>
#include <atomic>
#include <algorithm>
#include <functional>
#include <condition_variable>
#include <list>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define NUMBER_OF_THREADS 18
#define PRODUCT 0

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

int n1, m1, matrix1[MAX_HEIGHT][MAX_WIDTH];
int n2, m2, matrix2[MAX_HEIGHT][MAX_WIDTH];
int matrix1copy[MAX_HEIGHT][MAX_WIDTH];
int productResult[MAX_HEIGHT][MAX_WIDTH];
int numberOfThreads = NUMBER_OF_THREADS;

class ThreadPool {
public:
    explicit ThreadPool(size_t nrThreads)
        :m_end(false),
        m_liveThreads(nrThreads)
    {
        m_threads.reserve(nrThreads);
        for (size_t i = 0; i < nrThreads; ++i) {
            m_threads.emplace_back([this]() {this->run(); });
        }
    }

    ~ThreadPool() {
        close();
        for (std::thread& t : m_threads) {
            t.join();
        }
    }

    void close() {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_end = true;
        m_cond.notify_all();
        while (m_liveThreads > 0) {
            m_condEnd.wait(lck);
        }
    }

    void enqueue(std::function<void()> func) {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_queue.push_back(std::move(func));
        m_cond.notify_one();
    }

    //    template<typename Func, typename... Args>
    //    void enqueue(Func func, Args&&... args) {
    //        std::function<void()> f = [=](){func(args...);};
    //        enqueue(std::move(f));
    //    }
private:
    void run() {
        while (true) {
            std::function<void()> toExec;
            {
                std::unique_lock<std::mutex> lck(m_mutex);
                while (m_queue.empty() && !m_end) {
                    m_cond.wait(lck);
                }
                if (m_queue.empty()) {
                    --m_liveThreads;
                    if (0 == m_liveThreads) {
                        m_condEnd.notify_all();
                    }
                    return;
                }
                toExec = std::move(m_queue.front());
                m_queue.pop_front();
            }
            toExec();
        }
    }

    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::condition_variable m_condEnd;
    std::list<std::function<void()> > m_queue;
    bool m_end;
    size_t m_liveThreads;
    std::vector<std::thread> m_threads;
};

mutex m;
void sum(int threadNumber) {
    int from = threadNumber * ((int)(n1 * m1) / numberOfThreads);
    int to = from + ((int)(n1 * m1) / numberOfThreads) - 1;
    int line, column;
    for (int j = from; j <= to; ++j) {
        line = (int)j / m1;
        column = j % m1;
        m.lock();
        cout << threadNumber << " is on " << line << " " << column << " and have from and to:" << from<<" "<<to<< endl;
        m.unlock();
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
    // ///////////////////////////////////////////////////

    auto start = std::chrono::high_resolution_clock::now();
    if (PRODUCT) {
        ThreadPool pool(numberOfThreads);

        for (unsigned i = 0; i < numberOfThreads; ++i) {
            pool.enqueue([i]() {product(i); });
        }
        pool.close();

        /////////////////////////////////////////////////////////////
        int remainingFrom = (numberOfThreads - 1) * ((int)(n1 * m2) / numberOfThreads) + ((int)(n1 * m2) / numberOfThreads);
        int line, column, result;
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

    }
    else {
        ThreadPool pool(numberOfThreads);

        for (unsigned i = 0; i < numberOfThreads; ++i) {
            pool.enqueue([i]() {sum(i); });
        }
        pool.close();

        // //////////////////////////////////////////
        int remainingFrom = (numberOfThreads - 1) * ((int)(n1 * m1) / numberOfThreads) + ((int)(n1 * m1) / numberOfThreads);
        int line, column, result;

        for (int j = remainingFrom; j < n1 * m1; ++j) {
            line = (int)j / m1;
            column = j % m1;
            matrix1[line][column] += matrix2[line][column];
        }

        cout << "Resuled sum matrix is: " << endl;

        for (int k = 0; k < n2; ++k) {
            for (int l = 0; l < m2; ++l)
                cout << matrix1[k][l] << " ";
            cout << endl;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Time taken: " << duration * 0.0000001;

    return 0;
}