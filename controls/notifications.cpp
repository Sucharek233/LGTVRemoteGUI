#include "notifications.h"
#include "ui_notifications.h"

notifications::notifications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notifications)
{
    ui->setupUi(this);
}

notifications::~notifications()
{
    delete ui;
}

void notifications::on_pushButton_Notif_clicked()
{
    QString text = ui->lineEdit_Notif->text();

    coms.createNotification(text);
}

void notifications::on_pushButton_Alert_clicked()
{
    QString text = ui->plainTextEdit_AlertText->toPlainText();
    QString bText = ui->plainTextEdit_Buttons->toPlainText();
    QStringList buttons = bText.split("\n");

    QString type;
    if (ui->radioButton_Type_Confirm->isChecked()) {
        type = "confirm";
    } else {
        type = "warning";
    }
    if (type.isEmpty()) {type = "confirm";}

    coms.createAlert(text, buttons, type);
}

void notifications::on_pushButton_Close_clicked()
{
    close();
}
