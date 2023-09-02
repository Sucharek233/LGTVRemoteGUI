#ifndef SCANNER_H
#define SCANNER_H

#include <QDialog>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QSet>
#include <QTimer>

namespace Ui {
class scanner;
}

class scanner : public QDialog
{
    Q_OBJECT

public:
    explicit scanner(QWidget *parent = nullptr);
    ~scanner();

    void discover();
    QString readLocation(const QByteArray& data);
    bool validateLocation(const QString& location, const QString& keyword = "");

    void stopScan();

    void readData(QString url);

signals:
    void authorize(QString, QString);

private slots:
    void readDatagrams();
    void handleData();

private slots:
    void on_pushButton_Scan_clicked();

    void on_pushButton_Connect_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_StopScan_clicked();

private:
    Ui::scanner *ui;
};

#endif // SCANNER_H
