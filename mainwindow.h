#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auth.h"
#include "payloadContent.h"
#include "commands.h"
#include "tvs.h"
#include "rawdataviewer.h"

#include "controls/audio.h"
#include "controls/channels.h"
#include "controls/applications.h"
#include "controls/system.h"
#include "controls/input.h"
#include "controls/soundoutput.h"
#include "controls/notifications.h"
#include "controls/miscellaneous.h"
#include "controls/custom.h"
#include "controls/magicremote.h"

#include <QMainWindow>
#include <QtWebSockets/QWebSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QHostInfo>
#include <QNetworkInterface>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showRDV(QString type, QString data);

private slots:

    void on_pushButton_TVs_clicked();

    void on_pushButton_Audio_clicked();

    void on_pushButton_Channels_clicked();

    void on_pushButton_Apps_clicked();

    void on_pushButton_System_clicked();

    void on_pushButton_SoundOutpts_clicked();

    void on_pushButton_Inputs_clicked();

    void on_pushButton_Notifications_clicked();

    void on_pushButton_Misc_clicked();

    void on_pushButton_Custom_clicked();

    void on_pushButton_Remote_clicked();

private:
    Ui::MainWindow *ui;

    lgauth auth;
    payloadContent payloadC;
    commands coms;
    tvs tv;
    rawDataViewer rdv;

    audio aud;
    channels ch;
    applications apps;
    class system sys;
    input in;
    soundOutput sOut;
    notifications notifs;
    miscellaneous misc;
    custom cus;
    magicRemote remote;
};
#endif // MAINWINDOW_H
