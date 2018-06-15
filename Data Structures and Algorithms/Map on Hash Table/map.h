#ifndef MAP_H
#define MAP_H

struct Pair {
    int key;
    int value;
};

class Iterator;

class Map
{
    friend class Iterator;
private:
    Pair* elems;
    int len = 1;
    int nr = 0;
    int h1(int x);
    int h2(int x);
public:
    Map() {}
    Map(int _len);
    void add(int k, int v);
    int remove(int k);
    int search(int k);
    int size();
    Iterator iterator();
    ~Map();
};

class Iterator
{
private:
    int it;
    Map& m;
public:
    Iterator(Map& _m);
    bool valid();
    int next();
    Pair getCurrent();
    ~Iterator();

};
#endif // MAP_H
