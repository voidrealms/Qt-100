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

#ifndef COMMANDREQUEST_H
#define COMMANDREQUEST_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDomDocument>
#include <QDebug>

class CommandRequest : public QObject
{
    Q_OBJECT

public:
    explicit CommandRequest(QObject *parent = 0);
    
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
    * Gets the Command variable
    */
    QString Command();

    /*!
    * Sets the Command variable
    * @param Data the data to set the variable to
    */
    void SetCommand(QString Data);

    /*!
    * Gets the Args variable
    */
    QStringList Args();

    /*!
    * Sets the Args variable
    * @param Data the data to set the variable to
    */
    void SetArgs(QStringList Data);

    /*!
    * Loads the class from XML data
    * <commandpacket>
    * <from>From Name</from>
    * <command>Command Here</command>
    * <arguments>
    * <arg>This is argument 1</arg>
    * <arg>This is argument 2</arg>
    * <arg>This is argument 3</arg>
    * </arguments>
    * </commandpacket>
    * @param Data the xml data to load from
    */
    bool FromXML(QString Data);

    /*!
    * Loads the class from a string
    * <command> <arg> <arg> <arg>
    * @param XMLData the xml data to load from
    */
    bool FromString(QString Data);

signals:
    
public slots:
    

private:
     //! The mFrom variable contains where the request came from
    QString mFrom;

     //! The mCommand variable contains the command
    QString mCommand;

     //! The mArgs variable contains a list of arquments
    QStringList mArgs;

    /*!
    * Returns a QDomElement based on the name
    * @param Root the root element
    * @param Name the name of the node ot load
    */
    QDomElement GetNode(QDomElement Root, QString Name);

    /*!
    * Returns a QDomElement based on the name
    * @param Root the root element
    * @param Name the name of the node ot load
    */
    QString GetNodeValue(QDomElement Root, QString Name);

};

#endif // COMMANDREQUEST_H
