#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tutorial.h"
#include "tutorialvalidator.h"
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
#include <QRadioButton>
#include <QGroupBox>
#include <QPalette>
#include <QShortcut>
#include <QtGui>

MainWindow::MainWindow(Controller C, QWidget *parent) :
	c{ C },
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	init();
	gui();
	connectSS();
    c.read();
    populateList();
	ui->setupUi(this);
}

void MainWindow::init()
{

	hL = new QHBoxLayout{this};
	formLayout = new QFormLayout{};
	textt = new QHBoxLayout{};
	tB = new QTextBrowser{};
	list = new QListWidget{};
	nameTextBox = new QLineEdit{};
	nameLabel = new QLabel{ "&Title:" };
	prTextBox = new QLineEdit{};
    prLabel = new QLabel{ "P&resenter:" };
	minsBox = new QLineEdit{};
    minsLabel = new QLabel{ "Mi&nutes:" };
	secsBox = new QLineEdit{};
    secsLabel = new QLabel{ "Sec&onds:" };
	linkBox = new QLineEdit{};
	linkLabel = new QLabel{ "&Link:" };
    nnBox = new QLineEdit{};
    nn = new QLabel{ "Title to update:" };
	add = new QPushButton{"Add Tutorial"};
	del = new QPushButton{"Delete"};
	upd = new QPushButton{"Update"};
    u = new QPushButton{"Undo"};
    r = new QPushButton{"Redo"};
	wnd = new QWidget{};
	aR = new QRadioButton{};
	dR = new QRadioButton{};
	uR = new QRadioButton{};
    gr = new QGroupBox{};
}

void MainWindow::gui()
{
	hL->addLayout(formLayout);
	hL->addLayout(textt);
	textt->addWidget(list);
	nameLabel->setBuddy(nameTextBox);
	prLabel->setBuddy(prTextBox);
	minsLabel->setBuddy(minsBox);
	secsLabel->setBuddy(secsBox);
	linkLabel->setBuddy(linkBox);
	formLayout->addRow(nameLabel, nameTextBox);
	formLayout->addRow(prLabel, prTextBox);
	formLayout->addRow(minsLabel, minsBox);
	formLayout->addRow(secsLabel, secsBox);
	formLayout->addRow(linkLabel, linkBox);
    formLayout->addRow(nn, nnBox);
	formLayout->addRow(aR, add);
	formLayout->addRow(dR, del);
	formLayout->addRow(uR, upd);
    formLayout->addWidget(u);
    formLayout->addWidget(r);
    aR -> setChecked(false);
    dR -> setChecked(false);
    uR -> setChecked(false);
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::gray);
    palette->setColor(QPalette::Text, Qt::darkGray);

    und = new QShortcut(this);//QKeySequence(Qt::CTRL + Qt::Key_Z), this, SLOT(undo()));
    red = new QShortcut(this);//QKeySequence(Qt::CTRL + Qt::Key_Y), this, SLOT(redo()));
    und->setKey(Qt::CTRL + Qt::Key_Z);
    red->setKey(Qt::CTRL + Qt::Key_Y);

    prTextBox -> setReadOnly(true);
    prTextBox ->setPalette(*palette);

    minsBox -> setReadOnly(true);
    minsBox ->setPalette(*palette);

    secsBox -> setReadOnly(true);
    secsBox ->setPalette(*palette);

    linkBox -> setReadOnly(true);
    linkBox ->setPalette(*palette);

    nnBox -> setReadOnly(true);
    nnBox ->setPalette(*palette);

    nameTextBox -> setReadOnly(true);
    nameTextBox ->setPalette(*palette);

    wnd->setLayout(hL);
	wnd->show();


}

void MainWindow::connectSS()
{
    connect( add, SIGNAL(clicked(bool)), this, SLOT(populateList()) );
	connect( dR, SIGNAL(clicked(bool)), this, SLOT(hideOthers()) );
	connect( aR, SIGNAL(clicked(bool)), this, SLOT(showOthers()) );
    connect( uR, SIGNAL(clicked(bool)), this, SLOT(showUpd()) );
	connect( add, SIGNAL(clicked(bool)), this, SLOT(addTut()) );
    connect( del, SIGNAL(clicked(bool)), this, SLOT(delTut()) );
    connect( upd, SIGNAL(clicked(bool)), this, SLOT(updTut()) );
    connect( und, SIGNAL(activated()), this, SLOT(undo()));
    connect( red, SIGNAL(activated()), this, SLOT(redo()));
    connect( u, SIGNAL(clicked(bool)), this, SLOT( undo()) );
    connect( r, SIGNAL(clicked(bool)), this, SLOT( redo()) );
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::populateList()
{
    this -> list -> clear();
    std::string ret;

    for ( const auto& tut : c.byPresenter("") ) {
        ret = tut.getTitle() + " by " + tut.getPresenter() + " with the length of " + std::to_string( tut.getTime().getMinutes() ) + ":" +
              std::to_string( tut.getTime().getSeconds() ) + " has " + std::to_string( tut.getLikes() ) + " likes. \nAccess it on " + tut.getLink();
        this -> list ->addItem(QString::fromStdString(ret));
    }
}

void MainWindow::hideOthers()
{
	QPalette *palette = new QPalette();
	palette->setColor(QPalette::Base, Qt::gray);
    palette->setColor(QPalette::Text, Qt::darkGray);

    prTextBox -> setReadOnly(true);
    prTextBox ->setPalette(*palette);

	minsBox -> setReadOnly(true);
	minsBox ->setPalette(*palette);

	secsBox -> setReadOnly(true);
	secsBox ->setPalette(*palette);

	linkBox -> setReadOnly(true);
	linkBox ->setPalette(*palette);

    nnBox -> setReadOnly(true);
    nnBox ->setPalette(*palette);

    palette->setColor(QPalette::Base, Qt::white);
    palette->setColor(QPalette::Text, Qt::black);

    nameTextBox -> setReadOnly(false);
    nameTextBox ->setPalette(*palette);

}

void MainWindow::showOthers()
{
	QPalette *palette = new QPalette();
	palette->setColor(QPalette::Base, Qt::white);
    palette->setColor(QPalette::Text, Qt::black);

    nameTextBox -> setReadOnly(false);
    nameTextBox ->setPalette(*palette);

    prTextBox -> setReadOnly(false);
    prTextBox ->setPalette(*palette);

	minsBox -> setReadOnly(false);
	minsBox ->setPalette(*palette);

	secsBox -> setReadOnly(false);
	secsBox ->setPalette(*palette);

	linkBox -> setReadOnly(false);
	linkBox ->setPalette(*palette);

    palette->setColor(QPalette::Base, Qt::gray);
    palette->setColor(QPalette::Text, Qt::darkGray);

    nnBox -> setReadOnly(true);
    nnBox ->setPalette(*palette);
}

void MainWindow::showUpd()
{
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    palette->setColor(QPalette::Text, Qt::black);

    nnBox -> setReadOnly(false);
    nnBox ->setPalette(*palette);

    nameTextBox -> setReadOnly(false);
    nameTextBox ->setPalette(*palette);

    prTextBox -> setReadOnly(false);
    prTextBox ->setPalette(*palette);

    minsBox -> setReadOnly(false);
    minsBox ->setPalette(*palette);

    secsBox -> setReadOnly(false);
    secsBox ->setPalette(*palette);

    linkBox -> setReadOnly(false);
    linkBox ->setPalette(*palette);
}

void MainWindow::addTut()
{
	std::string tt, pr, lk;
	int min, sec;
	Duration d;

    if ( aR -> isChecked() ) {
        tt = nameTextBox -> text().toStdString();
        pr = prTextBox -> text().toStdString();
        lk = linkBox -> text().toStdString();
        min = minsBox -> text().toInt();
        sec = secsBox -> text().toInt();
        d = Duration(min, sec);
        Tutorial tut = Tutorial(tt, pr, d, 0, lk);

        try {
            if (this -> c.add(tut)) {
                QMessageBox::information(this, "Failed", "Tutorial already existing!", QMessageBox::Ok);


            } else {
                QMessageBox::information(this, "Success", "Added the tutorial succsefully!", QMessageBox::Ok);
                c.save();
                populateList();
            }

        } catch (TutorialException& exc ) {
            QMessageBox::information(this, "Failed", exc.what(), QMessageBox::Ok);
        }

    } else {
        QMessageBox::information(this, "Error", "You haven't selected the add button", QMessageBox::Ok);
    }
}

void MainWindow::delTut()
{
    std::string tt;

    tt = nameTextBox -> text().toStdString();

    if ( dR -> isChecked() ) {
        try {
            if (this -> c.rm(tt) == 0) {
                QMessageBox::information(this, "Failed", "Tutorial not found!", QMessageBox::Ok);


            } else {
                QMessageBox::information(this, "Success", "Deleted succesfully!", QMessageBox::Ok);
                c.save();
                populateList();
            }

        } catch (TutorialException& exc ) {
            QMessageBox::information(this, "Failed", exc.what(), QMessageBox::Ok);
        }

    } else {
        QMessageBox::information(this, "Error", "You haven't selected the delete button", QMessageBox::Rejected);
    }

}

void MainWindow::updTut()
{
    std::string tt, pr, lk, toReplace;
    int min, sec;
    Duration d;

    if ( uR -> isChecked() ) {
        tt = nameTextBox -> text().toStdString();
        pr = prTextBox -> text().toStdString();
        lk = linkBox -> text().toStdString();
        min = minsBox -> text().toInt();
        sec = secsBox -> text().toInt();
        toReplace = nnBox -> text().toStdString();
        d = Duration(min, sec);
        Tutorial tut = Tutorial(tt, pr, d, 0, lk);

        try {
            if (this -> c.upd(toReplace, tut) == 0) {
                QMessageBox::information(this, "Failed", "Tutorial not found!", QMessageBox::Ok);


            } else {
                QMessageBox::information(this, "Success", "Updated succesfully!", QMessageBox::Ok);
                c.save();
                populateList();
            }

        } catch (TutorialException& exc ) {
            QMessageBox::information(this, "Failed", exc.what(), QMessageBox::Ok);
        }

    } else {
        QMessageBox::information(this, "Error", "You haven't selected the update button", QMessageBox::Ok);
    }
}

void MainWindow::undo()
{
    if ( c.doUndo() ) {
        QMessageBox::information(this, "OK", "Undo done", QMessageBox::Ok);
        c.save();
        populateList();

    } else {
        QMessageBox::information(this, "Error", "You can't undo", QMessageBox::Rejected);
    }
}

void MainWindow::redo()
{
    if ( c.doRedo() ) {
        QMessageBox::information(this, "OK", "Redo done", QMessageBox::Ok);
        c.save();
        populateList();

    } else {
        QMessageBox::information(this, "Error", "You can't redo", QMessageBox::Rejected);
    }
}
