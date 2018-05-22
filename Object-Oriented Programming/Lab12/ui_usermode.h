/********************************************************************************
** Form generated from reading UI file 'usermode.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMODE_H
#define UI_USERMODE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_userMode
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *userMode)
    {
        if (userMode->objectName().isEmpty())
            userMode->setObjectName(QString::fromUtf8("userMode"));
        userMode->resize(400, 300);
        buttonBox = new QDialogButtonBox(userMode);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(userMode);
        QObject::connect(buttonBox, SIGNAL(accepted()), userMode, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), userMode, SLOT(reject()));

        QMetaObject::connectSlotsByName(userMode);
    } // setupUi

    void retranslateUi(QDialog *userMode)
    {
        userMode->setWindowTitle(QApplication::translate("userMode", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class userMode: public Ui_userMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMODE_H
