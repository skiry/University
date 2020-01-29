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

#define BIG_NUMBERS 5
#define THREADS_NUMBER BIG_NUMBERS-1
using namespace std;

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

vector<vector<int>> numbers(BIG_NUMBERS);
vector<ProducerConsumerQueue<int>> queues(BIG_NUMBERS);
thread threads[THREADS_NUMBER];

void add(int id) {
    if (id) {
        int val;
        int toAdd;
        int pos = 0;
        int carry = 0;
        int currentDigit;
        int numberSize = numbers[id + 1].size();

        while (queues[id - 1].deque(val)) {
            if (pos < numberSize) {
                currentDigit = numbers[id + 1][pos];
            }
            else {
                currentDigit = 0;
            }
            toAdd = val + currentDigit + carry;
            carry = (int)toAdd / 10;
            toAdd %= 10;
            queues[id].enqueue(toAdd);
            ++pos;
        }
        while (pos < numberSize) {
            toAdd = numbers[id + 1][pos] + carry;
            carry = (int)toAdd / 10;
            toAdd %= 10;
            queues[id].enqueue(toAdd);
            ++pos;
        }
        if (carry) {
            queues[id].enqueue(carry);
        }
        queues[id].close();
    }
    else {
        int firstNumberSize = numbers[id].size();
        int secondNumberSize = numbers[id + 1].size();
        int toAdd, carry = 0, i;
        bool first = true;

        for (i = 0; i < min(firstNumberSize, secondNumberSize); ++i) {
            toAdd = numbers[id][i] + numbers[id + 1][i] + carry;
            carry = (int)toAdd / 10;
            toAdd %= 10;
            queues[id].enqueue(toAdd);
        }
        if (i == firstNumberSize) {
            first = false;
        }
        for (int i = min(firstNumberSize, secondNumberSize); i < max(firstNumberSize, secondNumberSize); ++i) {
            if (first) {
                toAdd = numbers[id][i];
            }
            else {
                toAdd = numbers[id + 1][i];
            }
            toAdd += carry;
            carry = (int)toAdd / 10;
            toAdd %= 10; 
            queues[id].enqueue(toAdd);
        }
        if (carry) {
            queues[id].enqueue(carry);
        }
        queues[id].close();
    }
}

int my_rand() {
    return rand() % 10;
}

int main() {
    for (int i = 0; i < numbers.size(); ++i) {
        vector<int> random(rand() % 1000 + 300);
        generate(random.begin(), random.end(), my_rand);
        numbers[i] = random;
    }

    int counter = 0;
    // numbers are printed from right to left, ie the first is the least significant
    
    for (auto x : numbers) {
        cout << "Number " << ++counter << ": ";
        for (int i = x.size() - 1; i >= 0; --i) {
            cout << x[i];
        }
        cout << endl;
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < THREADS_NUMBER; ++i) {
        threads[i] = thread(add, i);
    }

    for (int i = 0; i < THREADS_NUMBER; ++i) {
        threads[i].join();
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(end2 - start).count();

    cout << "Time taken: " << duration * 0.0000001;

    cout << "The result of the addition is: ";

    int digit;
    stack<int> result;

    while (queues[THREADS_NUMBER - 1].deque(digit)) {
        result.push(digit);
    }
    while (result.size()) {
        cout << result.top();
        result.pop();
    }

    return 0;
}