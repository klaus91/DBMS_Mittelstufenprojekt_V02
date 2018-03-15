#ifndef PARSER_H
#define PARSER_H

#include <QList>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>


class Parser
{
public:
    Parser();

    virtual void getTable(QString path) = 0;
    virtual void saveTable(QString pathAndFqName) = 0;

private: // attributes
    QList<QStringList> m_table;

private: // methods
    virtual bool openFile(QString path) = 0;
    virtual QList<QStringList> readFile(QFile &file) = 0;
    virtual bool writeFile(QString pathAndFqName) = 0;
    virtual bool closeFile() = 0;
};

#endif // PARSER_H
