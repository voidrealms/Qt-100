#include "commandresponse.h"

CommandResponse::CommandResponse(QObject *parent) :
    QObject(parent)
{
    mFrom = "";
    mSource = "";
    mStatus = "";
    mCommand = "";
    mResponseData = "";
}

QString CommandResponse::From()
{
    return mFrom;
}

void CommandResponse::SetFrom(QString Data)
{
    mFrom = Data;
}

QString CommandResponse::Source()
{
    return mSource;
}

void CommandResponse::SetSource(QString Data)
{
    mSource = Data;
}

QString CommandResponse::Status()
{
    return mStatus;
}

void CommandResponse::SetStatus(QString Data)
{
    mStatus = Data;
}

QString CommandResponse::Command()
{
    return mCommand;
}

void CommandResponse::SetCommand(QString Data)
{
    mCommand = Data;
}

void CommandResponse::SetResponseData(QString Data)
{
    mResponseData = Data;
}

void CommandResponse::FromRequest(CommandRequest &Request)
{
    mFrom = Request.From();
    mCommand = Request.Command();
    mSource = "System";
}

QString CommandResponse::ToXML()
{

    QDomDocument document;
    QDomElement root = document.createElement("commandpacket");

    QDomElement dFrom = MakeNode(document,"From", mFrom);
    root.appendChild(dFrom);

    QDomElement dSource = MakeNode(document,"Source", mSource);
    root.appendChild(dSource);

    QDomElement dStatus = MakeNode(document,"Status", mStatus);
    root.appendChild(dStatus);

    QDomElement dCommand = MakeNode(document,"Command", mCommand);
    root.appendChild(dCommand);

    QDomElement dResponseData = MakeNode(document,"ResponseData", mResponseData);
    root.appendChild(dResponseData);

    document.appendChild(root);


    return document.toString();
}

QString CommandResponse::ToString()
{
    QString value;
    value = mCommand + " " + mStatus + " " + mResponseData;
    return value;
}

QDomElement CommandResponse::MakeNode(QDomDocument Document,QString Name, QString Text)
{
    //From Node
    QDomElement dElement = Document.createElement(Name);
    QDomText mText = Document.createTextNode(Name);
    mText.setNodeValue(Text);
    dElement.appendChild(mText);

    return dElement;
}
