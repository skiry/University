#include "mvc.h"
#include "ui_mvc.h"
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QBrush>
#include <tutorial.h>
#include <QMainWindow>
#include <QMessageBox>

TutorialsTableModel::TutorialsTableModel(Repository& _r, QObject* parent) : QAbstractTableModel{ parent }, r{ _r }
{
}

TutorialsTableModel::~TutorialsTableModel()
{
}

int TutorialsTableModel::rowCount(const QModelIndex & parent) const
{
    // Show a new empty row at the end, to allow adding data
    return r.getWlist().size() + 1;
}

int TutorialsTableModel::columnCount(const QModelIndex & parent) const
{
    return 6;
}

QVariant TutorialsTableModel::data(const QModelIndex & index, int role) const
{
    int row = index.row();
    int column = index.column();

    // get the tutorials
    std::vector<Tutorial> tuts = r.getWlist();

    // Allow adding in the table
    // this is to show an empty row at the end of the table - to allow adding new tutorials
    if (row == tuts.size()) {
        return QVariant();
    }

    // get the tutorial from the current row
    Tutorial t = tuts[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (column) {
        case 0:
            return QString::fromStdString(t.getTitle());

        case 1:
            return QString::fromStdString(t.getPresenter());

        case 2:
            return QString::fromStdString(std::to_string(t.getTime().getMinutes()) + ":"
                                          + std::to_string(t.getTime().getSeconds()));

        case 3:
            return QString::fromStdString(std::to_string(t.getLikes()));

        case 4:
            return QString::fromStdString(t.getLink());

        default:
            break;
        }
    }

    if (role == Qt::DecorationRole) {
        if ( index.column() == 5) {
            QPixmap pixMap("photo");
            return pixMap.scaled(40, 40, Qt::KeepAspectRatioByExpanding);
        }
    }

    if (role == Qt::FontRole) {
        QFont font("Times", 15, 10, true);
        font.setItalic(false);
        return font;
    }

    if (role == Qt::BackgroundRole) {
        if (row % 2 == 1) {
            return QBrush{ QColor{0, 250, 154} };
        }
    }

    return QVariant{};
}

QVariant TutorialsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Title");

            case 1:
                return QString("Presenter");

            case 2:
                return QString("Duration");

            case 3:
                return QString("Likes");

            case 4:
                return QString("Link");

            case 5:
                return QString("Play");
            }
        }
    }



    if (role == Qt::FontRole) {
        QFont font("Times", 15, 10, true);
        font.setBold(true);
        font.setItalic(false);
        return font;
    }

    return QVariant{};
}

bool TutorialsTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{

    if (!index.isValid() || role != Qt::EditRole) {
        return false;
    }

    int row = index.row();
    int col = index.column();

    Tutorial& currentTut = this->r.getWlist()[row];

    if (role == Qt::EditRole) {
        switch (col) {
        case 0:
            break;

        case 1:
            break;

        case 2:
            break;

        case 3: {
            std::string likes = value.toString().toStdString();
            r.setLikes(r.getWlist()[row].getTitle(), std::stoi(likes));
            std::cout << r.getWlist()[row].getLikes();
            break;
        }
        }
    }

    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags TutorialsTableModel::flags(const QModelIndex & index) const
{
    int col = index.column();

    if (col == 0 || col == 1)
        return Qt::ItemFlags{};

    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

PictureDelegate::PictureDelegate(QWidget *parent) : QStyledItemDelegate{ parent }
{
}

void PictureDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{

    // show a picture only in the second column; the other columns remain unchanged
    if (index.column() != 1) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    QPixmap pixMap("photo");
    painter->drawPixmap(option.rect, pixMap);
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    // show a picture only in the second column; the other columns remain unchanged
    if (index.column() == 1) {
        return QSize(32, 100);
    }

    return QStyledItemDelegate::sizeHint(option, index);
}
