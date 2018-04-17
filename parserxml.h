#ifndef PARSERXML_H
#define PARSERXML_H

#include "parser.h"
#include <QXmlStreamReader>

class ParserXml : public Parser
{
public:
    ParserXml();

    QList<QStringList> m_table;
    QList<QStringList> getMemberTable(){return m_table;}

    virtual void loadTable(QString path);
    virtual void saveTable(QString path, QString name, QString format, const QList<QStringList> table);

    ~ParserXml();

private:

    virtual bool openFile(QString path);
    virtual QList<QStringList> readFile(QFile &file);
    virtual bool createFile(QString path, QString name, QString format, const QList<QStringList> table);
    virtual bool closeFile();
    virtual bool writeFile(QFile &file, const QList<QStringList> table);

};

#endif // PARSERXML_H
