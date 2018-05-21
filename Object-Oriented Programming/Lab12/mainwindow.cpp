#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QMessageBox>

MainWindow::MainWindow(Controller C, QWidget *parent) :
    c{ C },
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QHBoxLayout* hL = new QHBoxLayout{};
        QFormLayout *formLayout = new QFormLayout{};
        QHBoxLayout* textt = new QHBoxLayout{};

        hL->addLayout(formLayout);
        hL->addLayout(textt);

        this -> tB = new QTextBrowser{};
        //textt->addWidget(tB);


        this->list = new QListWidget{};
        textt->addWidget(list);
            // create labels and textboxes
            QLineEdit* nameTextBox = new QLineEdit{};
            QLabel* nameLabel = new QLabel{ "&Title:" };
            nameLabel->setBuddy(nameTextBox);

            QLineEdit* prTextBox = new QLineEdit{};
            QLabel* prLabel = new QLabel{ "&Presenter:" };
            prLabel->setBuddy(prTextBox);

            QLineEdit* minsBox = new QLineEdit{};
            QLabel* minsLabel = new QLabel{ "&Minutes:" };
            minsLabel->setBuddy(minsBox);

            QLineEdit* secsBox = new QLineEdit{};
            QLabel* secsLabel = new QLabel{ "&Seconds:" };
            secsLabel->setBuddy(secsBox);

            QLineEdit* linkBox = new QLineEdit{};
            QLabel* linkLabel = new QLabel{ "&Link:" };
            linkLabel->setBuddy(linkBox);

            formLayout->addRow(nameLabel, nameTextBox);
            formLayout->addRow(prLabel, prTextBox);
            formLayout->addRow(minsLabel, minsBox);
            formLayout->addRow(secsLabel, secsBox);
            formLayout->addRow(linkLabel, linkBox);

            QPushButton* add = new QPushButton{"Add Tutorial"};
            QPushButton* pop = new QPushButton{"Populate"};
            QPushButton* clr = new QPushButton{"Clear"};


            formLayout->addWidget(add);
            formLayout->addWidget(pop);
            formLayout->addWidget(clr);

            connect( pop, SIGNAL(clicked(bool)), this, SLOT(populateList()) );
            connect( clr, SIGNAL(clicked(bool)), this, SLOT(clearList()) );

            QWidget *wnd = new QWidget{};
            wnd->setLayout(hL);
            wnd->show();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateList(){
    this -> list -> addItem(QString::fromStdString( this -> c.allTuts()) );
    QMessageBox::information(this, "Success", "Populated the list!", QMessageBox::Ok);
    //this -> tB -> insertPlainText(QString::fromStdString( this -> c.allTuts()));
}

void MainWindow::clearList(){
    this -> list -> clear();
    QMessageBox::information(this, "Success", "Cleared everything!", QMessageBox::Ok);
}
