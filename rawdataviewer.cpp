#include "rawdataviewer.h"
#include "ui_rawdataviewer.h"

rawDataViewer::rawDataViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rawDataViewer)
{
    ui->setupUi(this);
}

rawDataViewer::~rawDataViewer()
{
    delete ui;
}

void rawDataViewer::on_pushButton_Close_clicked()
{
    close();
}

void rawDataViewer::load(QString type, QString data)
{
    ui->label_Title->setText(type);
    ui->plainTextEdit_Data->clear();
    ui->plainTextEdit_Data->setPlainText(data);
}
