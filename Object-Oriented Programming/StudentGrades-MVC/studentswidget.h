#ifndef STUDENTSWIDGET_H
#define STUDENTSWIDGET_H

#include <QWidget>
#include "ui_studentswidget.h"
#include "Repository.h"

class StudentsWidget : public QWidget
{
	Q_OBJECT

public:
	StudentsWidget(Repository &r, QAbstractItemModel* model, bool isMain = false, QWidget *parent = 0);
	~StudentsWidget();

private:
	Ui::StudentsWidget ui;
	Repository& repo;

	bool isMainTeacher;	// specifies if this is the widget for the main teacher
	std::string group;  // if the dialog is NOT for the main teacher, show only the specific group
	QAbstractItemModel* tableModel;
};

#endif // STUDENTSWIDGET_H
