#include "soundoutput.h"
#include "ui_soundoutput.h"

QJsonDocument rawSOutputList;
QStringList sOutputIdList;

soundOutput::soundOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::soundOutput)
{
    ui->setupUi(this);
}

soundOutput::~soundOutput()
{
    delete ui;
}

void soundOutput::receiveSOutputList(QJsonDocument sOutputList)
{
    rawSOutputList = sOutputList;
    sOutputIdList.clear();
    ui->listWidget_Outputs->clear();
    ui->pushButton_ViewRaw->setEnabled(true);

    QJsonObject root = sOutputList.object();
    QJsonObject payload = root["payload"].toObject();
    QString output = payload["soundOutput"].toString();
    sOutputIdList.append(output);

    ui->listWidget_Outputs->addItem(output);
}

void soundOutput::on_pushButton_Refresh_clicked()
{
    coms.listSOutputs();
}

void soundOutput::on_pushButton_Set_clicked()
{
    int output = ui->listWidget_Outputs->currentRow();
    if (output < 0) {return;}

    coms.setSOutput(sOutputIdList.at(output));
}

void soundOutput::on_pushButton_ViewRaw_clicked()
{
    emit reqRawData("Sound Outputs Raw Data", rawSOutputList.toJson(QJsonDocument::Indented));
}

void soundOutput::on_pushButton_Close_clicked()
{
    close();
}
