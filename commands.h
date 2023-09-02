#ifndef COMMANDS_H
#define COMMANDS_H

#include <QDebug>
#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QMessageBox>

class commands : public QObject
{
    Q_OBJECT

public:
    void setPd(QJsonDocument pd) {payload = pd;}
    void setIPKey(QString i, QString clientKey) {qDebug() << "sent"; ip = i; key = clientKey;}
    void sendCommand(const QString &msgType, const QString &uri, const QJsonObject payload, const QString &prefix = QString());
    void rdvRequest(QString title);

    //Audio commands
    void volumeUp();
    void volumeDown();
    void mute(bool muted);
    void setVolume(int level);
    void play();
    void pause();
    void stop();
    void rewind();
    void fastForward();
    void audioStatus();

    //Channel commands
    void chUp();
    void chDown();
    void getChList();
    void getCurrChInfo();
    void getCurrChProg();
    void setCurrCh(QString id);

    //Application comands
    void getAppList();
    void startApp(QString appId);
    void closeApp(QString appId);
    void startAppPd(QJsonObject payload, QString appId);
    void getCurrAppInfo();
    void listLaunchPoints();

    //System commands
    void tvOff();
    void screenOn();
    void screenOff();
    void sysInfo();
    void getServices();
    void getSwInfo();
    void getPwrState();
    void getSettings(QString category);

    //Input commands
    void listInputs();
    void setInput(QString input);

    //Sound Output commnds
    void listSOutputs();
    void setSOutput(QString sOutput);

    //Notification commands
    void createNotification(QString text);
    void createAlert(QString text, QStringList bText, QString type);

    //Miscellaneous commands
    void enterText(QString text);
    void sendEnter();
    void deleteText(int value);
    void openYTLink(QString link);
    void openBrowserUrl(QString url);
    void v3DOn();
    void v3DOff();
    void v3DStatus();

    //Custom call
    void customCall(QJsonObject content);

    //Magic Remote
    void startRemote();
    void handleSocket(QJsonDocument socket);
    void stopRemote();
    void cursorMove(QString x, QString y, QString drag);
    void cursorClick();
    void cursorPress(QString button);
    void cursorScroll(QString x, QString y);
    void remoteDisconnected();

public slots:
    void handshake();

    void socketResponse(QString response);

    void disconnect();

public: signals:
    void statBar(QString);
    void sendRawData(QString, QString);
    void sendChannelList(QJsonDocument chList);
    void sendApplicationList(QJsonDocument appList);
    void sendInputList(QJsonDocument inputList);
    void sendSOutputList(QJsonDocument sOutputList);
    void sendAppPayloadResponse(QString response);
    void sendCustomCallResponse(QString response);

private:
    QJsonDocument payload;
    QString ip;
    QString key;
};

#endif // COMMANDS_H
