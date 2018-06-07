#include "usermode.h"
#include "ui_usermode.h"
#include "unordered_map"
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
#include <QComboBox>
#include <unistd.h>
#include <mvc.h>
#include <QTableView>
#include <QtCharts>

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
    textt = new QVBoxLayout{};
    tB = new QTextBrowser{};
    list = new QListWidget{};
    prTextBox = new QLineEdit{};
    prLabel = new QLabel{ "&Presenter Name:" };
    add = new QPushButton{"Show me tutorial"};
    del = new QPushButton{"Delete from the watch list"};
    prt = new QPushButton{};
    wnd = new QWidget{};
    vB = new QVBoxLayout{};
    combo = new QComboBox{};
    u = new QPushButton{"Undo"};
    r = new QPushButton{"Redo"};
    t = new QPushButton{"Table"};
    series = new QPieSeries();
    chart = new QChart();
    chartView = new QChartView(chart);
}

void userMode::showTable()
{
    QDialog* diag = new QDialog;
    diag->setWindowTitle("Tutorials Table");
    QVBoxLayout* v = new QVBoxLayout{};
    QTableView* tab = new QTableView{};
    tab->setModel(new TutorialsTableModel{c.getRepo()});
    v->addWidget(tab);
    tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tab->horizontalHeader()->resizeContentsPrecision();
    tab->resizeRowsToContents();
    tab->resizeColumnsToContents();
    diag->setLayout(v);
    diag->show();
}

void userMode::gui()
{
    hL->addLayout(vB);
    hL->addLayout(textt);
    vB -> addLayout(formLayout);
    vB -> addWidget(chartView);
    vB -> addWidget(add);
    vB -> addWidget(del);
    vB -> addWidget(prt);
    vB -> addWidget(u);
    vB -> addWidget(r);
    vB -> addWidget(t);
    chart -> addSeries(series);
    prt ->setText(QString::fromStdString("Show the watch list in the " + c.wat() + " format"));
    textt->addWidget(combo);
    combo->addItem(QString::fromStdString("Detailed"));
    combo->addItem(QString::fromStdString("Short"));
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
    connect( combo, SIGNAL(currentIndexChanged(int)), this, SLOT( populateList()) );
    connect( u, SIGNAL(clicked(bool)), this, SLOT( undo()) );
    connect( r, SIGNAL(clicked(bool)), this, SLOT( redo()) );
    connect( t, SIGNAL(clicked(bool)), this, SLOT( showTable()) );
}

void userMode::populateList()
{
    this -> list -> clear();
    std::string ret;
    std::unordered_map<std::string, bool> vis;

    chart->removeSeries(series);
    delete series;
    series = new QPieSeries();

    if ( combo->currentText().toStdString() == "Detailed" ) {
        for ( const auto& tut : c.getWlist() ) {
            ret = tut.getTitle() + " by " + tut.getPresenter() + " with the length of " + std::to_string( tut.getTime().getMinutes() ) + ":" +
                  std::to_string( tut.getTime().getSeconds() ) + " has " + std::to_string( tut.getLikes() ) + " likes. \nAccess it on " + tut.getLink();
            this -> list ->addItem(QString::fromStdString(ret));

            if ( vis[ tut.getPresenter() ] == false ) {
                series->append(QString::fromStdString(tut.getPresenter()), c.byPresenterWL(tut.getPresenter()).size());
                vis[ tut.getPresenter() ] = true;
            }
        }

    } else {
        for ( const auto& tut : c.getWlist() ) {

            ret = tut.getTitle() + ". \nAccess it on " + tut.getLink();
            this -> list ->addItem(QString::fromStdString(ret));

            if ( vis[ tut.getPresenter() ] == false ) {
                series->append(QString::fromStdString(tut.getPresenter()), c.byPresenterWL(tut.getPresenter()).size());
                vis[ tut.getPresenter() ] = true;
            }
        }
    }

    //this -> list ->addItem(QString::fromStdString(c.allTuts()));

    chart->addSeries(series);
    chart->setTitle("Most liked tutorials by Presenters");
    chartView->setRenderHint(QPainter::Antialiasing);
}

void userMode::showTuts()
{
    std::string openLink = "firefox ";
    int opt = 0;
    now = prTextBox -> text().toStdString();

    if ( before == "" || before != now ) {
        v = c.byPresenter(now);

        if ( !(before == "" && now == "") ) {
            counter = 0;
        }
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
        }

        c.save();
        c.saveToFile();
        populateList();
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


void userMode::undo()
{
    if ( c.doUndo() ) {
        QMessageBox::information(this, "OK", "Undo done", QMessageBox::Ok);
        c.save();
        populateList();

    } else {
        QMessageBox::information(this, "Error", "You can't undo", QMessageBox::Rejected);
    }
}

void userMode::redo()
{
    if ( c.doRedo() ) {
        QMessageBox::information(this, "OK", "Redo done", QMessageBox::Ok);
        c.save();
        populateList();

    } else {
        QMessageBox::information(this, "Error", "You can't redo", QMessageBox::Rejected);
    }
}
