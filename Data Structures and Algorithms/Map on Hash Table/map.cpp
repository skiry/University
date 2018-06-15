#include "map.h"
#include <iostream>
#include <exception>

Map::Map(int _len)
{
    this -> len = _len;
    elems = (Pair*)malloc(len * sizeof(Pair));

    for (int i = 0; i < len; ++i) {
        this -> elems[i].key = -1;
    }

    std::cout << "Constructed a map with " << len << " elements!\n";
}

int Map::h1(int x)
{
    return x % len;
}

int Map::h2(int x)
{
    return 7 - (x % 7);
}

void Map::add(int k, int v)
{
    if ( nr == len ) {
        throw ("The map is full\n");    //@resize and rehash
    }

    int pos = h1(k);
    int i = 1;

    while ( elems[pos].key != -1 && elems[pos].key != -2 ) { //vezi exact conditia aici si schimba pseudocodul

        if ( elems[pos].key == k ) {
            throw ("The key is already existing\n");
        }

        pos = ( h1(k) + h2(k) * i++ ) % len;
    }

    this -> nr++;
    this -> elems[pos].key = k;
    this -> elems[pos].value = v;
}

int Map::search(int k)
{
    int pos = h1(k);
    int i = 1;

    while ( elems[pos].key != k ) {

        if ( elems[pos].key == -1 || i == len ) {
            //if the element is not occupied or we looked everywhere
            return -1;
        }

        pos = ( h1(k) + h2(k) * i++ ) % len;


    }

    return elems[pos].value;
}

int Map::remove(int k)
{
    if ( nr == 0 ) {
        return -1;
    }

    int pos = h1(k);
    int i = 1;

    while ( elems[pos].key != k ) {

        if ( elems[pos].key == -1 || i == len ) {
            //if the element is not occupied <=> i've seen all the possibilities until that point
            // or we looked everywhere
            return -1;
        }

        pos = ( h1(k) + h2(k) * i++ ) % len;
    }

    int value = elems[pos].value;
    this -> nr --;
    this -> elems[pos].key = -2;
    this -> elems[pos].value = -2;
    return value;
}

int Map::size()
{
    return this -> nr;
}

Iterator Map::iterator()
{
    return Iterator{ *this };
}

Map::~Map()
{
    free(elems);
    std::cout << "Destructed the map and freed the memory!\n";
}

Iterator::Iterator(Map& _m) : m{ _m }
{
    this -> it = m.len - 1;
    std::cout << "Constructed the iterator. Map has " << m.size() << " elements." << '\n';
}

Iterator::~Iterator()
{
    std::cout << "Destructed the iterator\n";
}

bool Iterator::valid()
{
    return this -> it > 0;
    return this -> it < m.len;
}

int Iterator::next()
{
    //return ++this -> it;
    --this->it;

    while ( valid() )
        if ( this->getCurrent().key == -1 || this -> getCurrent().key == -2 ) {
            --this->it;

        } else {
            break;
        }

    return it;

    ++this->it;

    while ( valid() )
        if ( this->getCurrent().key == -1 || this -> getCurrent().key == -2 ) {
            ++this->it;

        } else {
            break;
        }

    return it;
}

Pair Iterator::getCurrent()
{
    return m.elems[this -> it];
}
