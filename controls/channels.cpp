#include "channels.h"
#include "ui_channels.h"

QStringList channelIdList;

channels::channels(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::channels)
{
    ui->setupUi(this);
}

channels::~channels()
{
    delete ui;
}

void channels::receiveChList(QJsonDocument chList)
{
    ui->listWidget_Channels->clear();
    channelIdList.clear();

    QJsonObject root = chList.object();
    QJsonObject payload = root["payload"].toObject();
    QJsonArray chListArray = payload["channelList"].toArray();
    for (const QJsonValue &channelValue : chListArray) {
        QJsonObject channel = channelValue.toObject();
        QString channelName = channel["channelName"].toString();
        QString channelId = channel["channelId"].toString();

        channelIdList.append(channelId);

        QListWidgetItem *item = new QListWidgetItem;
        item->setText(channelName);
        ui->listWidget_Channels->addItem(item);
    }
}

void channels::on_pushButton_Refresh_clicked()
{
    coms.getChList();
}

void channels::on_pushButton_Switch_clicked()
{
    int channel = ui->listWidget_Channels->currentRow();
    if (channel < 0) {return;}

    coms.setCurrCh(channelIdList.at(channel));
}

void channels::on_pushButton_Info_clicked()
{
    coms.getCurrChInfo();
}

void channels::on_pushButton_Up_clicked()
{
    coms.chUp();
}

void channels::on_pushButton_Down_clicked()
{
    coms.chDown();
}

void channels::on_pushButton_ProgInfo_clicked()
{
    coms.getCurrChInfo();
}

void channels::on_pushButton_Close_clicked()
{
    close();
}
