#include "usermode.h"
#include "ui_usermode.h"
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
#include <QMessageBox>
#include <unistd.h>

userMode::userMode(Controller C, QWidget *parent) :
    c{ C },
    QDialog(parent),
    ui(new Ui::userMode)
{
    init();
    gui();
    connectSS();
    c.read();
    populateList();
    ui->setupUi(this);
}

void userMode::init()
{

    hL = new QHBoxLayout{this};
    formLayout = new QFormLayout{};
    textt = new QHBoxLayout{};
    tB = new QTextBrowser{};
    list = new QListWidget{};
    prTextBox = new QLineEdit{};
    prLabel = new QLabel{ "&Presenter Name:" };
    add = new QPushButton{"Show me tutorial"};
    del = new QPushButton{"Delete from the watch list"};
    prt = new QPushButton{};
    wnd = new QWidget{};
    vB = new QVBoxLayout{};
}

void userMode::gui()
{
    hL->addLayout(vB);
    hL->addLayout(textt);
    vB -> addLayout(formLayout);
    vB -> addWidget(add);
    vB -> addWidget(del);
    vB -> addWidget(prt);
    prt ->setText(QString::fromStdString("Show the watch list in the " + c.wat() + " format"));
    textt->addWidget(list);
    prLabel->setBuddy(prTextBox);
    formLayout->addRow(prLabel, prTextBox);
    wnd->setLayout(hL);
    wnd->show();
}

void userMode::connectSS()
{
    connect( add, SIGNAL(clicked(bool)), this, SLOT( showTuts() ) );
    connect( del, SIGNAL(clicked(bool)), this, SLOT( delTut()) );
    connect( prt, SIGNAL(clicked(bool)), this, SLOT( printTuts()) );
}

void userMode::populateList()
{
    this -> list -> clear();
    std::string ret;

    for ( const auto& tut : c.getWlist() ) {
        ret = tut.getTitle() + " by " + tut.getPresenter() + " with the length of " + std::to_string( tut.getTime().getMinutes() ) + ":" +
              std::to_string( tut.getTime().getSeconds() ) + " has " + std::to_string( tut.getLikes() ) + " likes. \nAccess it on " + tut.getLink();
        this -> list ->addItem(QString::fromStdString(ret));
    }
}

void userMode::showTuts()
{
    std::string openLink = "firefox ";
    int opt = 0;
    now = prTextBox -> text().toStdString();

    if ( before == "" || before != now ) {
        v = c.byPresenter(now);
        counter = 0;
    }

    if ( counter < v.size() ) {
        openLink += v[counter].getLink();
        ++counter;

        if ( counter == v.size() ) {
            opt = 1;
            counter = 0;
        }
    }

    if ( !v.size() ) {
        QMessageBox::information(this, "Failed", "No such presenters!", QMessageBox::Ok);

    } else {
        system( &openLink[0u] );
        sleep(3);
        std::string ret;
        ret = v[counter].getTitle() + " by " + v[counter].getPresenter() + " with the length of " +
              std::to_string( v[counter].getTime().getMinutes() ) + ":" + std::to_string( v[counter].getTime().getSeconds() ) +
              " has " + std::to_string( v[counter].getLikes() ) + " likes. \n";

        auto reply = QMessageBox::question(this, "Query", QString::fromStdString(ret + "Add to the watch list?"), QMessageBox::Yes | QMessageBox::No);

        if ( reply == QMessageBox::Yes ) {
            if ( c.addToPL(v[counter]) == 0 ) {
                QMessageBox::information(this, "Failed", "It is already in the watch list", QMessageBox::Ok);

            } else {
                QMessageBox::information(this, "Succes", "Added to the watch list succesfully", QMessageBox::Ok);
                c.save();
                c.saveToFile();
                populateList();
            }
        }

        before = now;
    }

    if ( opt ) {
        QMessageBox::information(this, "OK", "You have seen all his tutorials!", QMessageBox::Ok);
    }

}

void userMode::delTut()
{
    std::string toDelete;
    toDelete = prTextBox -> text().toStdString();

    if (this -> c.rmW(toDelete) == 0) {
        QMessageBox::information(this, "Failed", "Tutorial not found in the watch list", QMessageBox::Ok);

    } else {
        auto reply = QMessageBox::question(this, "Query", "Do you like the video?", QMessageBox::Yes | QMessageBox::No);

        if ( reply == QMessageBox::Yes ) {
            c.like(toDelete);
            c.save();
            c.saveToFile();
            populateList();
        }
    }
}

void userMode::printTuts()
{
    c.displayFile();
}
userMode::~userMode()
{
    delete ui;
}
