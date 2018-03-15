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

void ParserCsv::saveTable(QString pathAndFqName)
{
    qDebug() << "saveTable called with: " << pathAndFqName;
    writeFile(pathAndFqName);
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

        if(line.contains(";;"))
        {
            qDebug() << "Fehler! Datei nicht kompatibel.";
            file.close();
            break;
        }
        else if(line.contains(";"))
        {
            QStringList columns(line.split(";", QString::SkipEmptyParts));
            lines.append(columns);
        }
    }
    file.close();
    return lines;
}

bool ParserCsv::writeFile(QString pathAndFqName)
{
    if (pathAndFqName != "")
    {
        qDebug() << "writeFile called with: " << pathAndFqName;
        return true;
    }
    else
    {
        qDebug() << "Error: incorrect filepath and/ or filename!";
        return false;
    }
}

bool ParserCsv::closeFile()
{
    return true;
}
