#include "commands.h"

QWebSocket *socket = new QWebSocket();
int commandCount = 0;

bool connected = false;
bool connecting = false;

bool viewRawData = false;
QString rType;

bool sendChList = false;
bool sendAppList = false;
bool sendInList = false;
bool sendSOutList = false;

bool sendAppPayoadInput = false;
bool sendAppPayoadOutput = false;

QJsonObject customCallContent;
bool onlyCustomCall = false;
bool customCallSendInput = false;
bool customCallSendOutput = false;

bool gettingRemoteSocket = false;

void commands::handshake()
{
    if (connected) {
        emit statBar("TV already connected");
        return;
    }
    if (connecting) {
        QMessageBox alert;
        alert.setWindowTitle("Already connecting");
        alert.setText("Already connecting to a TV!");
        alert.exec();
        return;
    }

    emit statBar("Initializing handshake...");
    QJsonObject pd = payload.object();

    QJsonObject payloadObject = pd["payload"].toObject();
    payloadObject["client-key"] = key;

    pd["payload"] = payloadObject;

    QJsonDocument fPd(pd);

    qDebug() << "Starting handshake" << ip;
    emit statBar("Starting handshake...");
    socket->open(QUrl(ip));
    connecting = true;

    QObject::connect(socket, &QWebSocket::connected, [fPd, this]() {
        qDebug() << "Connected";
        emit statBar("Connected, waiting for handshake response...");
        socket->sendTextMessage(QString::fromUtf8(fPd.toJson(QJsonDocument::Indented)));
        connected = true;
        connecting = false;
    });
    QObject::connect(socket, &QWebSocket::disconnected, [&]() {
        qDebug() << "Disconnected";
        if (connecting == true && connected == false) {
            emit statBar("TV Connection Failed");
        } else {
            emit statBar("TV Disconnected");
        }
        connected = false;
        connecting = false;

        socket->deleteLater();
        socket = new QWebSocket();
    });
    QObject::connect(socket, &QWebSocket::bytesWritten, [&]() {
        qDebug() << "Message sent.";
    });
    QObject::connect(socket, &QWebSocket::textMessageReceived, this, &commands::socketResponse);
}

void commands::disconnect()
{
    socket->close();
}

void commands::sendCommand(const QString &msgType, const QString &uri, const QJsonObject payload, const QString &prefix)
{
    if (connected == false) {
        QMessageBox alert;
        alert.setWindowTitle("No TV connected");
        alert.setText("No TV connected! Please conect to a TV before running any commands!");
        alert.exec();
        return;
    }

    QJsonObject messageData;
    if (onlyCustomCall) {
        messageData = customCallContent;
        QString input = QJsonDocument(messageData).toJson(QJsonDocument::Indented);
        emit sendCustomCallResponse("Sending command:\n" + input);
        onlyCustomCall = false;
    } else {
        QString messageId = prefix.isEmpty() ? QString::number(commandCount) : (prefix + '_' + QString::number(commandCount));

        messageData["id"] = messageId;
        messageData["type"] = msgType;
        messageData["uri"] = uri;

        messageData["payload"] = payload;

        commandCount++;
    }

    QJsonDocument doc(messageData);
    if (sendAppPayoadInput) {
        QString input = doc.toJson(QJsonDocument::Indented);
        emit sendAppPayloadResponse("Sending command:\n" + input); //doesn't work, don't know why
        sendAppPayoadInput = false;
    }
    if (customCallSendInput) {
        QString input = doc.toJson(QJsonDocument::Indented);
        emit sendCustomCallResponse("Sending command:\n" + input); //doesn't work, don't know why
        customCallSendInput = false;
    }
    qDebug() << "Sending command\n" << doc;

    socket->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}

void commands::socketResponse(QString response)
{
    qDebug() << "Response received:" << response;
    if (response.contains("registered")) {emit statBar("Handshake received, TV connected");}
    if (viewRawData) {
        QJsonDocument rawResponse = QJsonDocument::fromJson(response.toUtf8());
        QString formattedResponse = rawResponse.toJson(QJsonDocument::Indented);
        emit sendRawData(rType, formattedResponse);
        viewRawData = false;
    }
    if (sendChList) {
        QJsonDocument rawResponse = QJsonDocument::fromJson(response.toUtf8());
        emit sendChannelList(rawResponse);
        sendChList = false;
    }
    if (sendAppList) {
        QJsonDocument rawResponse = QJsonDocument::fromJson(response.toUtf8());
        emit sendApplicationList(rawResponse);
        sendAppList = false;
    }
    if (sendInList) {
        QJsonDocument rawResponse = QJsonDocument::fromJson(response.toUtf8());
        emit sendInputList(rawResponse);
        sendInList = false;
    }
    if (sendSOutList) {
        QJsonDocument rawResponse = QJsonDocument::fromJson(response.toUtf8());
        emit sendSOutputList(rawResponse);
        sendSOutList = false;
    }
    if (sendAppPayoadOutput) {
        QJsonDocument rawResponse = QJsonDocument::fromJson(response.toUtf8());
        QString formattedResponse = rawResponse.toJson(QJsonDocument::Indented);
        emit sendAppPayloadResponse("Received response:\n" + formattedResponse);
        sendAppPayoadOutput = false;
    }
    if (customCallSendOutput) {
        QJsonDocument rawResponse = QJsonDocument::fromJson(response.toUtf8());
        QString formattedResponse = rawResponse.toJson(QJsonDocument::Indented);
        emit sendCustomCallResponse("Received response:\n" + formattedResponse);
        customCallSendOutput = false;
    }
    if (gettingRemoteSocket) {
        handleSocket(QJsonDocument::fromJson(response.toUtf8()));
        gettingRemoteSocket = false;
    }
}
void commands::rdvRequest(QString title)
{
    viewRawData = true;
    rType = title;
}

//Audio commands
void commands::volumeUp()
{
    sendCommand("request", "ssap://audio/volumeUp", QJsonObject(), "volumeup");
}
void commands::volumeDown()
{
    sendCommand("request", "ssap://audio/volumeDown", QJsonObject(), "volumedown");
}
void commands::mute(bool muted)
{
    QJsonObject pd;
    if (muted == true) {
        pd["mute"] = "true";
    } else {
        pd["setMute"] = "false";
    }

    sendCommand("request", "ssap://audio/setMute", pd);
}
void commands::setVolume(int level)
{
    QJsonObject pd;
    pd["volume"] = level;

    sendCommand("request", "ssap://audio/setVolume", pd);
}
void commands::play()
{
    sendCommand("request", "ssap://media.controls/play", QJsonObject());
}
void commands::pause()
{
    sendCommand("request", "ssap://media.controls/pause", QJsonObject());
}
void commands::stop()
{
    sendCommand("request", "ssap://media.controls/stop", QJsonObject());
}
void commands::rewind()
{
    sendCommand("request", "ssap://media.controls/rewind", QJsonObject());
}
void commands::fastForward()
{
    sendCommand("request", "ssap://media.controls/fastForward", QJsonObject());
}
void commands::audioStatus()
{
    rdvRequest("Audio Status Raw Data");
    sendCommand("request", "ssap://audio/getStatus", QJsonObject(), "status");
}

//Channel commands
void commands::chUp()
{
    sendCommand("request", "ssap://tv/channelUp", QJsonObject());
}
void commands::chDown()
{
    sendCommand("request", "ssap://tv/channelDown", QJsonObject());
}
void commands::getChList()
{
    sendChList = true;
    sendCommand("request", "ssap://tv/getChannelList", QJsonObject(), "channels");
}
void commands::getCurrChInfo()
{
    viewRawData = true;
    rdvRequest("Current Channel Info");
    sendCommand("request", "ssap://tv/getCurrentChannel", QJsonObject(), "channels");
}
void commands::getCurrChProg()
{
    viewRawData = true;
    rdvRequest("Current Channel Program");
    sendCommand("request", "ssap://tv/getChannelProgramInfo", QJsonObject(), "channels");
}
void commands::setCurrCh(QString id)
{
    id = "1-" + id;

    QJsonObject pd;
    pd["channelId"] = id;

    sendCommand("request", "ssap://tv/openChannel", pd);
}

//Application commands
void commands::getAppList()
{
    sendAppList = true;

    sendCommand("request", "ssap://com.webos.applicationManager/listApps", QJsonObject());
}
void commands::startApp(QString appId)
{
    QJsonObject pd;
    pd["id"] = appId;

    sendCommand("request", "ssap://system.launcher/launch", pd);
}
void commands::closeApp(QString appId)
{
    QJsonObject pd;
    pd["id"] = appId;

    sendCommand("request", "ssap://system.launcher/close", pd);
}
void commands::startAppPd(QJsonObject payload, QString appId)
{
    sendAppPayoadInput = true;
    sendAppPayoadOutput = true;

    payload["id"] = appId;

    sendCommand("request", "ssap://system.launcher/launch", payload);
}
void commands::getCurrAppInfo()
{
    rType = "Current (Foregroud) App Information";
    viewRawData = true;
    sendCommand("request", "ssap://com.webos.applicationManager/getForegroundAppInfo", QJsonObject());
}
void commands::listLaunchPoints()
{
    rType = "Application Launch points";
    viewRawData = true;
    sendCommand("request", "ssap://com.webos.applicationManager/listLaunchPoints", QJsonObject(), "launcher");
}

//System commands
void commands::tvOff()
{
    sendCommand("request", "ssap://system/turnOff", QJsonObject());
}
void commands::screenOn()
{
    QJsonObject pd;
    pd["standbyMode"] = "active";

    sendCommand("request", "ssap://com.webos.service.tvpower/power/turnOnScreen", pd);
}
void commands::screenOff()
{
    QJsonObject pd;
    pd["standbyMode"] = "active";

    sendCommand("request", "ssap://com.webos.service.tvpower/power/turnOffScreen", pd);
}
void commands::sysInfo()
{
    rType = "System information";
    viewRawData = true;
    sendCommand("request", "ssap://system/getSystemInfo", QJsonObject());
}
void commands::getServices()
{
    rType = "Services information";
    viewRawData = true;
    sendCommand("request", "ssap://api/getServiceList", QJsonObject(), "services");
}
void commands::getSwInfo()
{
    rType = "Software information";
    viewRawData = true;
    sendCommand("request", "ssap://com.webos.service.update/getCurrentSWInformation", QJsonObject(), "sw_info");
}
void commands::getPwrState()
{
    rType = "Power State information";
    viewRawData = true;
    sendCommand("request", "ssap://com.webos.service.tvpower/power/getPowerState", QJsonObject());
}
void commands::getSettings(QString category)
{
    QJsonObject pd;
    QJsonArray keys;
    if (category == "picture") {
        rType = "Picture Settings information";
        keys = {"brightness", "backlight", "contrast", "color"};
    } else if (category == "sound") {
        rType = "Sound Settings information";
        keys = {"soundMode"};
    } else if (category == "twinTv") {
        rType = "Twin TV Settings information";
        keys = {"status", "role", "systemMode"};
    } else if (category == "network") {
        rType = "Network Settings information";
        keys = {"deviceName"};
    } else if (category == "option") {
        rType = "Option Settings information";
        keys = {"audioGuidance"};
    } else if (category == "time") {
        rType = "Time Settings information";
        keys = {"onTimerVolume"};
    }
    pd["keys"] = keys;
    pd["category"] = category;

    viewRawData = true;
    sendCommand("request", "ssap://settings/getSystemSettings", pd);
}

//Input commands
void commands::listInputs()
{
    sendInList = true;
    sendCommand("request", "ssap://tv/getExternalInputList", QJsonObject(), "input");
}
void commands::setInput(QString input)
{
    QJsonObject pd;
    pd["inputId"] = input;

    sendCommand("request", "ssap://tv/switchInput", pd);
}

//Sound Output commnds
void commands::listSOutputs()
{
    sendSOutList = true;
    sendCommand("request", "ssap://com.webos.service.apiadapter/audio/getSoundOutput", QJsonObject());
}
void commands::setSOutput(QString sOutput)
{
    QJsonObject pd;
    pd["output"] = sOutput;

    sendCommand("request", "ssap://audio/changeSoundOutput", pd);
}

//Notification commands
void commands::createNotification(QString text)
{
    QJsonObject pd;
    pd["message"] = text;

    sendCommand("request", "ssap://system.notifications/createToast", pd);
}
void commands::createAlert(QString text, QStringList bText, QString type)
{
    QJsonObject pd;
    pd["message"] = text;

    QJsonArray buttons;
    foreach(QString text, bText) {
        QJsonObject button;
        button["label"] = text;
        buttons.append(button);
    }

    pd["buttons"] = buttons;
    pd["type"] = type;
    qDebug() << pd;

    sendCommand("request", "ssap://system.notifications/createAlert", pd);
}

//Miscellaneous commands
void commands::enterText(QString text)
{
    QJsonObject pd;
    pd["text"] = text;
    pd["replace"] = 0;

    sendCommand("request", "ssap://com.webos.service.ime/insertText", pd);
}
void commands::sendEnter()
{
    sendCommand("request", "ssap://com.webos.service.ime/sendEnterKey", QJsonObject());
}
void commands::deleteText(int value)
{
    QJsonObject pd;
    pd["count"] = value;

    sendCommand("request", "ssap://com.webos.service.ime/deleteCharacters", pd);
}
void commands::openYTLink(QString link)
{
    QJsonObject pd;
    QJsonObject params;
    pd["id"] = "youtube.leanback.v4";
    params["contentTarget"] = link;
    pd["params"] = params;

    sendCommand("request", "ssap://system.launcher/launch", pd);
    sendCommand("request", "ssap://system.launcher/launch", pd);
}
void commands::openBrowserUrl(QString url)
{
    QJsonObject pd;
    pd["target"] = url;

    sendCommand("request", "ssap://system.launcher/open", pd);
}
void commands::v3DOn()
{
    sendCommand("request", "ssap://com.webos.service.tv.display/set3DOn", QJsonObject());
}
void commands::v3DOff()
{
    sendCommand("request", "ssap://com.webos.service.tv.display/set3DOff", QJsonObject());
}
void commands::v3DStatus()
{
    rType = "3D Status";
    viewRawData = true;
    sendCommand("request", "ssap://com.webos.service.tv.display/get3DStatus", QJsonObject());
}

//Custom call
void commands::customCall(QJsonObject content)
{
    onlyCustomCall = true;
    customCallSendInput = true;
    customCallSendOutput = true;
    customCallContent = content;

    sendCommand("Unused for", "this void", QJsonObject());
}

//Magic Remote
QWebSocket *remoteSocket = new QWebSocket();
bool remoteConnected = false;
void commands::startRemote()
{
    if (remoteConnected) {
        QMessageBox connected;
        connected.setWindowTitle("Already Running");
        connected.setText("Magic Remote Service is already running.");
        connected.exec();
    }

    gettingRemoteSocket = true;
    sendCommand("request", "ssap://com.webos.service.networkinput/getPointerInputSocket", QJsonObject());
}
void commands::handleSocket(QJsonDocument socket)
{
    QJsonObject root = socket.object();
    QJsonObject pd = root["payload"].toObject();
    QString sockPath = pd["socketPath"].toString();
    qDebug() << sockPath;

    remoteSocket->open(QUrl(sockPath));

    QObject::connect(remoteSocket, &QWebSocket::connected, [&]() {
        qDebug() << "Connected";
        remoteConnected = true;
    });
    QObject::connect(remoteSocket, &QWebSocket::disconnected, [&]() {
        qDebug() << "Disconnected";
        remoteConnected = false;
        remoteSocket->deleteLater();
        remoteSocket = new QWebSocket();
    });
    QObject::connect(remoteSocket, &QWebSocket::bytesWritten, [&]() {
        qDebug() << "Message sent.";
    });
}
void commands::stopRemote()
{
    remoteConnected = false; //probably useless
    remoteSocket->close();
}
void commands::cursorMove(QString x, QString y, QString drag)
{
    if (!remoteConnected) {remoteDisconnected();}

    QString command = "type:move\n"
                      "dx:" + x + "\n"
                      "dy:" + y + "\n"
                      "down:" + drag + "\n\n";
    remoteSocket->sendTextMessage(command);
}
void commands::cursorClick()
{
    if (!remoteConnected) {remoteDisconnected();}

    QString command = "type:click\n\n";
    remoteSocket->sendTextMessage(command);
}
void commands::cursorPress(QString button)
{
    if (!remoteConnected) {remoteDisconnected();}

    QString command = "type:button\n"
                      "name:" + button + "\n\n";
    remoteSocket->sendTextMessage(command);
}
void commands::cursorScroll(QString x, QString y)
{
    if (!remoteConnected) {remoteDisconnected();}

    QString command = "type:scroll\n"
                      "dx:" + x + "\n"
                      "dy:" + y + "\n\n";
    remoteSocket->sendTextMessage(command);
}
void commands::remoteDisconnected()
{
    QMessageBox disconnected;
    disconnected.setWindowTitle("Service Offline");
    disconnected.setText("Magic Remote service is offline.\nPlease start it before running any commands!");
    disconnected.exec();
}
