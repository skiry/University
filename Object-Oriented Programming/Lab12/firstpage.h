#ifndef FIRSTPAGE_H
#define FIRSTPAGE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QPalette>
#include "fileplaylist.h"
#include "mainwindow.h"
#include "usermode.h"

namespace Ui
{
class FirstPage;
}

class FirstPage : public QDialog
{
    Q_OBJECT

public:
    explicit FirstPage(QWidget *parent = 0);
    void init();
    void gui();
    void connectSS();
    ~FirstPage();

private slots:
    void start();

private:
    Ui::FirstPage *ui;
    QWidget* wdg;
    QHBoxLayout* main;
    QVBoxLayout* userType, * fileType, *last;
    QRadioButton* adm, *usr, *csv, *html;
    QGroupBox* grOne, *grTwo;
    QPushButton* done;
    QPalette pal;
    FilePlaylist* p;
    MainWindow* mw;
    userMode* um;
};

#endif // FIRSTPAGE_H
