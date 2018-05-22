#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
#include <QDebug>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QGroupBox>
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controller C, QWidget *parent = 0);
    void init();
    void gui();
    void connectSS();
    ~MainWindow();

public slots:
    void populateList();
    void hideOthers();
    void showOthers();
    void showUpd();
    void addTut();
    void delTut();
    void updTut();

private:
    Ui::MainWindow *ui;
    Controller c;
    QHBoxLayout* hL, * textt, *chs;
    QFormLayout *formLayout;
    QTextBrowser* tB;
    QListWidget* list;
    QLineEdit* nameTextBox, * prTextBox, * minsBox, * secsBox, * linkBox, *nnBox;
    QLabel* nameLabel, * prLabel, * minsLabel, * secsLabel, * linkLabel, *nn;
    QPushButton* add, * del, * upd;
    QRadioButton* aR, *dR, *uR;
    QWidget *wnd;
    QGroupBox* gr;

};

#endif // MAINWINDOW_H
