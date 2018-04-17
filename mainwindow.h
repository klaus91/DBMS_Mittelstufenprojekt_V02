#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QDirModel>
#include <QFileSystemModel>
#include <QMainWindow>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QString>
#include <QTreeView>
#include <QItemSelectionModel>
#include <QSignalMapper>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "datenverwaltung.h"
#include "exportdialog.h"
#include "parser.h"
#include "parsercsv.h"
#include "parserxml.h"
#include "newtabledialog.h"




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showDirectory();
    void showTable();
    bool contentWarnung(QString caller);

    QList<QStringList>  m_table;
    ParserCsv           *m_parserCsv;
    ParserXml           *m_parserXml;
    bool                m_tableLoaded = false;
    QStringList         m_searchResults;

private:
    Ui::MainWindow      *ui;
    ExportDialog        *m_exportDialog;
    NewTableDialog      *m_newTableDialog;
    QFileSystemModel    *m_FSystemModel;
    QStandardItemModel  *m_StdItemModel;

    int                 m_anzahlZeilen;
    int                 m_anzahlSpalten;
//    QList<QStringList> getMemberTable(){return m_table;}


//    ParserCsv getMemberParser(){return m_parserCsv;}



public slots:
    void getParser(QString path);

//    void updateTable(const QModelIndex&, const QModelIndex&);

private slots:
    void doubleclickEvent();
    void eintragSuchen();
    void tabelleAnlegen();
    void tabelleLoeschen();
    void zeileAnlegen();
    void spalteAnlegen();
    void zeileLoeschen();
    void spalteLoeschen();
    void modifyBtns();
    void updateTable();
    void callExportDlg();
    void openFileDialog();
};

#endif // MAINWINDOW_H
