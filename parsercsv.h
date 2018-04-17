#ifndef PARSERCSV_H
#define PARSERCSV_H

#include "parser.h"

class ParserCsv : public Parser
{
public:
    ParserCsv();

    QList<QStringList> m_table;

    QList<QStringList> getMemberTable(){return m_table;}

    virtual void loadTable(QString path);
    virtual void saveTable(QString fileName, const QList<QStringList> table);

    ~ParserCsv();

private:

    virtual bool openFile(QString path);
    virtual QList<QStringList> readFile(QFile &file);
    virtual void createFile(QString file, const QList<QStringList> table);
    virtual bool closeFile();
    virtual bool writeFile(QFile &file, const QList<QStringList> table);

};

#endif // PARSERCSV_H
