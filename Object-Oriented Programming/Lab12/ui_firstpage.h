/********************************************************************************
** Form generated from reading UI file 'firstpage.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTPAGE_H
#define UI_FIRSTPAGE_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_FirstPage
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FirstPage)
    {
        if (FirstPage->objectName().isEmpty())
            FirstPage->setObjectName(QString::fromUtf8("FirstPage"));
        FirstPage->resize(400, 300);
        buttonBox = new QDialogButtonBox(FirstPage);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(FirstPage);
        QObject::connect(buttonBox, SIGNAL(accepted()), FirstPage, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FirstPage, SLOT(reject()));

        QMetaObject::connectSlotsByName(FirstPage);
    } // setupUi

    void retranslateUi(QDialog *FirstPage)
    {
        FirstPage->setWindowTitle(QApplication::translate("FirstPage", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class FirstPage: public Ui_FirstPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTPAGE_H
