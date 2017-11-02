#ifndef TESTER_H
#define TESTER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QStringList>
#include "commandmanager.h"
#include "commandrequest.h"
#include "commandresponse.h"
#include "pluginmanager.h"

class Tester : public QObject
{
    Q_OBJECT
public:
    explicit Tester(QObject *parent = 0);
    
signals:
    
public slots:
    void TestRequest();
    void TestResponse();
    void TestLoad();
    void TestList();
    void TestInstall();
    void TestUninstall();
    void TestStart();
    void TestStop();
    void testCommands();

    void TestExec1();
    void TestExec2();

    void TestUnload();
    void TestStartAll();
    void TestStopAll();
    void TestLoadAll();
    void TestUnloadAll();

    void ResponseReady(CommandResponse &Reponse);
private:
    CommandManager *Manager;
    PluginManager *Plugins;
};

#endif // TESTER_H
