#include "ui.h"

void ui::run(){
    int a = 1, opt;
    while(a){
        std::cout << "0. Exit" << '\n';
        std::cout << "1. Add" << '\n';
        std::cout << "2. Print" << '\n';
        std::cout << "3. Am i ill?" << '\n';
        std::cout << "4. Save" << '\n';
        std::cin >> opt;
        if( opt == 0 ) a = 0;
        else if( opt == 1 ) addMA();
        else if( opt == 2 ) print();
        else if( opt == 3 ) ill();
        else if( opt == 4 ) w();
    }
}
void ui::addMA(){
    std::string type, date;
    double v;
    int s, d;
    //std::cin.ignore();
    std::cout<<"Type:";
    std::cin >> type;
    std::cout<<"\nDate:";
    std::cin >> date;
    if( type == "BMI" ){
        std::cout<<"\nValue:";
        std::cin >> v;
        c.addMA( std::make_shared<BMI> (date, v) );
    }
    else if( type == "BP" ){
        std::cout<<"\nsys, dys:";
        std::cin >> s >> d;
        c.addMA( std::make_shared<BP> (date, s, d) );
    }

}

void ui::print(){
    for( auto &i : c.get() )
        std::cout << i->toString() << '\n';
}

void ui::ill(){
    int month;
    std::cout << "Month: ";
    std::cin >> month;
    std::cout << c.ill(month);
}
void ui::w(){
    int d1, d2;
    std::cin >> d1 >> d2;
    c.wr(d1,d2);
}

