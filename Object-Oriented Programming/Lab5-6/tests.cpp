#include <iostream>
#include "tutorial.cpp"
#include "dynamicarray.cpp"
#include "repository.cpp"
#include "controller.cpp"
#include "assert.h"

using namespace std;

void testController(){

    Duration d = Duration(3,22);
    Duration d1 = Duration(5,59);
    Duration d2 = Duration(1,4);
    Tutorial tut = Tutorial("Easy C++", "Johnny", d, 1500, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    Tutorial tut2 = Tutorial("Easy C--", "Johny", d1, 10, "www.google.com");
    Tutorial tut3 = Tutorial("Easy C", "Johnnie", d2, 150, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    Tutorial tut4 = Tutorial("Easy Pyhton", "John", d, 15, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    Tutorial tut5 = Tutorial("Easy Java", "Ionut", d2, 500, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    Tutorial tut6 = Tutorial("Easy Info", "Ionutz", d1, 100, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    Tutorial tut7 = Tutorial("Easy OOP", "Ion", d, 1000, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    Tutorial tut8 = Tutorial("Easy Everything", "Mc John", d2, 1900, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");

    Repository myRepo = Repository();
    Controller ctrl = Controller(myRepo);
    ctrl.add(tut);
    assert( ctrl.add(tut) == 1 );
    ctrl.add(tut2);
    assert( ctrl.add(tut2) == 1 );
    ctrl.add(tut3);
    assert( ctrl.add(tut3) == 1 );
    ctrl.add(tut4);
    assert( ctrl.add(tut4) == 1 );
    ctrl.add(tut5);
    assert( ctrl.add(tut5) == 1 );
    ctrl.add(tut6);
    assert( ctrl.add(tut6) == 1 );
    ctrl.add(tut7);
    assert( ctrl.add(tut7) == 1 );
    ctrl.add(tut8);
    assert( ctrl.add(tut8) == 1 );

    assert( ctrl.len() == 8);
    assert( ctrl.rm("Error") == 0 );
    assert( ctrl.len() == 8);
    assert( ctrl.rm("Easy C") == 1 );
    assert( ctrl.len() == 7);

    assert( ctrl.upd("Easy C", tut3) == 0 );
    assert( ctrl.upd("Error", tut3) == 0 );
    assert( ctrl.upd("Easy C++", tut2) == 0 );
    assert( ctrl.upd("Easy C++", tut3) == 1 );

    assert( ctrl.len() == 7);

    assert( ctrl.addToPL(tut) == true );
    assert( ctrl.addToPL(tut) == false );

    ctrl.like("Easy C++");

    assert( ctrl.rmW("Error") == 0 );
    assert( ctrl.rmW("Easy C++") == 1 );

    assert( tut2.getLikes() == 10 );
    ++tut3;
    assert( tut2.getLikes() == 10 );
    ++tut2;
    assert( tut2.getLikes() == 11 );

    assert( tut2.getPresenter() == "Johny" );
    //assert( tut2.getTime().getMinutes() == d1.getMinutes() );
    //assert( tut2.getTime().getSeconds() == d1.getSeconds() );

}

void testDynamicArray(){
            DynamicArray<int> v;

            for (int i = 1; i <= 11; ++i) {
                v.add(i);
            }

            for (int i = 0; i < v.len(); ++i) {
                assert( v[i] == i + 1 );
            }

            for (int i = 0; i < 8; ++i) {
                v - v[i];
            }
            for (int i = 0; i < v.len(); ++i) {
                assert( v[i] == 11 - i );
            }

            DynamicArray<int> V2;

            for (int i = 1; i <= 3; ++i) {
                V2.add(i);
            }


            DynamicArray<int> V3{100};

            V3 = v;
            //assert(v == V3);
            DynamicArray<int> V4 = V3;
            //assert(V4 == V3);

            DynamicArray<int> D;
            int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            int in = 0;

            for (int i = 1; i <= 9; ++i) {
                D.add(i);
            }

            for (auto it = 0; it < D.len(); ++it) {
                //std::cout << it << " " << a[in] << "\n";
                assert( D[it] == a[in]);
                ++in;
            }

            in = 0;

            for (auto it = 0; it < D.len(); ++it) {
                //std::cout << it << " " << a[in] << "\n";
                //std::cout << it << " ";
                assert( D[it] == a[in]);
                ++in;
            }

            D - D[1];

            for (auto it = 0; it < D.len(); ++it) {
                //std::cout << D[it] << " ";
            }

            assert(D[1] == 9);
}

int main()
{

    testController();
    testDynamicArray();

    std::cout << "\n All the tests ran succesfully ! \n ";
    return 0;
}

