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
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controller C, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void populateList();
    void clearList();

private:
    Ui::MainWindow *ui;
    Controller c;
    QHBoxLayout* hL,* textt;
    QFormLayout *formLayout;
    QTextBrowser* tB;
    QListWidget* list;
    QLineEdit* nameTextBox,* prTextBox,* minsBox,* secsBox,* linkBox;
    QLabel* nameLabel,* prLabel,* minsLabel,* secsLabel,* linkLabel;
    QPushButton* add,* pop,* clr;
    QWidget *wnd;

};

#endif // MAINWINDOW_H
