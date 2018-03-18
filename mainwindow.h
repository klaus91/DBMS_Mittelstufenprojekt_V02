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
#include "ui_mainwindow.h"
#include "datenverwaltung.h"
#include "exportdialog.h"
#include "parser.h"
#include "parsercsv.h"
#include "newtabledialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void showDirectory();
    void showTable();

    QList<QStringList>  m_table;
    ParserCsv           *m_parserCsv;

//    QList<QStringList> getMemberTable(){return m_table;}


//    ParserCsv getMemberParser(){return m_parserCsv;}

    ~MainWindow();

public slots:
    void doubleclickEvent();
    void eintragSuchen();
    void tabelleAnlegen();
    void tabelleLoeschen();
    void zeileAnlegen();
    void spalteAnlegen();
    void zeileLoeschen();
    void spalteLoeschen();
    void getParser(QString path);
    //void updateTable(const QModelIndex& topLeft, const QModelIndex& bottomRight);

private slots:
    void callExportDlg();

private:
    Ui::MainWindow      *ui;
//    Datenverwaltung     *m_datenverwaltung;
    ExportDialog        *m_exportDialog;
    NewTableDialog      *m_newTableDialog;
    QFileSystemModel    *m_FSystemModel;
    QStandardItemModel  *m_StdItemModel;

    int                 m_anzahlZeilen = 0;
    int                 m_anzahlSpalten = 0;



};

#endif // MAINWINDOW_H
