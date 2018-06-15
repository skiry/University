#include "map.h"
#include "assert.h"
#include "string.h"
#include <iostream>

void run(Map &m, int& minimum, Pair& result, int M);
void testMap()
{
    Map m{15};
    assert(m.h1(15) == 0);
    assert(m.h1(19) == 4);
    assert(m.h2(15) == 6);
    assert(m.h2(19) == 2);
    m.add(2, 3);
    m.add(3, 2);
    m.add(18, 4);
    m.add(33, 4);

    try {
        m.add(2, 3);

    } catch (...) {
        std::cout << "The key is already existing\n";
    }

    assert(m.search(2) == 3);
    assert(m.search(4) == -1);
    assert(m.search(3) == 2);

    assert(m.nr == 4);
    assert(m.remove(2) == 3);

    assert(m.nr == 3);
    assert(m.remove(4) == -1);
    assert(m.nr == 3);

    m.add(2, 5);

    assert(m.nr == 4);
    assert(m.size() == 4);
    assert(m.remove(2) == 5);
    assert(m.size() == 3);
    assert(m.nr == 3);

    Iterator it = m.iterator();
    assert(it.getCurrent().key == -1);

    it.next();
    assert(it.valid() == true);
    assert(it.getCurrent().key == -1);

    it.next();
    it.next();
    assert(it.valid() == true);
    assert(it.getCurrent().key == 3);
}

void testProgram()
{
    Map m{5};
    m.add(9, 3);
    m.add(2, 4);

    try {
        m.add(2, 3);

    } catch (...) {
        std::cout << "The key is already existing\n";
    }

    m.add(1, 5);
    m.add(4, 9);

    try {
        m.add(4, 9);

    } catch (...) {
        std::cout << "The key is already existing\n";
    }

    m.add(5, 1);

    try {
        m.add(100, 3);

    } catch (...) {
        std::cout << "The map is full\n";
    }

    int minimum = 99999;
    Pair result;

    run(m, minimum, result, 100);
    assert( minimum == 99999 );

    run(m, minimum, result, 6);
    assert( minimum == 6 );

    minimum = 99999;
    run(m, minimum, result, 9);
    assert( minimum == 10 );

    minimum = 99999;
    run(m, minimum, result, 5);
    assert( minimum == 14 );
}

int main()
{
    testMap();
    testProgram();

    return 0;
}

void run(Map &m, int& minimum, Pair& result, int M)
{
    int value;
    int maybe;
    Iterator it = m.iterator();

    while ( it.valid() ) {
        value = m.search(M - it.getCurrent().key);

        if ( value != -1 ) {
            maybe = it.getCurrent().value + value;

            if ( maybe < minimum ) {
                minimum = maybe;
                result = it.getCurrent();
            }
        }

        it.next();
    }
}
