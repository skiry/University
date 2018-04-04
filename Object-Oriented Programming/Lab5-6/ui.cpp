#include "ui.h"
using namespace std;

void UI::start(){
int p, ok = 1, opt;
cout << "1. Administrator";
cout << "\n2. User Mode";
cin >> p;
if(p != 1) cout << "Not ok";
else while(ok){
    cout << "\n1. Add";
    cout << "\n2. Delete";
    cout << "\n3. Update";
    cout << "\n4. Print";
    cout << "\n5. Done";
    cout << '\n';
    cin >> opt;
    if(opt == 5) ok = 0;
    else if(opt == 4){
        Controller test = this -> ui;
        for(int i = 0; i < test.len(); i++)
            cout << test[i].getTitle() << " presented by " << test[i].getPresenter() << " has a duration of "
                    << test[i].getTime().getMinutes() << " mins and " << test[i].getTime().getSeconds() << " secs."
                    << '\n' <<"                VIEW IT NOW ON : " << test[i].getLink() << '\n';
    }
    else if(opt == 3){
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
        if(this -> ui.upd(toReplace, tut) == 0) cout << "\nTutorial not found";
        else cout << "\nOK!";
    }
    else if(opt == 2){
        std::string toDelete;
        cout << "\nTitle to delete: ";
        getline(cin, toDelete);
        getline(cin, toDelete);
        if(this -> ui.rm(toDelete) == 0) cout << "\nTutorial not found";
        else cout << "\nOK!";
    }
    else if(opt == 1){
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
        if(this -> ui.add(tut)) cout << "\nTutorial already existing";
        else cout << "\nOK!";
    }
}
}
