#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QJsonDocument pd = payloadC.getPayload();

    auth.setPayload(pd);
    coms.setPd(pd);

    ui->statusbar->showMessage("Connect to a TV");

    connect(&tv, &tvs::add, &auth, &lgauth::authorize, Qt::AutoConnection);
    connect(&auth, &lgauth::sendKey, &tv, &tvs::finished, Qt::AutoConnection);
    connect(&tv, &tvs::dataForComs, &coms, &commands::setIPKey, Qt::AutoConnection);
    connect(&auth,SIGNAL(statBar(QString)),ui->statusbar,SLOT(showMessage(QString)), Qt::AutoConnection);
    connect(&tv, &tvs::startHandshake, &coms, &commands::handshake, Qt::AutoConnection);
    connect(&tv, &tvs::disconnectTV, &coms, &commands::disconnect, Qt::AutoConnection);

    connect(&coms,SIGNAL(statBar(QString)),ui->statusbar,SLOT(showMessage(QString)), Qt::AutoConnection);
    connect(&coms, &commands::sendRawData, this, &MainWindow::showRDV, Qt::AutoConnection);
    connect(&in, &input::reqRawData, this, &MainWindow::showRDV, Qt::AutoConnection);
    connect(&sOut, &soundOutput::reqRawData, this, &MainWindow::showRDV, Qt::AutoConnection);

    connect(&coms, &commands::sendChannelList, &ch, &channels::receiveChList, Qt::AutoConnection);
    connect(&coms, &commands::sendApplicationList, &apps, &applications::receiveAppList, Qt::AutoConnection);
    connect(&coms, &commands::sendInputList, &in, &input::receiveInputList, Qt::AutoConnection);
    connect(&coms, &commands::sendSOutputList, &sOut, &soundOutput::receiveSOutputList, Qt::AutoConnection);
    connect(&coms, &commands::sendAppPayloadResponse, &apps, &applications::receiveResponse, Qt::AutoConnection);
    connect(&coms, &commands::sendCustomCallResponse, &cus, &custom::receiveResponse, Qt::AutoConnection);

    tv.checkAutoconnect();

}

MainWindow::~MainWindow()
{
    coms.disconnect();
    coms.stopRemote();

    delete ui;
}

void MainWindow::showRDV(QString type, QString data)
{
    rdv.load(type, data);
    rdv.exec();
}

void MainWindow::on_pushButton_TVs_clicked()
{
    tv.exec();
}

void MainWindow::on_pushButton_Audio_clicked()
{
    aud.exec();
}

void MainWindow::on_pushButton_Channels_clicked()
{
    ch.exec();
}

void MainWindow::on_pushButton_Apps_clicked()
{
    apps.exec();
}

void MainWindow::on_pushButton_System_clicked()
{
    sys.exec();
}

void MainWindow::on_pushButton_Inputs_clicked()
{
    in.exec();
}

void MainWindow::on_pushButton_SoundOutpts_clicked()
{
    sOut.exec();
}

void MainWindow::on_pushButton_Notifications_clicked()
{
    notifs.exec();
}

void MainWindow::on_pushButton_Misc_clicked()
{
    misc.exec();
}

void MainWindow::on_pushButton_Custom_clicked()
{
    cus.exec();
}

void MainWindow::on_pushButton_Remote_clicked()
{
    remote.exec();
}
