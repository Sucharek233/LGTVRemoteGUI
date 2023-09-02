#ifndef AUTH_H
#define AUTH_H

#include <QDebug>
#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QMessageBox>

class lgauth : public QObject
{
    Q_OBJECT

public:
    void authorize(const QString &host, bool ssl = false);

    void prompt(const QJsonObject &response);
    void setClientKey(const QJsonObject &response);
    QString getMacAddress(const QString &address);

    void setPayload(QJsonDocument pd) {payload = pd;}

public: signals:
    void sendKey(QString);
    void statBar(QString);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString &message);

private:
    QWebSocket *socket;
    QString clientKey;
    QString macAddress;
    QString name;
    QString ip;
    QString hostname;
    void (lgauth::*waitingCallback)(const QJsonObject &) = nullptr;

    QJsonDocument payload;

    void sendHelloData();
};


#endif // AUTH_H
