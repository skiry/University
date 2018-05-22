#include "mainwindow.h"
#include "firstpage.h"
#include <QApplication>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FirstPage fP{};
	/*Repository myRepo = Repository{};
	FilePlaylist* p = new CSVPlaylist{ "WatchList.CSV" };
	Controller ctrl = Controller{ myRepo, p };
	MainWindow w{ ctrl };*/
	// w.show();

	return a.exec();
}
