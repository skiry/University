/********************************************************************************
** Form generated from reading UI file 'studentswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTSWIDGET_H
#define UI_STUDENTSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudentsWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *studentsTableView;

    void setupUi(QWidget *StudentsWidget)
    {
        if (StudentsWidget->objectName().isEmpty())
            StudentsWidget->setObjectName(QStringLiteral("StudentsWidget"));
        StudentsWidget->resize(554, 300);
        verticalLayout = new QVBoxLayout(StudentsWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        studentsTableView = new QTableView(StudentsWidget);
        studentsTableView->setObjectName(QStringLiteral("studentsTableView"));

        verticalLayout->addWidget(studentsTableView);


        retranslateUi(StudentsWidget);

        QMetaObject::connectSlotsByName(StudentsWidget);
    } // setupUi

    void retranslateUi(QWidget *StudentsWidget)
    {
        StudentsWidget->setWindowTitle(QApplication::translate("StudentsWidget", "StudentsWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StudentsWidget: public Ui_StudentsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTSWIDGET_H
