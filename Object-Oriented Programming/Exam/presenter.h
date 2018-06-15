#ifndef PRESENTER_H
#define PRESENTER_H
#include "controller.h"
#include "observer.h"
#include "ui_presenter.h"
#include <QWidget>

namespace Ui
{
class Presenter;
}

class Presenter : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit Presenter(Controller& ct, QWidget *parent = 0);
    ~Presenter();

private:
    Ui::Presenter ui;
    Controller& c;
    void add();
    void update() override;
    void populate();
    int getListSelectedIndex();
    void listItemChanged();
    std::vector<Question> myList;
};

#endif // PRESENTER_H
