#ifndef STUDENTGRADES_H
#define STUDENTGRADES_H

#include <QtWidgets/QMainWindow>
#include "ui_studentgrades.h"

class StudentGrades : public QMainWindow
{
	Q_OBJECT

public:
	StudentGrades(QWidget *parent = 0);
	~StudentGrades();

private:
	Ui::StudentGradesClass ui;
};

#endif // STUDENTGRADES_H
