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

#define NUM_PRODUCTS 1000
#define NOT_ENOUGH_QUANTITY -1
#define MAX_BUYERS 20

using namespace std;
ifstream f("products.txt");
ofstream g("bill.txt");

int cwt = 0;
mutex cwtMutex;

struct product {
    int price;
    int quantity;
    string name;
    mutex mtx;
} products[NUM_PRODUCTS];

vector<string> productNames;
unordered_map<string, int> nameToId;

struct bill {
    vector<pair<string, int>> items;
    int totalPrice = 0;
};

struct inventory {
    int money;
    vector<bill*> bills;
    mutex mtx;
} supermarket;
mutex globalSum;
mutex billsList;
string line;

int numberOfProducts;

int readFile() {
    int index = 0;
    while (getline(f, line)) {
        int it = 0, prev = 0, counter = 0;
        while (line[it]) {
            if (line[it] == ',') {
                if (!counter) {
                    products[index].name = line.substr(0, it);
                    productNames.push_back(line.substr(0, it));
                    nameToId[line.substr(0, it)] = index;
                    ++counter;
                    prev = it + 1;
                }
                else if (counter == 1) {
                    string price = line.substr(prev, it - prev);
                    products[index].price = stoi(price);
                    ++counter;
                    prev = it + 1;
                }
            }
            ++it;
        }
        string quantity = line.substr(prev, it - prev);
        products[index++].quantity = stoi(quantity);
    }

    return index;
}

void inventoryCheck() {
    supermarket.mtx.lock();
    while (cwt) {
        Sleep((rand() % 10) / 100);
    }
    cout << "Supermarket's products: " << endl;
    for (int i = 0; i < numberOfProducts; ++i)
    {
        if (!products[i].quantity)
        {
            cout << "We do not have " << products[i].name << " that had the price " << products[i].price << endl;
        }
        else
        {
            cout << "We have " << products[i].quantity << " " << products[i].name << "s that each have the price of " << products[i].price << endl;
        }
    }

    int billsSum = 0;

    cout << "Supermarket's money: " << supermarket.money << endl;
    cout << "Bills: " << endl;
    for (auto currBill : supermarket.bills)
    {
        bool buyed = false;
        for (auto item : currBill->items)
        {
            buyed = true;
            cout << "Sold " << item.second << " pieces of the product " << item.first << endl;
        }
        if (buyed) {
            cout << "Total sum collected: " << currBill->totalPrice << endl;
        }
        else {
            cout << "Bought nothing on the current printed bill." << endl;
        }
        billsSum += currBill->totalPrice;
    }
    cout << "All bills added by value: " << billsSum << " and we actually have: " << supermarket.money << endl;
    cout << endl;
    supermarket.mtx.unlock();
}

int saleOperation(string product, int quantity, bill* current_bill) {
    while (!supermarket.mtx.try_lock()) {
        Sleep((rand() % 10) / 100);
    }
    cwtMutex.lock();
    cwt++;
    cwtMutex.unlock();
    supermarket.mtx.unlock();
    int id = nameToId[product];
    products[id].mtx.lock();
    if (products[id].quantity < quantity) {
        cwtMutex.lock();
        cwt--;
        cwtMutex.unlock();
        products[id].mtx.unlock();
        return NOT_ENOUGH_QUANTITY;
    }
    int value = quantity * products[id].price;
    products[id].quantity -= quantity;
    globalSum.lock();
    supermarket.money += value;
    globalSum.unlock();
    current_bill->totalPrice += value;
    current_bill->items.push_back(make_pair(product, quantity));
    cwtMutex.lock();
    cwt--;
    cwtMutex.unlock();
    products[id].mtx.unlock();
    return 1;
}

void makeSales(int buyerIndex, int randValue) {
    srand(time(0) + buyerIndex * randValue);
    int numberOfSales =  rand() % 10 + 1;
    for (int i = 0; i < numberOfSales; ++i) {
        if (rand() % 5 == 3) {
            inventoryCheck();
        }
        int numberOfProductsCurrentSell = rand() % numberOfProducts + 1;
        set<int> productIndices;
        while (productIndices.size() != numberOfProductsCurrentSell) {
            productIndices.insert(rand() % numberOfProducts);
        }
        bill* currentBill = new bill();
        billsList.lock();
        supermarket.bills.push_back(currentBill);
        billsList.unlock();
        for (int productIndex : productIndices) {
            int q = products[productIndex].quantity;
            if (!q) q = 1;
            saleOperation(productNames[productIndex], rand() % q + 1, currentBill);
        }
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    srand(time(0));
    numberOfProducts = readFile();
    for (int i = 0; i < numberOfProducts; ++i) {
        cout << "We have " << products[i].quantity << " " << products[i].name << "s that each costs $" << products[i].price << endl;
    }

    supermarket.money = 0;

    thread buyers[MAX_BUYERS];
    int numberOfBuyers = rand() % MAX_BUYERS + 1;

    for (int i = 0; i < numberOfBuyers; ++i) {
        buyers[i] = thread(makeSales, i, rand());
    }

    for (int i = 0; i < numberOfBuyers; ++i) {
        buyers[i].join();
    }

    inventoryCheck();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Time taken: " << duration * 0.0000001;

    return 0;
}
