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

ParserCsv::~ParserCsv()
{

}

void ParserCsv::loadTable(QString path)
{
    qDebug() << "getTable() called";
    ParserCsv::openFile(path);
}

void ParserCsv::saveTable(QString path, QString name, QString format, const QList<QStringList> table)
{
    qDebug() << "saveTable called with: " << path + name + format;
    createFile(path, name, format, table);
}

bool ParserCsv::openFile(QString path)
{
    QFile file(path);

    if(file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Success: File opened!  " << m_table.length();
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

bool ParserCsv::createFile(QString path, QString name, QString format, const QList<QStringList> table)
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
                writeFile(file, table);
            }
        }
        else
        {
            if (file.open(QIODevice::ReadWrite))
            {
                qDebug()<<"New file created.";
                writeFile(file, table);
            }
        }
        return true;
    }
    else
    {
        qDebug() << "Error: incorrect filepath and/or filename!";
        return false;
    }
}

bool ParserCsv::writeFile(QFile &file, const QList<QStringList> table)
{
    qDebug() << "writeFile called";
    QTextStream out(&file);

    if (file.isOpen())
    {
        qDebug() << "m_table.length() = " << table.length();
        QList<QStringList> temp = getMemberTable();
        //qDebug() << temp.length();

        for(int i = 0; i < table.length(); ++i)
        {
            for (int innerCounter = 0; innerCounter < table.length(); ++innerCounter)
            {
                out << "Test;";
//                out << table.length()[i][innerCounter] << ";";
            }
            out << "\n";
        }

        //        m_table
    }
    return true;
}

bool ParserCsv::closeFile()
{
    return true;
}
