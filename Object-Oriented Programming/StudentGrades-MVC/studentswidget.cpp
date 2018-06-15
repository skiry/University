#include "studentswidget.h"

StudentsWidget::StudentsWidget(Repository &r, QAbstractItemModel* model, bool isMain, QWidget *parent)
	: QWidget(parent), repo{ r }, isMainTeacher{ isMain }, tableModel{ model }
{
	ui.setupUi(this);
	
	// force the columns to resize, according to the size of the tabe view
	this->ui.studentsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	
	this->ui.studentsTableView->setModel(this->tableModel);
	if (this->isMainTeacher) // the main teacher can see all the list of students
	{
		this->ui.studentsTableView->setSortingEnabled(true);
	}
	else // each regular teacher sees only students from his/her group (group column is hidden)
	{
		this->ui.studentsTableView->hideColumn(1);
	}
}

StudentsWidget::~StudentsWidget()
{

}
