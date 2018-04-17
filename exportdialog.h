#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include "parsercsv.h"
#include <QDialog>
#include <QDebug>
#include <QString>


namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = 0);
    QString getValue();

    bool    m_dialogCompleted = false;

    ~ExportDialog();


signals:

public slots:
    void showExportDialog();

private slots:
    void abbrechenBtnClicked();
    void namePathChanged();
    void okBtnClicked();

protected:

private:

    Ui::ExportDialog *ui;
    ParserCsv        *m_parserCsv = nullptr;
    QString          m_pathAndFile;
};

#endif // EXPORTDIALOG_H
