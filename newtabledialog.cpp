#include "newtabledialog.h"
#include "ui_newtabledialog.h"

NewTableDialog::NewTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTableDialog)
{
    ui->setupUi(this);

    connect(ui->abbrechenButton, SIGNAL(clicked(bool)), this, SLOT(abbrechenBtnClicked()));
    connect(ui->spaltenLineEdit, SIGNAL(textChanged(QString)), this, SLOT(rowColumnsChanged()));
    connect(ui->zeilenLineEdit, SIGNAL(textChanged(QString)), this, SLOT(rowColumnsChanged()));
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
    QValidator *validator = new QIntValidator(1, 10000, this);
    ui->spaltenLineEdit->setValidator(validator);
    ui->zeilenLineEdit->setValidator(validator);
    this->exec();
}

/******************************************************************************
 * Methode die aufgerufen wird wenn im NewTableDialog Abbrechen geklickt wird und
 * den Dialog schließt.
 ******************************************************************************/
void NewTableDialog::abbrechenBtnClicked()
{
    ui->zeilenLineEdit->setText("");
    ui->spaltenLineEdit->setText("");
    m_dialogCompleted = false;
    this->close();
}

/******************************************************************************
 * Methode die aufgerufen wird, wenn sich der Content in den Lineedits des
 * NewTableDialog ändert und bei leeren Feldern (und < 1) den Ok Btn deaktiviert.
 ******************************************************************************/
void NewTableDialog::rowColumnsChanged()
{
    if (ui->spaltenLineEdit->text() != "" && ui->zeilenLineEdit->text() != "" &&
        ui->spaltenLineEdit->text().toInt() >= 1 && ui->zeilenLineEdit->text().toInt() >= 1)
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
    qDebug() << ui->zeilenLineEdit->text() << ui->spaltenLineEdit->text();
    m_rowColumnsCount = ui->zeilenLineEdit->text() + ";" + ui->spaltenLineEdit->text();
    ui->zeilenLineEdit->setText("");
    ui->spaltenLineEdit->setText("");
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

