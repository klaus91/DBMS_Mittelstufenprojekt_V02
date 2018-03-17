#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_exportDialog = new ExportDialog();
    m_parserCsv = new ParserCsv();

    connect(ui->sucheButton, SIGNAL(clicked()), this, SLOT(eintragSuchen()));
    connect(ui->neueTabelleButton, SIGNAL(clicked()), this, SLOT(tabelleAnlegen()));
    connect(ui->loescheTabelleButton, SIGNAL(clicked()), this, SLOT(tabelleLoeschen()));
    connect(ui->neueZeileButton, SIGNAL(clicked()), this, SLOT(zeileAnlegen()));
    connect(ui->neueSpalteButton, SIGNAL(clicked()), this, SLOT(spalteAnlegen()));
    connect(ui->loescheZeileButton, SIGNAL(clicked()), this, SLOT(zeileLoeschen()));
    connect(ui->loescheSpalteButton, SIGNAL(clicked()), this, SLOT(spalteLoeschen()));
    connect(ui->exportiereTabelleButton,SIGNAL(clicked()), this, SLOT(callExportDlg()));
    connect(ui->myTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleclickEvent()));
    connect(ui->sucheLineEdit, SIGNAL(textChanged(QString)), this, SLOT(eintragSuchen()));


    MainWindow::eintragSuchen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/******************************************************************************
 * Funktion zum oeffnen des ExportDialogs zwecks exportieren eines Files mit
 * Daten des tableView von MainWindow, aufgerufen durch Tabelle exportieren Btn
 * und Aufruf des entsprechenden Parser, abhäbing vom gewählten Format
 ******************************************************************************/
void MainWindow::callExportDlg()
{
    m_exportDialog->showExportDialog();
    //TODO Hier noch auf den Rückgabewert der exec() methode in showexportdialog überprüfung, bei abbruch muss auch hier abgebrochen werden
    if (true)
    {
        qDebug() << "Path and Filename from ExportDialog: " << m_exportDialog->getValue();
        QString pathAndName = m_exportDialog->getValue();
        QStringList qslPathAndName = pathAndName.split(";");
        qDebug() << qslPathAndName;

        //TODO abfrage zur Unterscheidung der verschiedenen Parser

        if (qslPathAndName[2] == ".csv")
        {
            m_parserCsv = new ParserCsv();
            m_parserCsv->saveTable(qslPathAndName[0], qslPathAndName[1], qslPathAndName[2], m_table);
            m_parserCsv->~ParserCsv();
        }
        //else if z.B. .xml
    }
}

/******************************************************************************
 * Funktion um CSV-Dateien im TreeView per Doppelklick zu oeffnen und
 * anzuzeigen
 ******************************************************************************/
void MainWindow::doubleclickEvent()
{
    QModelIndex index = ui->myTreeView->currentIndex();
    QString path;
    QFileInfo info = QFileInfo();
    if (index.isValid())
    {
        info = m_model->fileInfo(index);
        path = info.absoluteFilePath();
        qDebug() << path;
    }

    if (path.contains(".csv"))
    {
        m_parserCsv->loadTable(path);
        showTable(path);
    }
}

/******************************************************************************
 * Funktion zum aktivieren des Suche Buttons sowie
 * zum filtern des Treeviews (Filter -> QSortFilterProxy?!)
 ******************************************************************************/
void MainWindow::eintragSuchen()
{
    if (ui->sucheLineEdit->text() != "")
    {
        ui->sucheButton->setEnabled(true);
        qDebug() << "eintragSuchen called!/n";
        qDebug() << ui->sucheLineEdit->text();
    }
    else
    {
        ui->sucheButton->setEnabled(false);
    }
}

/******************************************************************************
 * Funktion zum Anzeigen des Verzeichnisbaums in Form eines TreeViews
 ******************************************************************************/
void MainWindow::showDirectory()
{
    QFileSystemModel *m_model = new QFileSystemModel;

    QString mPath = "C:/";

    m_model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    m_model->setRootPath(mPath);
    m_model->setReadOnly(true);

    ui->myTreeView->setModel(m_model);
}

/******************************************************************************
 * Funktion zum Anzeigen des Inhalts einer Datei im TableView
 ******************************************************************************/
void MainWindow::showTable(QString path)
{
    if (!path.isEmpty())
    {
        if (path.contains(".csv"))
        {
            m_parserCsv = new ParserCsv();
            m_parserCsv->loadTable(path);
            QList<QStringList> temp = m_parserCsv->getMemberTable();
            m_table = temp;
            qDebug() << "Imported File is a .csv File!";
            m_parserCsv->~ParserCsv();
        }

        int anzahlZeilen = m_table.count();
        int anzahlSpalten = m_table[0].count();

        QStandardItemModel *m_model = new QStandardItemModel(anzahlZeilen - 1, anzahlSpalten, this);

        for(int i = 0; i < anzahlSpalten; ++i)
        {
            m_model->setHorizontalHeaderItem(i, new QStandardItem(m_table[0][i]));
        }

        for (int outerCounter = 1; outerCounter < anzahlZeilen; ++outerCounter)
        {
            for (int innerCounter = 0; innerCounter < anzahlSpalten; ++innerCounter)
            {
                m_model->setItem(outerCounter - 1, innerCounter, new QStandardItem (m_table[outerCounter][innerCounter]));
            }
        }
        ui->myTableView->setModel(m_model);
    }
}

void MainWindow::tabelleAnlegen()
{
    qDebug() << "Tabelle anlegen clicked!";
}

void MainWindow::tabelleLoeschen()
{
    qDebug() << "Tabelle loeschen clicked!";
}

void MainWindow::zeileAnlegen()
{
    qDebug() << "Zeile anlegen clicked!";

    //   int anzahlZeilen;

    //  anzahlZeilen = MainWindow::m_model->rowCount()
    //    MainWindow::m_model->

    //  qDebug()
}

void MainWindow::spalteAnlegen()
{
    qDebug() << "Spalte anlegen clicked!";
}

void MainWindow::zeileLoeschen()
{
    qDebug() << "Zeile loeschen clicked!";
}

void MainWindow::spalteLoeschen()
{
    qDebug() << "Spalte loeschen clicked!";
}
