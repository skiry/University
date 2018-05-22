#ifndef USERMODE_H
#define USERMODE_H

#include <QDialog>
#include "controller.h"
#include <QMainWindow>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include <QListWidget>
#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui
{
class userMode;
}

class userMode : public QDialog
{
    Q_OBJECT

public:
    explicit userMode(Controller C, QWidget *parent = 0);
    void init();
    void gui();
    void connectSS();
    void populateList();
    ~userMode();

private slots:
    void showTuts();
    void delTut();
    void printTuts();

private:
    Ui::userMode *ui;
    Controller c;
    QVBoxLayout* vB;
    QHBoxLayout* hL, * textt;
    QFormLayout *formLayout;
    QTextBrowser* tB;
    QListWidget* list;
    QLineEdit* prTextBox;
    QLabel* prLabel;
    QPushButton* add, * del, *prt;
    QWidget *wnd;
    std::string before = "", now = "";
    int counter;
    std::vector<Tutorial> v;
};

#endif // USERMODE_H
