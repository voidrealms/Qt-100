/*
* CommandRequest
* Holds data about the command request
*
* Bryan Cairns - 2011
* All rights reserved.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef COMMANDRESPONSE_H
#define COMMANDRESPONSE_H

#include <QObject>
#include <QString>
#include <QDomDocument>
#include <QDebug>
#include "commandrequest.h"

class CommandResponse : public QObject
{
    Q_OBJECT
public:
    explicit CommandResponse(QObject *parent = 0);
    
    /*!
    * Gets the From variable, where the request originated from
    */
    QString From();

    /*!
    * Sets the From variable, where the request originated from
    * @param Data the data to set the variable to
    */
    void SetFrom(QString Data);

    /*!
    * Gets the Source variable, where the response originated from
    */
    QString Source();

    /*!
    * Sets the Source variable, where the response originated from
    * @param Data the data to set the variable to
    */
    void SetSource(QString Data);

    /*!
    * Gets the Status variable
    */
    QString Status();

    /*!
    * Sets the Status variable
    * @param Data the data to set the variable to
    */
    void SetStatus(QString Data);

    /*!
    * Gets the Command variable
    */
    QString Command();

    /*!
    * Sets the Command variable
    * @param Data the data to set the variable to
    */
    void SetCommand(QString Data);

    /*!
    * Gets the ResponseData variable
    */
    QStringList ResponseData();

    /*!
    * Sets the ResponseData variable
    * @param Data the data to set the variable to
    */
    void SetResponseData(QString Data);

    /*!
    * Loads the class from a request object
    * @param Request the request to load from
    */
    void FromRequest(CommandRequest &Request);

    /*!
    * Generates an XML response
    */
    QString ToXML();

    /*!
    * Generates a string response
    */
    QString ToString();

signals:

public slots:


private:
    //! The mFrom variable contains where the request orginally came from
    QString mFrom;

    //! The mSource variable contains where the response came from, this can be this prgram or a plugin
    QString mSource;

    //! The mStatus variable contains the command status
    QString mStatus;

    //! The mCommand variable contains the command
    QString mCommand;

    //! The mResponseData variable contains the response data
    QString mResponseData;

    /*!
    * Returns a QDomElement
    * @param Document the document to create from
    * @param Name the name of the node
    * @param Text the text of the node
    */
    QDomElement MakeNode(QDomDocument Document,QString Name, QString Text);
    
};

#endif // COMMANDRESPONSE_H
