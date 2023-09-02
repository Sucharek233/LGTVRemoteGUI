#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include "commands.h"
#include <QDialog>

namespace Ui {
class notifications;
}

class notifications : public QDialog
{
    Q_OBJECT

public:
    explicit notifications(QWidget *parent = nullptr);
    ~notifications();

private slots:
    void on_pushButton_Notif_clicked();

    void on_pushButton_Alert_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::notifications *ui;

    commands coms;
};

#endif // NOTIFICATIONS_H
