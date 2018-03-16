#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    m_datenverwaltung = new Datenverwaltung();
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


void MainWindow::callExportDlg()
{
    m_exportDialog->showExportDialog();
    //TODO Hier noch auf den Rückgabewert der exec() methode in showexportdialog überprüfung, bei abbruch muss auch hier abgebrochen werden
    if (true)
    {
        qDebug() << m_exportDialog->getValue();
        //TODO Hier die Rückgabewerte aus getvalue als parameter verwenden
        m_parserCsv = new ParserCsv();
        m_parserCsv->saveTable("C:/Users/folkerts_k/test/", "TestFilelala", ".csv", m_table);
        delete m_parserCsv;
        qDebug() << "Ich lebe noch";
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
    //    ParserCsv *pCsv = new ParserCsv();
    //QList<QStringList> myTable;

    if (!path.isEmpty())
    {
        if (path.contains(".csv"))
        {
            m_parserCsv = new ParserCsv();
            m_parserCsv->loadTable(path);
            QList<QStringList> temp = m_parserCsv->getMemberTable();
            m_table = temp;
            qDebug() << "Bla";
            m_parserCsv->~ParserCsv();
        }

        //        myTable = dwv->ge
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
