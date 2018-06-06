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
#include <QComboBox>
#include <QtCharts>

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
    ~userMode();

private slots:
    void showTuts();
    void delTut();
    void printTuts();
    void populateList();
    void undo();
    void redo();
    void showTable();

private:
    Ui::userMode *ui;
    Controller c;
    QVBoxLayout* vB, * textt;
    QHBoxLayout* hL;
    QFormLayout *formLayout;
    QTextBrowser* tB;
    QString act;
    QListWidget* list;
    QLineEdit* prTextBox;
    QLabel* prLabel;
    QPushButton* add, * del, *prt, *u, *r, *t;
    QComboBox* combo;
    QWidget *wnd;
    std::string before = "", now = "";
    int counter;
    std::vector<Tutorial> v;
    QPieSeries *series;
    QChart *chart;
    QChartView *chartView;
};

#endif // USERMODE_H
