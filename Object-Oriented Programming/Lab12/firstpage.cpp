#include "firstpage.h"
#include "ui_firstpage.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QRadioButton>
#include <QWidget>
#include <QGroupBox>
#include <QPalette>
#include "csvplaylist.h"
#include "htmlplaylist.h"
#include "repository.h"
#include "controller.h"

FirstPage::FirstPage(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FirstPage)
{
	init();
	gui();
	connectSS();
	ui->setupUi(this);
}

void FirstPage::init()
{
	wdg = new QWidget{};
	last = new QVBoxLayout{this};
	main = new QHBoxLayout{};
	userType = new QVBoxLayout{};
	fileType = new QVBoxLayout{};
	adm = new QRadioButton{"Administrator"};
	usr = new QRadioButton{"Regular User"};
	csv = new QRadioButton{"CSV File"};
	html = new QRadioButton{"HTML File"};
	grOne = new QGroupBox{tr("What type of user do you want to be?")};
	grTwo = new QGroupBox{"Where do you want to store the data?"};
	done = new QPushButton{"Start"};
}

void FirstPage::gui()
{
	//this -> setLayout(wdg);
	main -> addWidget(grOne);
	main -> addWidget(grTwo);
	userType -> addWidget(adm);
	userType -> addWidget(usr);
	fileType -> addWidget(csv);
	fileType -> addWidget(html);
	adm -> setChecked(true);
	csv -> setChecked(true);
	grOne -> setLayout(userType);
	grTwo -> setLayout(fileType);
	last -> addLayout(main);
	last -> addWidget(done);

	pal = done -> palette();
	pal.setColor(QPalette::Button, QColor(Qt::blue));
	done -> setPalette(pal);

	//int width = baseSize().width() + 3 * sizeIncrement().width();
	//int height = baseSize().height() + 1 * sizeIncrement().height();
	//done -> setSizeIncrement(width, height);
	this -> show();
}

void FirstPage::connectSS()
{
	connect(done, SIGNAL(clicked(bool)), this, SLOT(start()));
}

void FirstPage::start()
{
	Repository myRepo = Repository{};

	if ( csv -> isChecked() )
		p = new CSVPlaylist{ "WatchList.CSV" };
	else
		p = new HTMLPlaylist{ "WatchList.html" };

	Controller ctrl = Controller{ myRepo, p };

	if ( adm -> isChecked() ) {
		this -> hide();
		mw = new MainWindow { ctrl };

	} else {
        this -> hide();
        um = new userMode { ctrl };
	}
}

FirstPage::~FirstPage()
{
	delete ui;
}
