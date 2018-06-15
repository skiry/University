#include "presenter.h"
#include "ui_presenter.h"
#include <QMessageBox>
#include "exception.h"
Presenter::Presenter(Controller& ct, QWidget *parent) :
    QWidget(parent),
    c{ct}
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString("The Presenter"));
    this->c.addObserver(this);
    this->myList = this->c.getAllPr();
    this->populate();
    QObject::connect(ui.repoList, &QListWidget::itemSelectionChanged, this, &Presenter::listItemChanged);
    QObject::connect(ui.add, &QPushButton::clicked, this, &Presenter::add);
    listItemChanged();
}

void Presenter::populate()
{
    ui.repoList->clear();
    this->myList = this->c.getAllPr();

    if (myList.size() == 0) {
        return;
    }

    for (auto t : myList) {

        QString details = QString::fromStdString(std::to_string(t.getId()) + "," + t.getText() + "," + t.getAnswer() + "," + std::to_string(t.getScore()));

        QListWidgetItem *item = new QListWidgetItem(details);
        ui.repoList->addItem(item);
    }

    if (this->myList.size() > 0) {
        ui.repoList->setCurrentRow(0);
    }
}

void Presenter::add()
{
    std::string text, ans;
    int id, sc;
    text = ui.text->text().toStdString();
    ans = ui.answer->text().toStdString();
    id = ui.id->text().toInt();
    sc = ui.score->text().toInt();

    try {
        this->c.add(id, text, ans, sc);
        this->populate();

    } catch (Exception& e) {
        QMessageBox msg;
        msg.critical(0, "Warning", e.what());
    }
}

void Presenter::update()
{
    this->populate();
    listItemChanged();
}

int Presenter::getListSelectedIndex()
{
    if (ui.repoList->count() == 0) {
        return -1;
    }

    QModelIndexList index = ui.repoList->selectionModel()->selectedIndexes();

    if (index.size() == 0) {
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}
void Presenter::listItemChanged()
{
    int idx = getListSelectedIndex();

    if (idx == -1) {
        return;
    }

    if (idx >= myList.size()) {
        return;
    }
}

Presenter::~Presenter()
{
    c.removeObserver(this);
}
