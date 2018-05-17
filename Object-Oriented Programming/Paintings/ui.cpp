#include "ui.h"

void ui::run(){
    int a = 1, opt;
    while(a){
        std::cout << "0.Exit" << '\n';
        std::cout << "1. Add" << '\n';
        std::cout << "2. Move" << '\n';
        std::cout << "3. Show" << '\n';
        std::cout << "4. Undo" << '\n';
        std::cin >> opt;
        if( opt == 0 ) a = 0;
        else if( opt == 1 ) add();
        else if( opt == 2 ) move();
        else if( opt == 3 ) show();
        else if( opt == 4 ) undo();
    }
}

void ui::add(){
    std::string t, a;
    int y;
    std::cout << "Title: ";
    std::cin >> t;
    std::cout << "Artist: ";
    std::cin >> a;
    std::cout << "Year: ";
    std::cin >> y;
    c.addPainting( painting{t, a, y} );
}

void ui::move(){
    std::string t, a;
    int y;
    std::cout << "Title: ";
    std::cin >> t;
    std::cout << "Artist: ";
    std::cin >> a;
    std::cout << "Year: ";
    std::cin >> y;
    c.movePainting( painting{t, a, y} );
}

void ui::show(){
    std::cout<<"Gallery:" << '\n';
    for( auto& i : c.getG() )
        std::cout << i.getTitle() << " " << i.getArtist() << " " << i.getYear() << '\n';

    std::cout<<"Special Storage:" << '\n';
    for( auto& i : c.getS() )
        std::cout << i.getTitle() << " " << i.getArtist() << " " << i.getYear() << '\n';

}

void ui::undo(){
    c.doUndo();
}
