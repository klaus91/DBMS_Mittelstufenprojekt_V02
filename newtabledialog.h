#ifndef NEWTABLEDIALOG_H
#define NEWTABLEDIALOG_H

#include <QDialog>
#include <QString>
#include <QDebug>

namespace Ui {
class NewTableDialog;
}

class NewTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTableDialog(QWidget *parent = 0);
    QString getValue();

    bool    m_dialogCompleted = false;

    ~NewTableDialog();


signals:


public slots:
    void showNewTableDialog();
    void abbrechenBtnClicked();
    void rowColumnsChanged();
    void okBtnClicked();


protected:

private:
    Ui::NewTableDialog *ui;
    QString            m_rowColumnsCount;

};

#endif // NEWTABLEDIALOG_H
