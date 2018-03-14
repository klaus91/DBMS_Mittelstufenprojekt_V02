#include "ParserCsv.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

ParserCsv::ParserCsv()
{
//    Constructor
}

void ParserCsv::getTable(QString path)
{
    qDebug() << "getTable() called";
    ParserCsv::openFile(path);
}

void ParserCsv::saveTable(QString path)
{

}

bool ParserCsv::openFile(QString path)
{
    QFile file(path);

    if(file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Success: File opened!";
        m_table = readFile(file);
    }
    else
    {
        qDebug() << "Error: File not found!";
        return false;
    }
    file.close();

    return true;
}

QList<QStringList> ParserCsv::readFile(QFile &file)
{
    qDebug() << "leseDatei called";

    QTextStream in(&file);

    QList<QStringList> lines;

    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (line.contains(";"))             // TODO mit ; getrennte Elemente trennen und in String[][] Schreiben ?!
        {
            QStringList columns(line.split(";", QString::SkipEmptyParts));
            lines.append(columns);

//            qDebug() << "lines.count() = " << lines.count();
//            qDebug() << "columns = " << columns;
//            qDebug() << "columns[0] = " << columns[0];
//            qDebug() << "columns.count() = " << columns.count();
        }
    }
    return lines;
}

bool ParserCsv::writeFile()
{
    return true;
}

bool ParserCsv::closeFile()
{
    return true;
}
