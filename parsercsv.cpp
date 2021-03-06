#include "ParserCsv.h"

ParserCsv::ParserCsv()
{
    //    Constructor
    qDebug() << "ParserCsv() instanziiert...";
}

ParserCsv::~ParserCsv()
{
    qDebug() << "ParserCsv() zerstoert...";
    //    Destructor
}

void ParserCsv::loadTable(QString path)
{
    qDebug() << "getTable() called";
    openFile(path);
}

//void ParserCsv::saveTable(QString path, QString name, QString format, const QList<QStringList> table)
//{
//    qDebug() << "saveTable called with: " << path + name + format;
//    createFile(path, name, format, table);
//}

void ParserCsv::saveTable(QString fileName, const QList<QStringList> table)
{
    createFile(fileName, table);
}

/******************************************************************************
 * Methode zum oeffnen eines Files mit dem Path aus loadTable
 ******************************************************************************/
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

/******************************************************************************
 * Methode zum einlesen eines .csv Files das mit openFile geöffnet wurde
 ******************************************************************************/
QList<QStringList> ParserCsv::readFile(QFile &file)
{
    qDebug() << "leseDatei called";

    QTextStream in(&file);

    QList<QStringList> lines;

    while (!in.atEnd())
    {
//        QString line = in.readLine();

        QStringList columns(in.readLine().split(";", QString::KeepEmptyParts));
        lines.append(columns);

//        if(line.contains(";;"))
//        {
//            qDebug() << "Fehler! Datei nicht kompatibel.";
//            file.close();
//            break;
//        }
//        else if(line.contains(";"))
//        {
//            QStringList columns(line.split(";", QString::SkipEmptyParts));
//            lines.append(columns);
//        }
    }
    file.close();
    return lines;
}

/******************************************************************************
 * Methode zum Erzeugen (oder Ueberschreiben) eines Files und gegebenenfalls
 * Paths mit den Angaben aus dem ExportDialog
 ******************************************************************************/
//bool ParserCsv::createFile(QString path, QString name, QString format, const QList<QStringList> table)
//{
//    if (path != "")
//    {
//        qDebug() << "createFile called with: " << path + name + format;
//        QDir dir;
//        QFile file(path + name + format);

//        if (!dir.exists(path))
//        {
//            dir.mkpath(path);
//            qDebug() << "New directory created.";

//            if (file.open(QIODevice::ReadWrite))
//            {
//                qDebug()<<"New file created.";
//                writeFile(file, table);
//            }
//        }
//        else
//        {
//            if (!file.exists())
//            {
//                file.open(QIODevice::ReadWrite);
//                qDebug()<<"New file created.";
//                writeFile(file, table);
//            }
//            else
//            {
//                file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
//                qDebug()<<"Existing file overwritten.";
//                writeFile(file, table);
//            }
//        }
//        return true;
//    }
//    else
//    {
//        qDebug() << "Error: incorrect filepath and/or filename!";
//        return false;
//    }
//}

void ParserCsv::createFile(QString fileName, const QList<QStringList> table)
{
    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            //            int ret = QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
        writeFile(file, table);
    }
}

/******************************************************************************
 * Methode zum Beschreiben des in createFile erzeugten Files mit den Daten aus
 * m_table von MainWindow
 ******************************************************************************/
bool ParserCsv::writeFile(QFile &file, const QList<QStringList> table)
{
    qDebug() << "writeFile called.";
    QTextStream out(&file);

    if (file.isOpen())
    {
        qDebug() << "Number of columns in table is: " << table.length();
        qDebug() << "Number of rows in table is: " << table[0].length();

        for(int i = 0; i < table.length(); ++i)
        {
            for (int innerCounter = 0; innerCounter < table[i].length(); ++innerCounter)
            {
                out << table[i][innerCounter] << ";";
            }
            out << "\n";
        }

        //        m_table

        file.close();
    }
    return true;
}

bool ParserCsv::closeFile()         //noch nötig?
{
    return true;
}
