#include "exportdialog.h"
#include "ui_exportdialog.h"
#include "mainwindow.h"

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    qDebug() << "ExportDialog instanziiert...";
    ui->setupUi(this);

    connect(ui->abbrechenExportBtn, SIGNAL(clicked(bool)), this, SLOT(abbrechenBtnClicked()));
    connect(ui->dateinameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(namePathChanged()));
    connect(ui->dateipfadLineEdit, SIGNAL(textChanged(QString)), this, SLOT(namePathChanged()));
    connect(ui->okExplortBtn, SIGNAL(clicked(bool)), this, SLOT(okBtnClicked()));
}

ExportDialog::~ExportDialog()
{
    delete ui;
    qDebug() << "ExportDialog zerstoert...";
}

/******************************************************************************
 * Methode die von MainWindow aufgerufen wird und den ExportDialog anzeigt.
 ******************************************************************************/
void ExportDialog::showExportDialog()
{
    namePathChanged();
    this->exec();
}

/******************************************************************************
 * Methode die aufgerufen wird wenn im Exportdlg Abbrechen geklickt wird und
 * den Dialog schließt.
 ******************************************************************************/
void ExportDialog::abbrechenBtnClicked()
{
    ui->dateipfadLineEdit->setText("");
    ui->dateinameLineEdit->setText("");
    m_dialogCompleted = false;
    this->close();
}

/******************************************************************************
 * Methode die aufgerufen wird wenn der sich der Content in den Lineedits des
 * Exportdlg ändert und bei leeren feldern den Ok Btn deaktiviert.
 ******************************************************************************/
void ExportDialog::namePathChanged()
{
    if (ui->dateinameLineEdit->text() != "" && ui->dateipfadLineEdit->text() != "")
    {
        ui->okExplortBtn->setEnabled(true);
    }
    else
    {
        ui->okExplortBtn->setEnabled(false);
    }
}

/******************************************************************************
 * Methode die aufgerufen wird wenn der Ok Btn im ExportDialog geklickt wird
 * und m_pathAndFile einen zusammengesetzen QString aus den lineedits zuweisst
 ******************************************************************************/
void ExportDialog::okBtnClicked()
{
    qDebug() << "Ok button clicked!";

    QString path = ui->dateipfadLineEdit->text();
    QString name = ui->dateinameLineEdit->text();
    QString format = ui->formatComboBox->currentText();

    m_pathAndFile = path + ";" + name + ";" + format;

    ui->dateipfadLineEdit->setText("");
    ui->dateinameLineEdit->setText("");
    m_dialogCompleted = true;
    this->close();
}
/******************************************************************************
 * Methode zur Rückgabe von m_pathAndFile der eine QString aus
 * path; + name; + format enthält
 ******************************************************************************/
QString ExportDialog::getValue()
{
    return m_pathAndFile;
}
