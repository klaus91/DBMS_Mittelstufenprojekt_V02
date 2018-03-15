#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QDirModel>
#include <QFileSystemModel>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QString>
#include <QTreeView>
#include <QItemSelectionModel>
#include "ui_mainwindow.h"
#include "datenverwaltung.h"
#include "exportdialog.h"
#include "parser.h"
#include "parsercsv.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void showDirectory();
    void showTable(QString path);

    ~MainWindow();

public slots:
    void doubleclickEvent(QModelIndex);

private:
    Ui::MainWindow      *ui;
    Datenverwaltung     *m_datenverwaltung;
    ExportDialog        *m_exportDialog;
    QFileSystemModel    *m_model;

};

#endif // MAINWINDOW_H
