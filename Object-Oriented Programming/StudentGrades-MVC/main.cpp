#include "studentgrades.h"
#include <QtWidgets/QApplication>
#include <studentswidget.h>
#include "StudentsTableModel.h"
#include <QSortFilterProxyModel>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Repository repo{"Students.txt"};
	StudentsTableModel* tableModel = new StudentsTableModel{ repo };
	
	QSortFilterProxyModel* sortModel = new QSortFilterProxyModel{};
	sortModel->setSourceModel(tableModel);
	StudentsWidget mainTeacherWidget{ repo, sortModel, true };
	mainTeacherWidget.setWindowTitle("Main teacher");
	mainTeacherWidget.show();

	QSortFilterProxyModel* filterModel = new QSortFilterProxyModel{};
	filterModel->setSourceModel(tableModel);
	QString filterGroup{ QString::fromStdString("912") };
	filterModel->setFilterRegExp(QRegExp{ filterGroup, Qt::CaseInsensitive, QRegExp::FixedString });
	filterModel->setFilterKeyColumn(1);
	StudentsWidget regularTeacherWidget{ repo, filterModel};
	regularTeacherWidget.setWindowTitle(QString{ "Regular teacher - " } + filterGroup);
	regularTeacherWidget.show();

	return a.exec();
}
