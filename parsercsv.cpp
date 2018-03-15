#include "ParserCsv.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <Qdir>

ParserCsv::ParserCsv()
{
    //    Constructor
}

void ParserCsv::getTable(QString path)
{
    qDebug() << "getTable() called";
    ParserCsv::openFile(path);
}

void ParserCsv::saveTable(QString path, QString name, QString format)
{
    qDebug() << "saveTable called with: " << path + name + format;
    writeFile(path, name, format);
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

bool ParserCsv::writeFile(QString path, QString name, QString format)
{
    if (path != "")
    {
        qDebug() << "writeFile called with: " << path + name + format;
        QDir dir;
        QFile file(path + name + format);

        if (!dir.exists(path))
        {
            dir.mkpath(path);
            qDebug() << "New directory created.";
            if (file.open(QIODevice::ReadWrite))
                {
                    qDebug()<<"New file created.";
                }
        }
        else
        {
            if (file.open(QIODevice::ReadWrite))
                {
                    qDebug()<<"New file created.";
                }
        }


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
