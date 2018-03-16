#include "exportdialog.h"
#include "ui_exportdialog.h"
#include "mainwindow.h"

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);

    connect(ui->abbrechenExportBtn, SIGNAL(clicked(bool)), this, SLOT(abbrechenBtnClicked()));
    connect(ui->dateinameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(namePathChanged()));
    connect(ui->dateipfadLineEdit, SIGNAL(textChanged(QString)), this, SLOT(namePathChanged()));
    connect(ui->okExplortBtn, SIGNAL(clicked(bool)), this, SLOT(okBtnClicked()));
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::showExportDialog()
{
//    m_parser = p;
//    this->show();
    this->exec();
    namePathChanged();
}

void ExportDialog::abbrechenBtnClicked()
{
    ui->dateipfadLineEdit->setText("");
    ui->dateinameLineEdit->setText("");
    this->close();
}

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

void ExportDialog::okBtnClicked()
{
    qDebug() << "Ok button clicked!";

    QString path = ui->dateipfadLineEdit->text();
    QString name = ui->dateinameLineEdit->text();
    QString format = ui->formatComboBox->currentText();
    //ParserCsv *csvP = new ParserCsv();

//    m_parserCsv->saveTable(path, name, format, nullptr);
    ui->dateipfadLineEdit->setText("");
    ui->dateinameLineEdit->setText("");

    this->close();
}

QString ExportDialog::getValue()
{
    return "C:/Users/folkerts_k/test;FileNameTest;.csv";
}
