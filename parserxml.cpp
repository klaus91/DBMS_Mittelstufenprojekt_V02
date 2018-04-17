#include "parserxml.h"

ParserXml::ParserXml()
{
    qDebug() << "ParserXml instanziiert...";
    //Constructor
}

ParserXml::~ParserXml()
{
    //Destructor
    qDebug() << "ParserXml zerstoert...";
}

void ParserXml::loadTable(QString path)
{
    qDebug() << "getTable() called";
    openFile(path);
    qDebug() << "File opened: " << path;
}

void ParserXml::saveTable(QString path, QString name, QString format, const QList<QStringList> table)
{
    qDebug() << "saveTable called with: " << path + name + format;
    createFile(path, name, format, table);
}

bool ParserXml::openFile(QString path)
{
    QFile file(path);

    if(file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Success: File opened! " << m_table.length();
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

//QList<QStringList> ParserXml::readFile(QFile &file)
//{
//    //TODO
//    qDebug() << "XML readFile called...";

//    QStringList elements;
//    QList<QStringList> lines;
//    QXmlStreamReader in(&file);

//    int i = 0;

//    while(in.readNextStartElement())
//    {
//        QString element = in.readElementText();
//        qDebug() << "XML: Lese Element...";
//        qDebug(qPrintable(element));
//        qDebug() << element;
//        elements.append(element);
//    }

//    return lines;
//}

QList<QStringList> ParserXml::readFile(QFile &file)
{
    //TODO
    qDebug() << "XML readFile called...";

    QStringList elements;
    QList<QStringList> lines;



    QXmlStreamReader xml(&file);

    while(!xml.atEnd() && !xml.hasError())
    {
        if (xml.readNextStartElement())
        {
            qDebug() << "*************************";
            qDebug() << xml.name().toString();
        }
        else
        {
            qDebug() << "No start element found...";
        }










//        QXmlStreamReader::TokenType token = xml.readNext();

//        if(token == QXmlStreamReader::StartDocument)
//        {
//            qDebug() << "token == StartDocument";

//            if(token == QXmlStreamReader::StartElement)
//            {
//                qDebug() << "token == StartElement";

//                if(xml.name() == "persons")
//                {
//                    qDebug() << "Lese Person...";
//                    continue;
//                }
//            }
//        }
    }

    return lines;
}

bool ParserXml::createFile(QString path, QString name, QString format, const QList<QStringList> table)
{
    //TODO
    return true;
}

bool ParserXml::closeFile()
{
    //TODO
    return true;
}

bool ParserXml::writeFile(QFile &file, const QList<QStringList> table)
{
    //TODO
    return true;
}
