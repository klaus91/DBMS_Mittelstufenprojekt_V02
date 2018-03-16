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

    ~ExportDialog();

    QString getValue();

signals:

public slots:

    void showExportDialog();
    void abbrechenBtnClicked();
    void namePathChanged();
    void okBtnClicked();

protected:

private:

    Ui::ExportDialog *ui;
    ParserCsv        *m_parserCsv = nullptr;
};

#endif // EXPORTDIALOG_H