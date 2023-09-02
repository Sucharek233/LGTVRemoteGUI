#include "auth.h"

bool running = false;

void lgauth::authorize(const QString &host, bool ssl)
{
    if (running) {
        QMessageBox alert;
        alert.setWindowTitle("Authorization running");
        alert.setText("An authorization is already running!\nPlease wait for it to finish.");
        alert.exec();
        return;
    }
    running = true;
    emit statBar("Starting authorization...");
    QString macAddress;
    QHostInfo hostInfo = QHostInfo::fromName(host);
    if (hostInfo.addresses().isEmpty()) {
        running = false;
        emit statBar("Invalid IP Address");
        qDebug() << "Host resolution failed for" << host;
        return;
    }

    QHostAddress hostAddress = hostInfo.addresses().first();
    if (hostAddress.protocol() == QAbstractSocket::IPv4Protocol) {
        ip = hostAddress.toString();
    } else {
        running = false;
        emit statBar(("IPv6 addresses unsupported"));
        qDebug() << "IPv6 addresses are not supported in this example.";
        return;
    }

    hostname = hostInfo.hostName();

    if (macAddress.isEmpty()) {
        macAddress = getMacAddress(ip);
    }

    QString wsUrl = ssl ? "wss://" : "ws://";
    wsUrl += ip + ":300" + (ssl ? "1" : "0");

    qDebug() << wsUrl;

    socket = new QWebSocket;
    QObject::connect(socket, &QWebSocket::connected, this, &lgauth::onConnected);
    QObject::connect(socket, &QWebSocket::disconnected, this, &lgauth::onDisconnected);
    QObject::connect(socket, &QWebSocket::textMessageReceived, this, &lgauth::onTextMessageReceived);

    socket->open(QUrl(wsUrl));
    waitingCallback = &lgauth::prompt;
}

void lgauth::onConnected()
{
    emit statBar("Connected, sending auth request...");
    qDebug() << "connected";
    sendHelloData();
}
void lgauth::onDisconnected()
{
    qDebug() << "disconnected";
    if (running) {emit statBar("Authorization failed (timed out)");}
    running = false;
}
void lgauth::onTextMessageReceived(const QString &message)
{
    QJsonObject response = QJsonDocument::fromJson(message.toUtf8()).object();
    QString stringResponse = QJsonDocument(response).toJson();
    qDebug() << stringResponse;
    QString key = response.value("payload").toObject().value("client-key").toString();
    if (waitingCallback) {
        (this->*waitingCallback)(response);
    }
    if (stringResponse.contains("403 Error: User rejected pairing")) {
        emit statBar("Authorization canceled");
        running = false;
    }
    if (!key.simplified().isEmpty()) {
        emit statBar("Authorization successful");
        emit sendKey(key);
        running = false;
    }
}

void lgauth::sendHelloData()
{
    socket->sendTextMessage(QString::fromUtf8(payload.toJson(QJsonDocument::Compact)));
}

void lgauth::prompt(const QJsonObject &response)
{
    if (response.contains("payload")) {
        QJsonObject payload = response.value("payload").toObject();
        if (payload.contains("pairingType") && payload.value("pairingType") == "PROMPT") {
            emit statBar("Waiting for pairing confirmation");
            qDebug() << "Please accept the pairing request on your LG TV";
            waitingCallback = &lgauth::setClientKey;
        }
    }
}

void lgauth::setClientKey(const QJsonObject &response)
{
    if (response.contains("payload") && response.value("payload").isObject()) {
        QJsonObject payload = response.value("payload").toObject();
        if (payload.contains("client-key")) {
            clientKey = payload.value("client-key").toString();
            waitingCallback = nullptr;
            emit statBar("Authorization successful");
            socket->close();
        }
    }
}

QString lgauth::getMacAddress(const QString &address)
{
    QHostAddress hostAddress(address);
    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
            if (entry.ip() == hostAddress) {
                return interface.hardwareAddress();
            }
        }
    }
    return QString();
}
