#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <set>
#include <unordered_map>
#include <Windows.h>
#include <chrono>
#include <algorithm>
#include <future>

#define THREADS_NUMBER 3
#define ELEMENTS_NUMBER 8
using namespace std;

int number_of_threads = min(THREADS_NUMBER, (int)ELEMENTS_NUMBER / 2);
vector<int> A(ELEMENTS_NUMBER);
vector<int> result(ELEMENTS_NUMBER);
thread threads[min(THREADS_NUMBER, (int)ELEMENTS_NUMBER / 2)];

class OneShotEvent {
public:
    void wait() {
        unique_lock<mutex> l(m);
        while (!isSignaled) {
            cv.wait(l);
        }
    }
    void signal() {
        unique_lock<mutex> l(m);
        isSignaled = true;
        cv.notify_all();
    }
private:
    bool isSignaled = false;
    condition_variable cv;
    mutex m;
};

vector<OneShotEvent*> events;
void first_step(int id) {
    int todo = (int) ELEMENTS_NUMBER / number_of_threads;
    int from = id * todo;
    for (int i = from + 1; i < from + todo; ++i) {
        result[i] += result[i - 1];
    }
}
mutex lala;
void second_step(int id) {
    // I can make computations only when last[prev] is computed, to send forward the result
    if (id != 1) {
        events[id]->wait();
    }
    int todo = (int)ELEMENTS_NUMBER / number_of_threads;
    int from = id * todo;
    int toAdd = result[from - 1];
    result[from + todo - 1] += toAdd;
    events[id + 1]->signal();
    for (int i = from; i < from + todo - 1; ++i) {
        result[i] += toAdd;
    }
}

int my_rand() {
    return rand() % 39;
}

int main() {
    generate(A.begin(), A.end(), my_rand);

    cout << "A is: ";
    for (int i = 0; i < A.size(); ++i) {
        cout << A[i] << " ";
        result[i] = A[i];
    }
    cout << endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < number_of_threads; ++i) {
        threads[i] = thread(first_step, i);
    }

    for (int i = 0; i < number_of_threads; ++i) {
        threads[i].join();
    }

    for (int i = ((int)ELEMENTS_NUMBER / number_of_threads) * number_of_threads + 1; i < A.size(); ++i) {
        result[i] += result[i - 1];
    }

    cout << "After the first step, the result is: ";
    for (int i = 0; i < A.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    // Declare an additional event to avoid different edge cases in the second step function
    for (int i = 0; i <= number_of_threads; ++i) {
        OneShotEvent* e = new OneShotEvent();
        events.push_back(e);
    }
    // Start from the 'second' position because the first bucket is already computed
    for (int i = 2; i < number_of_threads; ++i) {
        threads[i] = thread(second_step, i);
    }
    threads[1] = thread(second_step, 1);
    for (int i = 1; i < number_of_threads; ++i) {
        threads[i].join();
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(end2 - start).count();

    cout << "Time taken: " << duration * 0.0000001;
    
    int toAdd = result[((int)ELEMENTS_NUMBER / number_of_threads) * number_of_threads - 1];
    for (int i = ((int)ELEMENTS_NUMBER / number_of_threads) * number_of_threads; i < A.size(); ++i) {
        result[i] += toAdd;
    }
    cout << "\nAfter the second step, the result is: ";
    for (int i = 0; i < A.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    

    return 0;
}