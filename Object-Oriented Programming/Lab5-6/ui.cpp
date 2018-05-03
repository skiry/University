#include "ui.h"
#include "comparator.h"
#include <string.h>
#include <bits/stdc++.h>
#include "tutorialvalidator.h"

using namespace std;

void UI::start() {

    int p, ok = 1, opt;
    testComparator();
    cout << "1. Administrator";
    cout << "\n2. User Mode";
    cin >> p;

    if( p == 1){
        ui.readR();
        while(ok) {
            printMenu();
            cin >> opt;
            if(opt == 5) ok = 0;
            else if(opt == 4) printRepo();
            else if(opt == 3) update();
            else if(opt == 2) deleteA();
            else if(opt == 1) addA();
        }
    }
    else if( p == 2){
        ui.readP();
        while(ok){
            printWmenu();
            cin >> opt;
            if(opt == 5) ok = 0;
            else if(opt == 4) printWlist();
            else if(opt == 2) delTut();
            else if(opt == 1) showTuts();
            else if(opt == 3) saveTuts();

        }
    }
}

void UI::update(){
    std::string toReplace, tt, pr, lk;
    int min, sec;
    Duration d;
    cout << "\nTitle to replace: ";
    getline(cin, toReplace);
    getline(cin, toReplace);
    cout << "\nNew Title: ";
    getline(cin, tt);
    cout << "\nNew Presenter name: ";
    getline(cin, pr);
    cout << "\nNew Duration(minutes): ";
    cin >> min;
    cout << "\nNew Duration(seconds): ";
    cin >> sec;
    cout << "\nNew Link: ";
    getline(cin, lk);
    getline(cin, lk);
    d = Duration(min, sec);
    Tutorial tut = Tutorial(tt, pr, d, 0, lk);
    try{
        if(this -> ui.upd(toReplace, tut) == 0) cout << "\nTutorial not found";
        else {
            cout << "\nOK!";
            ui.saveR();
        }
    }
    catch(TutorialException& exc){
        std::cout << exc.what();
    }
}

void UI::addA(){
    std::string tt, pr, lk;
    int min, sec;
    Duration d;
    cout << "\nTitle: ";
    getline(cin, tt);
    getline(cin, tt);
    cout << "\nPresenter name: ";
    getline(cin, pr);
    cout << "\nDuration(minutes): ";
    cin >> min;
    cout << "\nDuration(seconds): ";
    cin >> sec;
    cout << "\nLink: ";
    getline(cin, lk);
    getline(cin, lk);
    d = Duration(min, sec);
    Tutorial tut = Tutorial(tt, pr, d, 0, lk);
    try{
        if(this -> ui.add(tut)) cout << "\nTutorial already existing";
        else {
            cout << "\nOK!";
            ui.saveR();
        }
    }
    catch(TutorialException& exc){
        std::cout << exc.what();
    }
}

void UI::deleteA(){
    std::string toDelete;
    cout << "\nTitle to delete: ";
    getline(cin, toDelete);
    getline(cin, toDelete);
    if(this -> ui.rm(toDelete) == 0) cout << "\nTutorial not found";
    else {
        cout << "\nOK!";
        ui.saveR();
    }
}

void UI::printMenu(){
    cout << "\n1. Add";
    cout << "\n2. Delete";
    cout << "\n3. Update";
    cout << "\n4. Print";
    cout << "\n5. Done";
    cout << '\n';
}

void UI::printWmenu(){
    cout << "\n1. See tutorial by a presenter";
    cout << "\n2. Delete a tutorial from watch list";
    cout << "\n3. Save the watch list to file";
    cout << "\n4. Display the watch list";
    cout << "\n5. Done";
    cout << '\n';
}

void UI::printRepo(){
    for( auto it : ui.byPresenter("") )
        cout << it.getTitle() << " presented by " << it.getPresenter() << " has a duration of "
                << it.getTime().getMinutes() << " mins and " << it.getTime().getSeconds() << " secs."
                << '\n' <<"                VIEW IT NOW ON : " << it.getLink() << '\n';
}

void UI::showTuts(){
    std::string pr, openLink = "firefox ";
    int opt;
    cout << "\nPresenter name: ";
    getline(cin, pr);
    getline(cin, pr);
    ui.readR();
    std::vector<Tutorial> v = ui.byPresenter(pr);
    if( v.size() != 0 ) {
        int doThis = 1;
        while(doThis){

            for(auto it : v){

                openLink = "firefox ";
                openLink += it.getLink();

                system( &openLink[0u] );
                cout << it.getTitle() << " presented by " << it.getPresenter() << " has a duration of "
                     << it.getTime().getMinutes() << " mins and " << it.getTime().getSeconds() << " secs."<< '\n';
                std::cout<<"Like the tutorial? \n1.Yes\n2.No"<<'\n';
                cin >> opt;
                if(opt == 1){
                    if( ui.addToPL(it) == 0) cout << "It is already in the watch list." << '\n';
                        else {
                        cout << "Added to the watch list succesfully." << '\n';
                        ui.saveP();
                    }
                }
                cout << "1.Next" << '\n';
                cout << "2.Exit" << '\n';
                cin >> opt;
                doThis = opt;
                if(opt == 2) {
                    doThis = 0;
                    break;
                }
            }
        }
    }

    else std::cout << "There is no such presenter" << '\n';

}

void UI::delTut(){
    std::string toDelete;
    int like;
    cout << "\nTitle to delete: ";
    getline(cin, toDelete);
    getline(cin, toDelete);
    if(this -> ui.rmW(toDelete) == 0) cout << "\nTutorial not found";
    else {
        cout << "\nOK!";
        cout << "1.Like\n2.Not so useful\n";
        cin >> like;
        if( like == 1) ui.like(toDelete);
        ui.saveP();
    }
}

void UI::saveTuts(){
    ui.saveToFile();
}

void UI::printWlist(){
    /*
     *
     * Normal printing
     *
     * vector<Tutorial> v = ui.getWlist();
    for(auto it : v)
        cout << it.getTitle() << " presented by " << it.getPresenter() << " has a duration of "
             << it.getTime().getMinutes() << " mins and " << it.getTime().getSeconds() << " secs."
             << " Likes: " << it.getLikes()
                << '\n' <<"                VIEW IT NOW ON : " << it.getLink() << '\n';

                */
    ui.displayFile();
}
