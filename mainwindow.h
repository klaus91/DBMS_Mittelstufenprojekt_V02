#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QTreeView>
#include <QFileSystemModel>
#include <QDirModel>
#include <QDebug>
#include <QString>
#include <QStandardItemModel>
#include "datenverwaltung.h"
#include "parser.h"
#include "parsercsv.h"
#include "datenverwaltung.h"
#include "exportdialog.h"


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

    ~MainWindow();

public slots:
    void doubleclickEvent(QModelIndex);

private:
    Ui::MainWindow *ui;
    Datenverwaltung     *m_datenverwaltung;
    ExportDialog        *m_exportDialog;
};

#endif // MAINWINDOW_H
