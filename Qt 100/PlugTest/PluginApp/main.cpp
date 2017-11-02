#include <QtCore/QCoreApplication>
#include "appclass.h"

AppClass *cApp = NULL;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int ret = 0;

    //Create a new app class and load the plugins
    cApp = new AppClass;
    cApp->LoadAllPlugins();

    //The Qt main event loop
    ret = a.exec();

    //clean up
    delete cApp;
    cApp = NULL;

    return ret;
}
