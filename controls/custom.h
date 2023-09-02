#ifndef CUSTOM_H
#define CUSTOM_H

#include "commands.h"
#include <QDialog>
#include <QJsonDocument>

namespace Ui {
class custom;
}

class custom : public QDialog
{
    Q_OBJECT

public:
    explicit custom(QWidget *parent = nullptr);
    ~custom();

public slots:
    void receiveResponse(QString response);

private slots:
    void on_pushButton_Send_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::custom *ui;

    commands coms;
};

#endif // CUSTOM_H
