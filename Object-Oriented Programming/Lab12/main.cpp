#include "mainwindow.h"
#include <QApplication>
#include "fileplaylist.h"
#include "csvplaylist.h"
#include "repository.h"
#include "controller.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository myRepo = Repository{};
    FilePlaylist* p = new CSVPlaylist{ "WatchList.CSV" };
    Controller ctrl = Controller{ myRepo, p };
    MainWindow w{ ctrl };
   // w.show();

    return a.exec();
}
