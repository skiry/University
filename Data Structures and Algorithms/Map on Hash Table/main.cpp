#include <iostream>
#include "map.h"

using namespace std;

void run(Map &m, int &minimum, Pair &result, int M);

int main()
{
    int N, M;
    int number, cost;
    cout << "Give n: ";
    cin >> N;
    cout << "Give m: ";
    cin >> M;

    Map m{N};

    for ( int i = 0; i < N; ++i ) {
        cout << "Number: ";
        cin >> number;
        cout << "Cost: ";
        cin >> cost;

        try {
            if ( number < 0 ) {
                cout << number << " is not greater than 0" << '\n';

            } else {
                m.add(number, cost);
            }

        } catch (...) {
            --i;
            std::cout << "The key is already existing\n";
        }
    }

    int minimum = 999999;
    Pair result;
    run(m, minimum, result, M);

    if ( minimum != 999999 ) {
        cout << M << " can be made of " << result.key << " and " << M - result.key << " with the cost " << minimum << '\n';

    } else {
        cout << "There are no 2 numbers that sum up to " << M << '\n';
    }

    return 0;
}

void run(Map &m, int& minimum, Pair& result, int M)
{
    int value;
    int maybe;
    Iterator it = m.iterator();

    while ( it.valid() ) {
        value = -1;

        if ( M > it.getCurrent().key ) {
            value = m.search(M - it.getCurrent().key);
        }

        if ( value != -1 ) {
            maybe = it.getCurrent().value + value;

            if ( maybe < minimum && it.getCurrent().value != value ) {
                minimum = maybe;
                result = it.getCurrent();
            }
        }

        it.next();
    }
}
