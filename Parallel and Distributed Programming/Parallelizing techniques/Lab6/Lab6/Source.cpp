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

#define VERSION 4
#define THREADS_NUMBER 80
#define BIG_NUMBERS 1

using namespace std;

vector<int> A(700), B(700);
vector<int> parralelizedResult;
mutex m;
int v;
vector<int> classicSequential(vector<int> A, vector<int> B) {
    vector<int> result(A.size() + B.size() - 1);
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B.size(); ++j) {
            result[i + j] += A[i] * B[j];
        }
    }

    return result;
}

void multiply(int id) {
    if (id > A.size() * B.size() - 1) {
        return;
    }
    int todo = (int) A.size() * B.size() / min(THREADS_NUMBER, A.size() * B.size());
    int toskip = id * todo;
    int startA = (int)toskip / B.size();
    toskip %= B.size();
    int startB = toskip;
    int counter = 0;
    for (int i = startA; i < A.size(); ++i) {
        for (int j = startB; j < B.size(); ++j) {
            m.lock();
            parralelizedResult[i + j] += A[i] * B[j];
            m.unlock();
            counter += 1;
            if (counter == todo) return;
        }
        startB = 0;
    }
}

vector<int> shift(vector<int> A, int offset) {
    vector<int> result;
    for (int i = 0; i < offset; i++) {
        result.push_back(0);
    }
    for (int i = 0; i < A.size(); i++) {
        result.push_back(A[i]);
    }
    return result;
}

void addRemainingCoefficients(vector<int> p1, vector<int> p2, int minDegree, int maxDegree, vector<int>& result) {
    if (minDegree != maxDegree) {
        if (maxDegree == p1.size() - 1) {
            for (int i = minDegree + 1; i <= maxDegree; i++) {
                result[i] = p1[i];
            }
        }
        else {
            for (int i = minDegree + 1; i <= maxDegree; i++) {
                result[i] = p2[i];
            }
        }
    }
}

vector<int> add(vector<int> A, vector<int> B) {
    int minDegree = min(A.size(), B.size()) - 1;
    int maxDegree = max(A.size(), B.size()) - 1;
    vector<int> result(maxDegree + 1);

    //Add the 2 polynomials
    for (int i = 0; i <= minDegree; i++) {
        result[i] = A[i] + B[i];
    }

    addRemainingCoefficients(A, B, minDegree, maxDegree, result);

    return result;
}

vector<int> subtract(vector<int> A, vector<int> B) {
    int minDegree = min(A.size(), B.size()) - 1;
    int maxDegree = max(A.size(), B.size()) - 1;
    vector<int> result(maxDegree + 1);

    //Add the 2 polynomials
    for (int i = 0; i <= minDegree; i++) {
        result[i] = A[i] - B[i];
    }

    addRemainingCoefficients(A, B, minDegree, maxDegree, result);

    //remove coefficients starting from biggest power if coefficient is 0

    int i = result.size() - 1;
    while (result[i] == 0 && i > 0) {
        result.erase(result.begin() + i);
        i--;
    }
    return result;
}

vector<int> karatsubaSequential(vector<int> A, vector<int> B) {
    int degreeA = A.size() - 1;
    int degreeB = B.size() - 1;
    if (degreeA < 2 || degreeB < 2) {
        return classicSequential(A, B);
    }

    int len = (int) min(degreeA, degreeB) / 2;
    
    vector<int> lowP1(A.begin(), A.begin() + len);
    vector<int> highP1(A.begin() + len, A.end());
    vector<int> lowP2(B.begin(), B.begin() + len);
    vector<int> highP2(B.begin() + len, B.end());
    
    vector<int> z1 = karatsubaSequential(lowP1, lowP2);
    vector<int> z2 = karatsubaSequential(add(lowP1, highP1), add(lowP2, highP2));
    vector<int> z3 = karatsubaSequential(highP1, highP2);

    //calculate the final result
    vector<int> r1 = shift(z3, 2 * len);
    vector<int> r2 = shift(subtract(subtract(z2, z3), z1), len);
    vector<int> result = add(add(r1, r2), z1);
    
    return result;
}

vector<int> karatsubaParallelized(vector<int> A, vector<int> B) {
    
    int degreeA = A.size() - 1;
    int degreeB = B.size() - 1;
    if (degreeA < 2 || degreeB < 2) {
        return karatsubaSequential(A, B);
    }

    int len = (int)min(degreeA, degreeB) / 2;

    vector<int> lowP1(A.begin(), A.begin() + len);
    vector<int> highP1(A.begin() + len, A.end());
    vector<int> lowP2(B.begin(), B.begin() + len);
    vector<int> highP2(B.begin() + len, B.end());

    auto rez1 = async(karatsubaParallelized, lowP1, lowP2);
    auto rez2 = async(karatsubaParallelized, add(lowP1, highP1), add(lowP2, highP2));
    auto rez3 = async(karatsubaParallelized, highP1, highP2);

    vector<int> z1 = rez1.get();
    vector<int> z2 = rez2.get();
    vector<int> z3 = rez3.get();

    //calculate the final result
    vector<int> r1 = shift(z3, 2 * len);
    vector<int> r2 = shift(subtract(subtract(z2, z3), z1), len);
    vector<int> result = add(add(r1, r2), z1);

    return result;
}
int my_rand() {
    return rand() % 39;
}

int my_rand_digits() {
    return rand() % 10;
}

int main() {
    if (BIG_NUMBERS) {
        generate(A.begin(), A.end(), my_rand_digits);
        generate(B.begin(), B.end(), my_rand_digits); 
        cout << "A is: ";
        for (int x : A) {
            cout << x;
        }
        cout << "\nB is: ";
        for (int x : B) {
            cout << x;
        }
        cout << endl;
    }
    else {
        generate(A.begin(), A.end(), my_rand);
        generate(B.begin(), B.end(), my_rand);
        cout << "A is: ";
        for (int x : A) {
            cout << x << " ";
        }
        cout << "\nB is: ";
        for (int x : B) {
            cout << x << " ";
        }
        cout << endl;
    }

    
    if (VERSION == 1) {
        auto start = std::chrono::high_resolution_clock::now();
        vector<int> result = classicSequential(A, B);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (BIG_NUMBERS) {
            int carry = 0;
            for (int i = result.size() - 1; i >= 0; --i) {
                result[i] += carry;
                carry = (int) result[i] / 10;
                result[i] %= 10;
            }
            if (carry) {
                cout << carry;
            }
            for (auto x : result) {
                cout << x;
            }
        }
        else {
            for (auto x : result) {
                cout << x << " ";
            }
        }
        cout << "\nTime taken for n2 sequential: " << duration * 0.0000001;
    }
    else if (VERSION == 2) {
        auto start = std::chrono::high_resolution_clock::now();
        vector<int> result = karatsubaSequential(A, B);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (BIG_NUMBERS) {
            int carry = 0;
            for (int i = result.size() - 1; i >= 0; --i) {
                result[i] += carry;
                carry = (int)result[i] / 10;
                result[i] %= 10;
            }
            if (carry) {
                cout << carry;
            }
            for (auto x : result) {
                cout << x;
            }
        }
        else {
            for (auto x : result) {
                cout << x << " ";
            }
        }
        cout << "\nTime taken for karatsuba sequential: " << duration * 0.0000001;
    }
    else if (VERSION == 3) {
        auto start = std::chrono::high_resolution_clock::now();
        thread threads[THREADS_NUMBER];
        for (int i = 0; i < A.size() + B.size() - 1; ++i) {
            parralelizedResult.push_back(0);
        }
        for (int i = 0; i < THREADS_NUMBER; ++i) {
            threads[i] = thread(multiply, i);
        }

        for (int i = 0; i < THREADS_NUMBER; ++i) {
            threads[i].join();
        }
        int todo = (int)A.size() * B.size() / min(THREADS_NUMBER, A.size() * B.size());
        int toskip = THREADS_NUMBER * todo;
        int startA = (int)toskip / B.size();
        toskip %= B.size();
        int startB = toskip;
        for (int i = startA; i < A.size(); ++i) {
            for (int j = startB; j < B.size(); ++j) {
                parralelizedResult[i + j] += A[i] * B[j];
            }
            startB = 0;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (BIG_NUMBERS) {
            int carry = 0;
            for (int i = parralelizedResult.size() - 1; i >= 0; --i) {
                parralelizedResult[i] += carry;
                carry = (int)parralelizedResult[i] / 10;
                parralelizedResult[i] %= 10;
            }
            if (carry) {
                cout << carry;
            }
            for (auto x : parralelizedResult) {
                cout << x;
            }
        }
        else {
            for (auto x : parralelizedResult) {
                cout << x << " ";
            }
        }
        cout << "\nTime taken for n2 parallelized " << duration * 0.0000001;
    }
    else if (VERSION == 4) {
        auto start = std::chrono::high_resolution_clock::now();
        vector<int> result = karatsubaParallelized(A, B);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (BIG_NUMBERS) {
            int carry = 0;
            for (int i = result.size() - 1; i >= 0; --i) {
                result[i] += carry;
                carry = (int)result[i] / 10;
                result[i] %= 10;
            }
            if (carry) {
                cout << carry;
            }
            for (auto x : result) {
                cout << x;
            }
        }
        else {
            for (auto x : result) {
                cout << x << " ";
            }
        }
        cout << "\nTime taken for karatsuba parallelized: " << duration * 0.0000001;
    }

    return 0;
}