#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H
#include "observer.h"
#include <QWidget>
#include "controller.h"
#include "ui_participants.h"
namespace Ui
{
class Participants;
}

class Participants : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit Participants(Controller& ct, Participant pt, QWidget *parent = 0);
    ~Participants();

private:
    Ui::Participants ui;
    Controller& c;
    Participant p;
    void answer();
    void update() override;
    void populate();
    int getListSelectedIndex();
    void listItemChanged();
    std::vector<Question> myList;
    std::vector<std::string> answered;
};

#endif // PARTICIPANTS_H
