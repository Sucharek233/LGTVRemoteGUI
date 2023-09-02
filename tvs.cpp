#include "tvs.h"
#include "ui_tvs.h"

QString path;

bool autoConnect = false;
QStringList connectInfo;

tvs::tvs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tvs)
{
    ui->setupUi(this);

    connect(&scan, &scanner::authorize, this, &tvs::authScan, Qt::AutoConnection);

    path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/";
    init();
}

tvs::~tvs()
{
    delete ui;
}

void tvs::init()
{
    ui->listWidget_TVs->clear();

    QDir checkPath(path);
    if (!checkPath.exists()) {checkPath.mkpath(path);}

    QFile config(path + "tvs.info");
    if (!config.exists()) {config.open(QIODevice::WriteOnly); config.close();}
    config.open(QIODevice::ReadOnly);
    QString content = config.readAll();
    config.close();

    if (content.simplified().isEmpty()) {
        return;
    }

    QStringList entries = content.split("\u200B");
    entries.removeAll("");
    qDebug() << entries;
    foreach (QString entry, entries) {
        QStringList data = entry.split("\n");

        QListWidgetItem *item = new QListWidgetItem;
        QString name = data.at(0) + " (" + data.at(1) + ")";
        if (data.at(3) == "yes") {autoConnect = true; connectInfo = data; name += " (Connecting on start)";}
        item->setText(name);
        qDebug() << "adding item" << data.at(0);
        ui->listWidget_TVs->addItem(item);
    }
}

void tvs::addToConfig(QString name, QString ip, QString key, QString autoconnect)
{
    QFile config(path + "tvs.info");
    config.open(QIODevice::ReadWrite);
    QString content = config.readAll();

    QString toAdd = content + name + "\n" + ip + "\n" + key + "\n" + autoconnect + "\u200B";

    config.resize(0);
    config.write(toAdd.toUtf8());
    config.close();

    init();
}

void tvs::checkAutoconnect()
{
    if (!autoConnect) {
        return;
    }

    QString ip = "ws://" + connectInfo.at(1) + ":3000";
    QString clientKey = connectInfo.at(2);

    emit dataForComs(ip, clientKey);
    emit startHandshake();

    connectInfo.clear();
    autoConnect = false;
}

QStringList tvs::getConfig()
{
    int tv = ui->listWidget_TVs->currentRow();

    QFile config(path + "tvs.info");
    config.open(QIODevice::ReadOnly);
    QString content = config.readAll();
    config.close();

    QStringList data = content.split("\u200B");
    QString tvContent = data.at(tv);
    QStringList tvData = tvContent.split("\n");

    return tvData;
}

void tvs::finished(QString key)
{
    QString name = ui->lineEdit_Name->text();
    QString ip = ui->lineEdit_IP->text();

    addToConfig(name, ip, key, "no");
}

void tvs::on_pushButton_Add_clicked()
{
    QString ip = ui->lineEdit_IP->text();
    if (ip.simplified().isEmpty()) {
        QMessageBox alert;
        alert.setWindowTitle("No IP address");
        alert.setText("No IP address has been entered.\nPlease enter an IP address before adding a TV!");
        alert.exec();
        return;
    }

    emit add(ip, false);
}

void tvs::on_pushButton_Connect_clicked()
{
    if (ui->listWidget_TVs->currentRow() < 0) {
        QMessageBox selection;
        selection.setWindowTitle("No TV Selected");
        selection.setText("No TV has been selected to connect.\nPlease select a TV and then connect!");
        selection.exec();
        return;
    }

    QStringList data = getConfig();

    QString ip = "ws://" + data.at(1) + ":3000";
    QString clientKey = data.at(2);

    emit dataForComs(ip, clientKey);
    emit startHandshake();
}

void tvs::on_pushButton_Disconnect_clicked()
{
    emit disconnectTV();
}

void tvs::on_pushButton_Autoconnect_clicked()
{
    QFile config(path + "tvs.info");
    config.open(QIODevice::ReadOnly);
    QString current = config.readAll();
    config.close();

    QStringList data = current.split("\u200B");
    data.removeAll("");
    int i = -1; int target = ui->listWidget_TVs->currentRow();
    QStringList modifiedData;
    foreach(QString entry, data) {
        i += 1;
        QStringList entryData = entry.split("\n");
        if (entryData.at(3) == "yes") {entryData.replace(3, "no");}
        if (i == target) {
            entryData.replace(3, "yes");
        }

        modifiedData.append(entryData.join("\n"));
    }

    QString write = modifiedData.join("\u200B");
    qDebug() << modifiedData;
    qDebug() << write;
    config.open(QIODevice::WriteOnly);
    config.resize(0);
    config.write(write.toUtf8());
    config.close();

    init();
}

void tvs::on_pushButton_Scanner_clicked()
{
    scan.exec();
}
void tvs::authScan(QString name, QString ip)
{
    ui->lineEdit_Name->setText(name);
    ui->lineEdit_IP->setText(ip);

    emit add(ip, false);
}

void tvs::on_pushButton_Close_clicked()
{
    close();
}
