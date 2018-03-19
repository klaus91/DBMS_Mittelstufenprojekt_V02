#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "MainWindow instanziiert...";
    ui->setupUi(this);

    m_exportDialog = new ExportDialog();
    m_newTableDialog = new NewTableDialog();
    m_parserCsv = new ParserCsv();
    //    m_StdItemModel = new QStandardItemModel(0, 0, this);  //<- für den auskommentierten connect...
    //    ui->myTableView->setModel(m_StdItemModel);

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


    //    CONNECT um value change in TableView zu registrieren und m_table mit diesen Werten zu updaten....
    //    connect(ui->myTableView->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this,
    //                SLOT(updateTable(const QModelIndex&, const QModelIndex&)));


    MainWindow::eintragSuchen();
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "MainWindow zerstoert...";
}

/******************************************************************************
 * Methode zum oeffnen des ExportDialogs zwecks exportieren eines Files mit
 * Daten des tableView von MainWindow, aufgerufen durch Tabelle exportieren Btn
 * und Aufruf des entsprechenden Parser, abhäbing vom gewählten Format
 ******************************************************************************/
void MainWindow::callExportDlg()
{
    m_exportDialog->showExportDialog();



    if (m_exportDialog->m_dialogCompleted == true)
    {
        updateTable();
        qDebug() << "Path and Filename from ExportDialog: " << m_exportDialog->getValue();
        QString pathAndName = m_exportDialog->getValue();
        QStringList qslPathAndName = pathAndName.split(";");
        qDebug() << qslPathAndName;

        if (qslPathAndName[2] == ".csv")
        {
            m_parserCsv = new ParserCsv();
            m_parserCsv->saveTable(qslPathAndName[0], qslPathAndName[1], qslPathAndName[2], m_table);
            m_parserCsv->~ParserCsv();
        }
        //else if (z.B. .xml)
    }
    else
    {
        return;
    }
}

/******************************************************************************
 * Methode um CSV-Dateien im TreeView per Doppelklick zu oeffnen und
 * anzuzeigen
 ******************************************************************************/
void MainWindow::doubleclickEvent()
{
    QModelIndex index = ui->myTreeView->currentIndex();
    QString path;
    QFileInfo info = QFileInfo();
    if (index.isValid())
    {
        info = m_FSystemModel->fileInfo(index);
        path = info.absoluteFilePath();
        qDebug() << path;
        if (path.contains(".csv")) //this query needs all format types when more formats are added (|| .xml)!
        {
            getParser(path);
        }
    }
    else
    {
        return;
    }
}

/******************************************************************************
 * Methode zum aktivieren des Suche Buttons sowie
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
 * Methode zum Anzeigen des Verzeichnisbaums in Form eines TreeViews
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

void MainWindow::getParser(QString path)
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
    }
    else
    {
        return;
    }
    showTable();
}

/******************************************************************************
 * Methode zum Anzeigen des Inhalts einer Datei im TableView
 ******************************************************************************/
void MainWindow::showTable()
{
    if (m_table[0].length() == 0)
    {
        return;
    }
    else
    {
        int anzahlZeilen = m_table.count();
        int anzahlSpalten = m_table[0].count();

        m_anzahlZeilen = anzahlZeilen;
        m_anzahlSpalten = anzahlSpalten;

        m_StdItemModel = new QStandardItemModel(anzahlZeilen, anzahlSpalten, this);

        for (int outerCounter = 0; outerCounter < anzahlZeilen; ++outerCounter)
        {
            for (int innerCounter = 0; innerCounter < anzahlSpalten; ++innerCounter)
            {
                m_StdItemModel->setItem(outerCounter, innerCounter, new QStandardItem (m_table[outerCounter][innerCounter]));
            }
        }
        ui->myTableView->setModel(m_StdItemModel);
    }
}

/******************************************************************************
 * Methode zum Aufrufen des NewTableDialog und zum Erzeugen einer neuen
 * Tabelle im TableView mit den Eingaben aus dem NewTableDialog
 ******************************************************************************/
void MainWindow::tabelleAnlegen()
{
    qDebug() << "Tabelle anlegen clicked!";
    m_newTableDialog->showNewTableDialog();
    if (m_newTableDialog->m_dialogCompleted == true)
    {
        QString rcCount = m_newTableDialog->getValue();
        QStringList rcCountSL = rcCount.split(";");
        //qDebug() << rcCountSL[0] + " " + rcCountSL[1];
        QString zeileString = rcCountSL[0];
        QString spalteString = rcCountSL[1];
        //qDebug() << zeileString + " und " + spalteString;

        const int anzahlSpalten = spalteString.toInt();
        const int anzahlZeilen = zeileString.toInt();

        qDebug() << "Zeilen: " << anzahlZeilen;
        qDebug() << "Spalten: " << anzahlSpalten;

        QList<QStringList> list;
        QString temp = "";
        m_StdItemModel = new QStandardItemModel(anzahlZeilen - 1, anzahlSpalten, this);

        // macht aus m_table eine QList of QStringList aus leeren QStrings
        for (int outerCounter = 0; outerCounter < anzahlZeilen; ++outerCounter)
        {
            QStringList sList;
            for (int innerCounter = 0; innerCounter < anzahlSpalten; ++innerCounter)
            {
                m_StdItemModel->setItem(outerCounter, innerCounter, new QStandardItem (""));
                sList.append(temp);
            }
            list.append(sList);
        }
        m_table = list;

        showTable();

        m_anzahlZeilen = anzahlZeilen;
        m_anzahlSpalten = anzahlSpalten;
    }
    else
    {
        return;
    }
}

void MainWindow::tabelleLoeschen()
{
    qDebug() << "Tabelle loeschen clicked!";
}

void MainWindow::zeileAnlegen()
{
    qDebug() << "Zeile anlegen clicked!";
    qDebug() << "m_anzahlZeilen before method = " << m_anzahlZeilen;

    QStringList newLine;

    if (m_anzahlZeilen != 0 || m_anzahlSpalten != 0)
    {
        for (int i = 0; i < m_anzahlSpalten; ++i)
        {
            newLine.append("");
        }
        m_table.append(newLine);
        showTable();
        qDebug() << "m_anzahlZeilen after method = " << m_anzahlZeilen;
    }
    else
    {
        qDebug() << "Fehler! Keine Tabelle angelegt.";
    }
}

void MainWindow::spalteAnlegen()
{
    qDebug() << "Spalte anlegen clicked!";

    if(m_anzahlZeilen != 0 || m_anzahlSpalten != 0)
    {
        for (int i = 0; i < m_anzahlZeilen; ++i)
        {
            m_table[i].append("");
        }
        showTable();
    }
    else
    {
        qDebug() << "Fehler! Keine Tabelle angelegt.";
    }
}

void MainWindow::zeileLoeschen()
{
    qDebug() << "Zeile loeschen clicked!";
    qDebug() << "m_anzahlZeilen before method = " << m_anzahlZeilen;

    if(m_anzahlZeilen > 1)
    {
        m_table.removeLast();
        showTable();
        qDebug() << "m_anzahlZeilen after method = " << m_anzahlZeilen;
    }
    else
    {
        qDebug() << "Fehler! Es muss mindestens eine Zeile vorhanden sein.";
    }
}

void MainWindow::spalteLoeschen()
{
    qDebug() << "Spalte loeschen clicked!";

    if(m_anzahlSpalten > 1)
    {
        for(int i = 0; i < m_table.length(); ++i)
        {
            m_table[i].removeLast();
            showTable();
        }
    }
    else
    {
        qDebug() << "Fehler! Es muss mindestens eine Spalte vorhanden sein.";
    }
}

/******************************************************************************
 * Methode um bei Export einer Tabelle m_table mit den Werten von myTableView
 * abzugleichen und ggf. um diese Werte zu erweitern
 ******************************************************************************/
void MainWindow::updateTable()
{
    qDebug() << "updateTable called!!";

    QString temp = "";
    QList<QStringList> list;

    for (int outerCounter = 0; outerCounter < m_StdItemModel->rowCount(); ++outerCounter)
    {
        QStringList sList;
        for (int innerCounter = 0; innerCounter < m_StdItemModel->columnCount(); ++innerCounter)
        {
            temp = m_StdItemModel->data(m_StdItemModel->index(outerCounter,innerCounter), Qt::DisplayRole).toString();
            sList.append(temp);
            qDebug() << sList << "\n";
        }
        list.append(sList);
    }
    m_table = list;
}

/******************************************************************************
 * Methode um den Tabelle exportieren Btn zu deaktivieren sollte keine Tabelle
 * in myTableView vorhanden sein
 ******************************************************************************/
//void MainWindow::disableExportBtn()
//{
//    if (m_StdItemModel->columnCount() < 1)
//    {
//        ui->exportiereTabelleButton->setEnabled(false);
//    }
//    else
//    {
//        ui->exportiereTabelleButton->setEnabled(true);
//    }
//}
