#include "StudentsTableModel.h"
#include <qbrush.h>
#include <qcolor.h>

StudentsTableModel::~StudentsTableModel()
{
}

int StudentsTableModel::rowCount(const QModelIndex & parent) const
{
	return this->repo.getSize();
}

int StudentsTableModel::columnCount(const QModelIndex & parent) const
{
	return 4;
}

QVariant StudentsTableModel::data(const QModelIndex & index, int role) const
{
	Student currentStudent = this->repo.getStudents()[index.row()];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (index.column())
		{
		case 0:		// first column - name
			return QString::fromStdString(currentStudent.getName());
		case 1:		// second column - group
			return QString::fromStdString(currentStudent.getGroup());
		case 2:		// third column - lab grade
			return QString::number(currentStudent.getLabGrade());
		case 3:		// fourth column - seminar grade
			return QString::number(currentStudent.getSeminarGrade());
		default:
			break;
		}
	}

	return QVariant();
}

QVariant StudentsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Name" };
			case 1:
				return QString{ "Group" };
			case 2:
				return QString{ "Lab grade" };
			case 3:
				return QString{ "Seminar grade" };
			default:
				break;
			}
		}
	}

	return QVariant();
}

bool StudentsTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	int row = index.row();
	int col = index.column();

	Student& currentStudent = this->repo.getStudents()[index.row()];

	if (role == Qt::EditRole)
	{
		switch (col)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
		{
			std::string labGrade{ value.toString().toStdString() };
			currentStudent.setLabGrade(std::stod(labGrade));
			break;
		}
		case 3:
		{
			std::string seminarGrade{ value.toString().toStdString() };
			currentStudent.setSeminarGrade(std::stod(seminarGrade));
		}
		}
	}

	emit dataChanged(index, index);
	return true;
}

Qt::ItemFlags StudentsTableModel::flags(const QModelIndex & index) const
{
	int col = index.column();
	if (col == 0 || col == 1)
		return Qt::ItemFlags{};
	return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}
