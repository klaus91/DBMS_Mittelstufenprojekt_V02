#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "MainWindow instanziiert...";
    ui->setupUi(this);

    m_exportDialog = new ExportDialog();
    m_newTableDialog = new NewTableDialog();
    m_parserCsv = new ParserCsv();
    m_parserXml = new ParserXml();

    m_anzahlZeilen = 0;
    m_anzahlSpalten = 0;
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
    connect(ui->sucheLineEdit, SIGNAL(textChanged(QString)), this, SLOT(modifyBtns()));

    //MainWindow::eintragSuchen();
    MainWindow::modifyBtns();
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
        if (info.isFile())
        {
            path = info.absoluteFilePath();
            qDebug() << path;
            //            if (path.contains(".csv")) //this query needs all format types when more formats are added (|| .xml)!
            //            {
            //                if (contentWarnung("doubleClick"))
            //                {
            //                }
            getParser(path);
            //            }
        }
    }
    else
    {
        return;
    }
}

/******************************************************************************
 * Methode zum durchsuchen des TableViews
 * m_searchResults enthält alle zur Suche passenden Ergebnisse in einer QStringList
 * Format: flag ob Eintrag schon angezeigt wurde 0 = nein 1 = ja;row;column (0;1;2)
 ******************************************************************************/
void MainWindow::eintragSuchen()
{
    QString temp = ui->sucheLineEdit->text();
    if (temp != "" && m_searchResults.empty())
    {
        goToFirstElement:;
        qDebug() << "eintragSuchen called!";
        qDebug() << temp;
        ui->myTableView->keyboardSearch(temp);

        for (int outerCounter = 0; outerCounter < m_StdItemModel->rowCount(); ++outerCounter)
        {
            for (int innerCounter = 0; innerCounter < m_StdItemModel->columnCount(); ++innerCounter)
            {
                QString bla = m_StdItemModel->data(m_StdItemModel->index(outerCounter,innerCounter), Qt::DisplayRole).toString();
                if (bla.contains(temp))
                {
                    QString row = QString::number(outerCounter);
                    QString column = QString::number(innerCounter);
                    QString result = "0;" + row +  ";" +  column;
                    m_searchResults.append(result);
                }
            }
        }
        qDebug() << "Suchergebnisse: " << m_searchResults.size();
    }

    if (temp != "" && !m_searchResults.empty())
    {
        ui->myTableView->clearSelection();
        /* entleert m_searchResult wenn es einmal durchlaufen wurde (scroll to beginnt von neuem) */
        int size = m_searchResults.size() - 1;
        QString lastValue = m_searchResults.at(size);
        QStringList lastValueCall = lastValue.split(";");
        if (lastValueCall[0] == "1")
        {
                m_searchResults.clear();
                goto goToFirstElement;
        }

        for (int counter = 0; counter < m_searchResults.size(); ++counter)
        {
            QString result = m_searchResults.at(counter);
            QStringList temp = result.split(";");
            if (temp[0] == "0")
            {
                QString rowS = temp[1];
                QString columnS = temp[2];
                int row = rowS.toInt();
                int column = columnS.toInt();
                QModelIndex index = ui->myTableView->model()->index(row, column);
                ui->myTableView->scrollTo(index);
                ui->myTableView->selectionModel()->select(index, QItemSelectionModel::Select);
                ui->myTableView->setStyleSheet("selection-background-color: red");
                QString myString = "1;" + rowS + ";" + columnS;
                qDebug() << "Jetziges Suchergebnis: " << m_searchResults.at(counter);
                m_searchResults.replace(counter, myString);
                qDebug() << "Flag gesetzt: " << m_searchResults.at(counter);

                goto stop;
            }
        }
    }
    stop:;
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

/******************************************************************************
 * Methode zum Initialisieren des Parsers
 ******************************************************************************/
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
            m_tableLoaded = true;
            modifyBtns();
        }
        else if (path.contains(".xml"))
        {
            m_parserXml = new ParserXml();
            m_parserXml->loadTable(path);
            qDebug() << "Imported File is a .xml File!";
            m_parserXml->~ParserXml();


            qDebug() << "Doppelklick auf XML-Datei! Fortsetzung folgt... ;-)";

//            Stuerzt momentan noch beim initialen Aufrufen einer XML-Datei ab. Vermutlich sind noch diverse Abhaengigkeiten nicht
//            beruecksichtigt worden.

            qDebug() << "Doppelklick auf XML-Datei!";

        }
    }
    else
    {
        return;
    }
    if(!m_table.length() == 0)
    {
        showTable();
    }
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
    //    if (contentWarnung("neueTabelle"))
    //    {
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
        m_tableLoaded = true;
        modifyBtns();
    }

    else
    {
        return;
    }
    //    }
}

void MainWindow::tabelleLoeschen()
{
    if (contentWarnung("tabelleLeeren"))
    {
        qDebug() << "Tabelle loeschen clicked!";

        if(m_anzahlZeilen != 0)
        {
            for (int outerCounter = 0; outerCounter < m_table.length(); ++outerCounter)
            {
                for (int innerCounter = 0; innerCounter < m_table[outerCounter].length(); ++innerCounter)
                {
                    m_table[outerCounter][innerCounter] = "";
                }
            }
            showTable();
        }
    }
    else
    {
        return;
    }
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
    if (contentWarnung("zeile"))
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
    else
    {
        return;
    }
}

void MainWindow::spalteLoeschen()
{     
    if (contentWarnung("spalte"))
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
    else
    {
        return;
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
 * Methode um Tabelle exporteiren, neue Zeile / Spalte, loesche Zeile / Spalte und
 * Suche Buttons zu aktivieren wenn eine Tabelle in myTableView vorhanden ist
 ******************************************************************************/
void MainWindow::modifyBtns()
{
    if (m_tableLoaded == false)
    {
        ui->exportiereTabelleButton->setEnabled(false);
        ui->loescheSpalteButton->setEnabled(false);
        ui->loescheZeileButton->setEnabled(false);
        ui->neueSpalteButton->setEnabled(false);
        ui->neueZeileButton->setEnabled(false);
        if (ui->sucheLineEdit->text() == "")
        {
            ui->sucheButton->setEnabled(false);
            m_searchResults.clear();
        }
    }
    else
    {
        ui->exportiereTabelleButton->setEnabled(true);
        ui->loescheSpalteButton->setEnabled(true);
        ui->loescheZeileButton->setEnabled(true);
        ui->neueSpalteButton->setEnabled(true);
        ui->neueZeileButton->setEnabled(true);
        if (ui->sucheLineEdit->text() != "")
        {
            ui->sucheButton->setEnabled(true);
            m_searchResults.clear();
        }
        else if (ui->sucheLineEdit->text() == "")
        {
            ui->sucheButton->setEnabled(false);
            m_searchResults.clear();
        }
    }
}

/******************************************************************************
 * Methode um Warnung zu oeffnen wenn sich inder zu löschenden Tabelle, Spalte
 * oder Zeile Daten befinden
 ******************************************************************************/
bool MainWindow::contentWarnung(QString caller)
{
    QString callerMessage = "";

    for (int outerCounter = 0; outerCounter < m_StdItemModel->rowCount(); ++outerCounter)
    {
        for (int innerCounter = 0; innerCounter < m_StdItemModel->columnCount(); ++innerCounter)
        {
            qDebug() << "CONTENT: " << outerCounter << innerCounter << m_StdItemModel->data(m_StdItemModel->index(outerCounter,innerCounter), Qt::DisplayRole).toString();
            if (m_StdItemModel->data(m_StdItemModel->index(outerCounter,innerCounter), Qt::DisplayRole).toString() != "")
            {
                goto callerQuery;
            }
            else
            {
                return true;
            }
        }
    }

callerQuery:
    if (caller != "")
    {
        if (caller == "zeile")
        {
            QString temp = m_StdItemModel->data(m_StdItemModel->index(m_StdItemModel->rowCount() - 1, 0), Qt::DisplayRole).toString();
            qDebug() << "innerCONTENT: " << m_StdItemModel->rowCount() << "0" << temp;
            if (temp != "")
            {
                callerMessage = "Die zu löschende Zeile enthält Daten. Zeile wirklich löschen?";
            }
            else
            {
                return true;
            }
        }
        else if (caller == "spalte")
        {
            QString temp = m_StdItemModel->data(m_StdItemModel->index(0, m_StdItemModel->columnCount() - 1), Qt::DisplayRole).toString();
            qDebug() << "innerCONTENT: " << m_StdItemModel->rowCount() << "0" << temp;
            if (temp != "")
            {
                callerMessage = "Die zu löschende Spalte enthält Daten. Spalte wirklich löschen?";
            }
            else
            {
                return true;
            }
        }
        else if (caller == "tabelleLeeren")
        {
            callerMessage = "Die Tabelle enthält Daten. Tabelle wirklich leeren?";
        }
        else if (caller == "neueTabelle")
        {
            callerMessage = "Die Tabelle enthält Daten. Trotzdem neue Tabelle anlegen?";
        }
        else if (caller == "doubleClick")
        {
            callerMessage = "Die Tabelle enthält Daten. Trotzdem neue Tabelle laden?";
        }
        else
        {
            qDebug() << "Error: contentWarnung called with unknown String!";
            return false;
        }

        QMessageBox::StandardButton antwort;
        antwort = QMessageBox::warning(this,"Warnung vor Datenverlust!", callerMessage,
                                       QMessageBox::Ok | QMessageBox::Abort);
        if (antwort == QMessageBox::Ok)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
