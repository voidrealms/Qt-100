#ifndef APPCLASS_H
#define APPCLASS_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QPluginLoader>
#include "PluginInterface.h"

class AppClass : public QObject
{
    Q_OBJECT
public:
    explicit AppClass(QObject *parent = 0);

signals:

public slots:
    void LoadAllPlugins();
    void LoadPlugin(QString Filename);

};

#endif // APPCLASS_H
