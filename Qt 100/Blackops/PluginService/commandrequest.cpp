#include "commandrequest.h"

CommandRequest::CommandRequest(QObject *parent) :
    QObject(parent)
{

}

QString CommandRequest::From()
{
    return mFrom;
}

void CommandRequest::SetFrom(QString Data)
{
    mFrom = Data;
}

QString CommandRequest::Command()
{
    return mCommand;
}

void CommandRequest::SetCommand(QString Data)
{
    mCommand = Data;
}

QStringList CommandRequest::Args()
{
    return mArgs;
}

void CommandRequest::SetArgs(QStringList Data)
{
    mArgs = Data;
}

bool CommandRequest::FromXML(QString Data)
{
    try
    {
        QDomDocument document;
        if(document.setContent(Data))
        {
            QDomElement root = document.firstChildElement();

            //Load the From field
            mFrom = GetNodeValue(root,"from");

            //Load the Command field
            mCommand = GetNodeValue(root,"command");

            //Load the arguments
            QDomElement ArgNode = GetNode(root,"arguments");
            QDomNodeList ArgList = ArgNode.elementsByTagName("arg");

            for(int i = 0; i < ArgList.count(); i++)
            {
                if(ArgList.at(0).isElement())
                {
                    QDomElement item = ArgList.at(i).toElement();
                    if(item.hasChildNodes())
                    {
                        QString value = item.firstChild().nodeValue();
                        mArgs.append(value);
                    }
                }
            }
        }

        return true;
    }
    catch(...)
    {
        return false;
    }

}

bool CommandRequest::FromString(QString Data)
{
    try
    {
        mArgs = Data.split(" ");

        if(mArgs.count() > 0)
        {
            mCommand = mArgs.at(0);
            mArgs.removeFirst();
        }

        return true;
    }
    catch(...)
    {
        return false;
    }
}

QDomElement CommandRequest::GetNode(QDomElement Root, QString Name)
{
    QDomElement Node;
    QDomNodeList nodes = Root.elementsByTagName(Name);

    if(nodes.count() > 0)
    {
        if(nodes.at(0).isElement())
        {
            Node = nodes.at(0).toElement();
        }
    }

    return Node;
}


QString CommandRequest::GetNodeValue(QDomElement Root, QString Name)
{
    QString ret = "";
    QDomElement Node;
    QDomNodeList nodes = Root.elementsByTagName(Name);

    if(nodes.count() > 0)
    {
        if(nodes.at(0).isElement())
        {
            Node = nodes.at(0).toElement();

            if(Node.hasChildNodes())
            {
                ret = Node.firstChild().nodeValue();
            }
        }
    }

    return ret;
}
