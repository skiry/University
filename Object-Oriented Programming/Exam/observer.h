#pragma once
#include <vector>
#include <bits/stdc++.h>
class Observer
{
public:
    virtual void update() = 0;
    virtual ~Observer() {}
};

class Observable
{
private:
    std::vector<Observer*> observers;

public:
    virtual ~Observable() {}

    void addObserver(Observer* o)
    {
        this->observers.push_back(o);
    }

    void removeObserver(Observer* o)
    {
        this->observers.erase(std::find(this->observers.begin(), this->observers.end(), o));
    }

    void notify()
    {
        for (auto o : this->observers) {
            o->update();
        }
    }
};
