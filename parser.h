#ifndef PARSER_H
#define PARSER_H

#include <QList>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <Qdir>
#include <QMessageBox>


class Parser
{
public:
    Parser();

    virtual void loadTable(QString path) = 0;
    virtual void saveTable(QString fileName, const QList<QStringList> table) = 0;


private: // attributes
    QList<QStringList> m_table;

private: // methods
    virtual bool openFile(QString path) = 0;
    virtual QList<QStringList> readFile(QFile &file) = 0;
    virtual void createFile(QString fileName, const QList<QStringList> table) = 0;
    virtual bool closeFile() = 0;
    virtual bool writeFile(QFile &file, const QList<QStringList> table) = 0;
};

#endif // PARSER_H
