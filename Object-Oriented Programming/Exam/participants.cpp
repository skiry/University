#include "participants.h"
#include "ui_participants.h"
#include "QBrush"
#include "QColor"

Participants::Participants(Controller& ct, Participant pt, QWidget *parent) :
    QWidget(parent),
    c{ct},
    p{pt}
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(p.getName()));
    this->c.addObserver(this);
    this->myList = this->c.getAll();
    this->populate();
    QObject::connect(ui.repoList, &QListWidget::itemSelectionChanged, this, &Participants::listItemChanged);
    QObject::connect(ui.answerB, &QPushButton::clicked, this, &Participants::answer);
    listItemChanged();
}

void Participants::answer()
{
    std::string an = ui.answer->text().toStdString();
    int idx = getListSelectedIndex();

    if (idx == -1) {
        return;
    }

    if (idx >= myList.size()) {
        return;
    }

    Question tt = myList[idx];

    if ( an == tt.getAnswer() ) {
        c.increaseScore(p.getName(), tt.getScore());
        p.addScore(tt.getScore());
        answered.push_back(an);
        //QPalette pal = ui.repoList[idx].palette();
        // pal.setColor(ui.repoList[idx].backgroundRole(), Qt::green);
        //ui.repoList[idx].setPalette(pal);

    }

    this->populate();
}

void Participants::populate()
{
    ui.repoList->clear();
    this->myList = this->c.getAll();

    if (myList.size() == 0) {
        return;
    }

    for (auto t : myList) {

        QString details = QString::fromStdString(std::to_string(t.getId()) + "," + t.getText() + "," + std::to_string(t.getScore()));

        QListWidgetItem *item = new QListWidgetItem(details);

        for (auto& j : answered)
            if ( j == t.getAnswer() ) {
                item->setBackgroundColor(Qt::green);
            }

        ui.repoList->addItem(item);
    }

    if (this->myList.size() > 0) {
        ui.repoList->setCurrentRow(0);
    }

    ui.score->setText(QString::fromStdString(std::to_string(p.getScore())));
}

void Participants::update()
{
    this->populate();
    listItemChanged();
}

int Participants::getListSelectedIndex()
{
    if (ui.repoList->count() == 0) {
        return -1;
    }

    QModelIndexList index = ui.repoList->selectionModel()->selectedIndexes();

    if (index.size() == 0) {
        ui.answer->clear();
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}
void Participants::listItemChanged()
{
    int idx = getListSelectedIndex();

    if (idx == -1) {
        return;
    }

    if (idx >= myList.size()) {
        return;
    }

    Question t = myList[idx];
    ui.answer->setText(QString::fromStdString(t.getText()));
    int ok = 0;

    for (auto& i : answered)
        if ( i == t.getAnswer() ) {
            ++ok;
        }

    if (ok == 0) {
        ui.answerB->setEnabled(true);

    } else {
        ui.answerB->setEnabled(false);
    }
}

Participants::~Participants()
{
    c.removeObserver(this);
}
