#include <iostream>
#include "tutorial.cpp"
#include "dynamicarray.cpp"

using namespace std;
template <typename john>
john multiply(john a, john b){
    return a * b;
}
int main()
{
    cout << multiply <int> (5,3) << '\n';
    Duration d = Duration(3,22);
    Tutorial tut = Tutorial("Easy C++", "Johnny", d, 1500, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    cout << tut.getTime().getMinutes() << '\n' << tut.getLink() << '\n';
    Tutorial tut2 = tut;
    cout << tut . getLikes() << '\n' << tut2 . getPresenter() << '\n';

    DynamicArray<Tutorial> d1;
    d1.add(tut);
    cout << d1[0].getTitle();
    return 0;
}
