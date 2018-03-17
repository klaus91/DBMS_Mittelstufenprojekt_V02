#include "newtabledialog.h"
#include "ui_newtabledialog.h"

NewTableDialog::NewTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTableDialog)
{
    ui->setupUi(this);

    connect(ui->abbrechenButton, SIGNAL(clicked(bool)), this, SLOT(abbrechenBtnClicked()));
    connect(ui->rowCountLineEdit, SIGNAL(textChanged(QString)), this, SLOT(rowColumnsChanged()));
    connect(ui->columnCountLineEdit, SIGNAL(textChanged(QString)), this, SLOT(rowColumnsChanged()));
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(okBtnClicked()));

}

NewTableDialog::~NewTableDialog()
{
    delete ui;
}

/******************************************************************************
 * Methode die von MainWindow aufgerufen wird und den NewTableDialog anzeigt,
 * außerdem festlegen der Min-Max-Werte es Row und Column LineEdits
 ******************************************************************************/
void NewTableDialog::showNewTableDialog()
{
    rowColumnsChanged();
    m_dialogCompleted = false;
    m_rowColumnsCount = "";
    ui->rowCountLineEdit->setValidator(new QIntValidator(1, 10000, this));
    ui->columnCountLineEdit->setValidator(new QIntValidator(1, 10000, this));
    this->exec();
}

/******************************************************************************
 * Methode die aufgerufen wird wenn im NewTableDialog Abbrechen geklickt wird und
 * den Dialog schließt.
 ******************************************************************************/
void NewTableDialog::abbrechenBtnClicked()
{
    ui->rowCountLineEdit->setText("");
    ui->columnCountLineEdit->setText("");
    m_dialogCompleted = false;
    this->close();
}

/******************************************************************************
 * Methode die aufgerufen wird wenn der sich der Content in den Lineedits des
 * NewTableDialog ändert und bei leeren feldern den Ok Btn deaktiviert.
 ******************************************************************************/
void NewTableDialog::rowColumnsChanged()
{
    if (ui->columnCountLineEdit->text() != "" && ui->rowCountLineEdit->text() != "")
    {
        ui->okButton->setEnabled(true);
    }
    else
    {
        ui->okButton->setEnabled(false);
    }
}

/******************************************************************************
 * Methode die aufgerufen wird wenn der Ok Btn im NewTableDialog geklickt wird
 * und m_rowColumnsCount einen zusammengesetzen QString aus den lineedits zuweisst
 ******************************************************************************/
void NewTableDialog::okBtnClicked()
{
    qDebug() << ui->rowCountLineEdit->text() << ";" << ui->columnCountLineEdit->text();
    m_rowColumnsCount = ui->rowCountLineEdit->text() + ";" + ui->columnCountLineEdit->text();
    ui->rowCountLineEdit->setText("");
    ui->columnCountLineEdit->setText("");
    m_dialogCompleted = true;
    this->close();
}

/******************************************************************************
 * Methode zur Rückgabe von m_rowColumnsCount der eine QString aus
 * path; + name; + format enthält
 ******************************************************************************/
QString NewTableDialog::getValue()
{
    return m_rowColumnsCount;
}

