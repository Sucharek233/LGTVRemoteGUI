#include "scanner.h"
#include "ui_scanner.h"

QUdpSocket *udpSocket;
QSet<QString> locations;
QSet<QString> seen;

QStringList names;
QStringList ips;

QTimer* scanTimeout;

scanner::scanner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scanner)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 0, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead, this, &scanner::readDatagrams);

    scanTimeout = new QTimer();
    scanTimeout->setInterval(20000);
    connect(scanTimeout, &QTimer::timeout, this, &scanner::stopScan);
}

scanner::~scanner()
{
    delete ui;
}

void scanner::discover()
{
    scanTimeout->start();

    QString message = QString(
               "M-SEARCH * HTTP/1.1\n"
               "HOST: 239.255.255.250:1900\n"
               "MAN: \"ssdp:discover\"\n"
               "ST: urn:schemas-upnp-org:device:MediaRenderer:1\n"
               "MX: 3\n\n");

    QByteArray data = message.toUtf8();

    QString keyword = "LG";

    udpSocket->writeDatagram(data, QHostAddress("239.255.255.250"), 1900);

    while (udpSocket->hasPendingDatagrams()) {
        qDebug() << "a";
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QString location = readLocation(datagram.data());

        if (!location.isEmpty() && !seen.contains(location) && validateLocation(location, keyword)) {
            seen.insert(location);
            locations.insert(location);
            qDebug() << "Discovered:" << location;
        }
    }
}
void scanner::readDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QString location = readLocation(datagram.data());

        if (!location.isEmpty() && !seen.contains(location) && validateLocation(location)) {
            seen.insert(location);
            locations.insert(location);
            qDebug() << "Discovered:" << location;

            readData(location);
        }
    }
}
QString scanner::readLocation(const QByteArray& data)
{
    QString resp = QString::fromUtf8(data);
    QStringList lines = resp.toLower().split('\n');
    for (const QString& line : lines) {
        if (line.startsWith("location: ")) {
            return line.mid(10).trimmed();
        }
    }
    return "";
}
bool scanner::validateLocation(const QString& location, const QString& keyword)
{
    QUrl url(location);
    QByteArray content = QUrl(location).toEncoded();
    if (!keyword.isEmpty()) {
        QByteArray keywordBytes = keyword.toUtf8();
        if (!content.contains(keywordBytes)) {
            return false;
        }
    }
    return true;
}

void scanner::stopScan()
{
    ui->pushButton_Scan->setEnabled(true);
    ui->pushButton_StopScan->setEnabled(false);
    ui->label_Main->setText("Scanner");

    locations.clear();
    seen.clear();

    udpSocket->disconnect();
    udpSocket->deleteLater();
    udpSocket = new QUdpSocket;
    udpSocket->bind(QHostAddress::AnyIPv4, 0, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead, this, &scanner::readDatagrams);
}

QNetworkAccessManager networkManager;
void scanner::readData(QString url)
{
    QNetworkRequest request(url);
    QNetworkReply* reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, &scanner::handleData);
}
void scanner::handleData()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QString content = QString::fromUtf8(responseData);
        QStringList locate = content.split("\n");
        QString target;
        foreach(QString line, locate) {
            if (line.contains("friendlyName")) {
                QString one = line.mid(0, line.indexOf(">")) + ">";
                QString two = line.replace(one, "");
                QString three = two.mid(0, line.indexOf("<"));

                target = three;
            }
        }

        QString url = reply->url().toString();
        QString one = url.mid(0, url.indexOf("/")) + "/";
        QString two = url.replace(one, "");
        QString three = two.replace("/", "");
        QString ip = three.mid(0, three.indexOf(":"));

        if (!target.simplified().isEmpty()) {
            ui->listWidget_Scanned->addItem(target + " (" + ip + ")");
            names.append(target);
        } else {
            ui->listWidget_Scanned->addItem(ip);
            names.append(ip);
        }
        ips.append(ip);

    } else {
        qDebug() << "Error reading website data:" << reply->errorString();
    }
    reply->deleteLater();
}

void scanner::on_pushButton_Scan_clicked()
{
    ui->listWidget_Scanned->clear();
    ui->pushButton_Scan->setEnabled(false);
    ui->pushButton_StopScan->setEnabled(true);
    ui->label_Main->setText("Scanning...");

    discover();
}


void scanner::on_pushButton_StopScan_clicked()
{
    scanTimeout->stop();
    stopScan();
}

void scanner::on_pushButton_Connect_clicked()
{
    int item = ui->listWidget_Scanned->currentRow();
    if (item == -1) {
        return;
    }

    QString name = names.at(item);
    QString ip = ips.at(item);

    emit authorize(name, ip);

    close();
}

void scanner::on_pushButton_Close_clicked()
{
    close();
}
