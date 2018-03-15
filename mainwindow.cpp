#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_datenverwaltung = new Datenverwaltung();
    m_exportDialog = new ExportDialog();

    connect(ui->sucheButton, SIGNAL(clicked()), this, SLOT(eintragSuchen()));
    connect(ui->neueTabelleButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(tabelleAnlegen()));
    connect(ui->loescheTabelleButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(tabelleLoeschen()));
    connect(ui->neueZeileButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(zeileAnlegen()));
    connect(ui->neueSpalteButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(spalteAnlegen()));
    connect(ui->loescheZeileButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(zeileLoeschen()));
    connect(ui->loescheSpalteButton, SIGNAL(clicked()), m_datenverwaltung, SLOT(spalteLoeschen()));
    connect(ui->exportiereTabelleButton,SIGNAL(clicked()), m_exportDialog, SLOT(showExportDialog()));
    connect(ui->myTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleclickEvent()));
    connect(ui->sucheLineEdit, SIGNAL(textChanged(QString)), this, SLOT(eintragSuchen()));


    MainWindow::eintragSuchen();
}

MainWindow::~MainWindow()
{
    delete ui;
}


/******************************************************************************
 * Funktion um CSV-Dateien im TreeView per Doppelklick zu oeffnen und
 * anzuzeigen
 *
 * https://forum.qt.io/topic/30494/solved-get-current-file-path-qtreeview/8
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
        ParserCsv *pCsv = new ParserCsv();
        pCsv->getTable(path);
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
    ParserCsv *pCsv = new ParserCsv();
    QList<QStringList> myTable;

    if (!path.isEmpty())
    {
        pCsv->getTable(path);
        myTable = pCsv->getMemberTable();

        int anzahlZeilen = myTable.count();
        int anzahlSpalten = myTable[0].count();

        QStandardItemModel *m_model = new QStandardItemModel(anzahlZeilen - 1, anzahlSpalten, this);

        for(int i = 0; i < anzahlSpalten; ++i)
        {
            m_model->setHorizontalHeaderItem(i, new QStandardItem(myTable[0][i]));
        }

        for (int outerCounter = 1; outerCounter < anzahlZeilen; ++outerCounter)
        {
            for (int innerCounter = 0; innerCounter < anzahlSpalten; ++innerCounter)
            {
                m_model->setItem(outerCounter - 1, innerCounter, new QStandardItem (myTable[outerCounter][innerCounter]));
            }
        }
        ui->myTableView->setModel(m_model);
    }

}
