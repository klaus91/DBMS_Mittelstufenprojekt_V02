#ifndef PARSERCSV_H
#define PARSERCSV_H

#include "parser.h"


class ParserCsv : public Parser
{
public:
    ParserCsv();

    QList<QStringList> m_table;

    virtual void getTable(QString path);
    virtual void saveTable(QString path, QString name, QString format);

    QList<QStringList> getMemberTable(){return m_table;}

private:

    virtual bool openFile(QString path);
    virtual QList<QStringList> readFile(QFile &file);
    virtual bool writeFile(QString path, QString name, QString format);
    virtual bool closeFile();

};

#endif // PARSERCSV_H
