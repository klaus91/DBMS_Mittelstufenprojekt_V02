#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_datenverwaltung = new Datenverwaltung();
    m_exportDialog = new ExportDialog();

    connect(ui->sucheButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(eintragSuchen()));
    connect(ui->neueTabelleButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(tabelleAnlegen()));
    connect(ui->loescheTabelleButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(tabelleLoeschen()));
    connect(ui->neueZeileButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(zeileAnlegen()));
    connect(ui->neueSpalteButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(spalteAnlegen()));
    connect(ui->loescheZeileButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(zeileLoeschen()));
    connect(ui->loescheSpalteButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(spalteLoeschen()));
    connect(ui->exportiereTabelleButton,SIGNAL(clicked()), m_exportDialog, SLOT(showExportDialog()));
    connect(ui->myTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleclickEvent(QModelIndex)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doubleclickEvent(QModelIndex)
{
//    QModelIndexList test = ui->myTreeView->indexAt();
//    qDebug() << "Test " <<
//    qDebug() << "MyTreeview doubleclicked" << test;

//    https://forum.qt.io/topic/30494/solved-get-current-file-path-qtreeview/8
}

/******************************************************************************
 * Funktion zum Anzeigen des Verzeichnisbaums in Form eines TreeViews
 ******************************************************************************/
void MainWindow::showDirectory()
{
    QFileSystemModel *model = new QFileSystemModel;

    QString mPath = "C:/";

    model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    model->setRootPath(mPath);
    model->setReadOnly(true);

    ui->myTreeView->setModel(model);

}

/******************************************************************************
 * Funktion zum Anzeigen des Inhalts einer Datei im TableView
 ******************************************************************************/
void MainWindow::showTable()
{
    ParserCsv *pCsv = new ParserCsv();
    pCsv->getTable("C:/Users/folke/OneDrive/Documents/Versetzungsplan.csv");
    QList<QStringList> myTable = pCsv->getMemberTable();

    int anzahlZeilen = myTable.count();
    int anzahlSpalten = myTable[0].count();

    QStandardItemModel *model = new QStandardItemModel(anzahlZeilen, anzahlSpalten, this);

    for(int i = 0; i < anzahlSpalten; ++i)
    {
        model->setHorizontalHeaderItem(i, new QStandardItem(myTable[0][i]));
    }

    for (int outerCounter = 1; outerCounter < anzahlZeilen; ++outerCounter)
    {
        for (int innerCounter = 0; innerCounter < anzahlSpalten; ++innerCounter)
        {
            model->setItem(outerCounter - 1, innerCounter, new QStandardItem(myTable[outerCounter][innerCounter]));
        }
    }

    ui->myTableView->setModel(model);
}
