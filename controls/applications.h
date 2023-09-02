#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include "commands.h"
#include <QDialog>
#include <QJsonArray>
#include <QPlainTextEdit>
#include <QLineEdit>

namespace Ui {
class applications;
}

class applications : public QDialog
{
    Q_OBJECT

public:
    explicit applications(QWidget *parent = nullptr);
    ~applications();

    void setUpDialog();

public slots:
    void receiveAppList(QJsonDocument appList);

    void receiveResponse(QString Response);
    void sendPd();

private slots:
    void on_pushButton_Refresh_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_StartPd_clicked();

    void on_pushButton_Info_clicked();

    void on_pushButton_LaunchPoints_clicked();

    void on_pushButton_Close_W_clicked();

private:
    Ui::applications *ui;

    QDialog dialog;

    commands coms;
};

#endif // APPLICATIONS_H
