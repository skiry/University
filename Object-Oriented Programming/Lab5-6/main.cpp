#include <iostream>
#include "tutorial.cpp"
#include "tutorialvalidator.cpp"
#include "dynamicarray.cpp"
#include "repository.cpp"
#include "controller.cpp"
#include "ui.cpp"

using namespace std;
template <typename john>
john multiply(john a, john b){
    return a * b;
}
int main()
{/*
    cout << multiply <int> (5,3) << '\n';
    Duration d = Duration(3,22);
    Tutorial tut = Tutorial("Easy C++", "Johnny", d, 1500, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    cout << tut.getTime().getMinutes() << '\n' << tut.getLink() << '\n';
    Tutorial tut2 = Tutorial("Easy C--", "Johnny", d, 1500, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    cout << tut . getLikes() << '\n' << tut2 . getPresenter() << '\n';
    if(tut == tut2) cout<<"da";
    else cout<<"nu";
    DynamicArray<Tutorial> d1;
    d1.add(tut);*/
    //
   // cout<<'\n' <<"nesters"<< d1.len() << '\n';
   // d1-tut;cd
   // cout<<'\n'<<" sters:" << d1.len() << '\n';
    //SEE THIS ERR  d1.add(tut2);
   // cout << d1[0].getTitle();
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
    //myRepo.addTut(tut);
    //cout << myRepo.len()<<'\n';
    //myRepo.rmTut("Easy C++");
    //cout << myRepo.len();

    /*Repository a = myRepo.getRepo();
    cout << '\n' << a[0].getTitle()<<'\n';
    a.updTut("Easy C++", tut2);
    cout << '\n' << a[0].getTitle()<<'\n';*/
    //-------------------------------------
    Controller ctrl = Controller(myRepo);
    //ctrl.add(tut);
    //ctrl.add(tut2);
    //ctrl.add(tut3);
    //ctrl.add(tut4);

    //ctrl.add(tut);
    //cout << ctrl[0].getTitle()<<'\n';
    UI ui = UI(ctrl);
    ui.start();
    return 0;
}
