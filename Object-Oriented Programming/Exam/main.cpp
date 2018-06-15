#include "mainwindow.h"
#include <QApplication>
#include "repository.h"
#include "controller.h"
#include "participants.h"
#include "presenter.h"
void tests()
{
    Repository r{"questions.txt", "participants.txt"};
    assert(r.getP().size() == 4 );

    assert(r.getQ().size() == 3);

    for (auto i : r.getP() ) {
        assert(i.getScore() == 0);
    }

    assert(r.getQ()[2].getText() == "How well do you know OOP?");

    assert(r.getQ()[1].getScore() == 2);
    assert(r.getQ()[0].getAnswer() == "9");

    r.add(Question{4, "What year it is?", "2018", 10});
    assert(r.getQ().size() == 4);

    assert(r.getQ()[3].getAnswer() == "2018");
    assert(r.getQ()[3].getText() == "What year it is?");

    r.increaseScore("Ionut", 10);

    assert(r.getP()[0].getScore() == 10);
    r.increaseScore("Ionut", 3);

    assert(r.getP()[0].getScore() == 13);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Repository r{"questions.txt", "participants.txt"};
    Controller c{r};
    //tests();
    std::vector<Participants*> pts;

    for (int i = 0; i < r.getP().size(); i++) {
        Participants *p = new Participants{ c, r.getP()[i] };
        pts.push_back(p);
        pts[i]->show();
    }

    Presenter* pr = new Presenter{c};
    pr->show();

    return a.exec();
}
