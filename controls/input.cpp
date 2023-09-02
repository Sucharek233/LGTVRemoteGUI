#include "input.h"
#include "ui_input.h"

QJsonDocument rawInputList;
QStringList inputIdList;

input::input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::input)
{
    ui->setupUi(this);
}

input::~input()
{
    delete ui;
}

void input::receiveInputList(QJsonDocument inputList)
{
    ui->listWidget_Inputs->clear();
    inputIdList.clear();

    ui->pushButton_ViewRaw->setEnabled(true);
    rawInputList = inputList;
    qDebug() << inputList;

    QJsonObject root = inputList.object();
    QJsonObject payload = root["payload"].toObject();
    QJsonArray inputListArray = payload["devices"].toArray();
    for (const QJsonValue &inputValue : inputListArray) {
        QJsonObject input = inputValue.toObject();
        QString inputName = input["label"].toString();
        QString inputId = input["id"].toString();

        inputIdList.append(inputId);

        QListWidgetItem *item = new QListWidgetItem;
        item->setText(inputName);
        ui->listWidget_Inputs->addItem(item);
    }
}

void input::on_pushButton_Refresh_clicked()
{
    coms.listInputs();
}

void input::on_pushButton_Set_clicked()
{
    int input = ui->listWidget_Inputs->currentRow();
    if (input < 0) {return;}

    coms.setInput(inputIdList.at(input));
}

void input::on_pushButton_ViewRaw_clicked()
{
    emit reqRawData("Inputs Raw Data", rawInputList.toJson(QJsonDocument::Indented));
}

void input::on_pushButton_Close_clicked()
{
    close();
}
