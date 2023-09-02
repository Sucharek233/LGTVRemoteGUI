#ifndef CHANNELS_H
#define CHANNELS_H

#include "commands.h"
#include <QDialog>
#include <QJsonArray>

namespace Ui {
class channels;
}

class channels : public QDialog
{
    Q_OBJECT

public:
    explicit channels(QWidget *parent = nullptr);
    ~channels();

public slots:
    void receiveChList(QJsonDocument chList);

private slots:
    void on_pushButton_Refresh_clicked();

    void on_pushButton_Switch_clicked();

    void on_pushButton_Info_clicked();

    void on_pushButton_Up_clicked();

    void on_pushButton_Down_clicked();

    void on_pushButton_ProgInfo_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::channels *ui;

    commands coms;
};

#endif // CHANNELS_H
