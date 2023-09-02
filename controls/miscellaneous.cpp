#include "miscellaneous.h"
#include "ui_miscellaneous.h"

miscellaneous::miscellaneous(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::miscellaneous)
{
    ui->setupUi(this);
}

miscellaneous::~miscellaneous()
{
    delete ui;
}

void miscellaneous::on_pushButton_EnterText_clicked()
{
    QInputDialog getText;
    getText.setOptions(QInputDialog::UsePlainTextEditForTextInput);
    getText.setWindowTitle("Enter Text");
    getText.setLabelText("Enter text you want to send to your TV.");
    if (getText.exec() == QInputDialog::Accepted) {
        QString text = getText.textValue();
        coms.enterText(text);
    }
}

void miscellaneous::on_pushButton_Enter_clicked()
{
    coms.sendEnter();
}

void miscellaneous::on_pushButton_Delete_clicked()
{
    int num = ui->spinBox_Delete->value();
    coms.deleteText(num);
}

void miscellaneous::on_pushButton_YT_Open_clicked()
{
    QString url = ui->lineEdit_YT_URL->text();
    if (!url.startsWith("https://www.youtube.com/watch?v=")) {
        QMessageBox alert;
        alert.setWindowTitle("Invalid URL");
        alert.setText("Invalid url.\nPlease make sure the url you entered is in this format:\nhttps://www.youtube.com/watch?v=dQw4w9WgXcQ");
        alert.exec();
        return;
    }
    coms.openYTLink(url);
}

void miscellaneous::on_pushButton_Browser_Open_clicked()
{
    QString url = ui->lineEdit_Browser_URL->text();

    if (!url.startsWith("http")) {
        QMessageBox alert;
        alert.setWindowTitle("Invalid URL");
        alert.setText("Invalid url.\nPlease make sure the url you entered is in this format:\nhttp(s)://google.com");
        alert.exec();
        return;
    }
    coms.openBrowserUrl(url);
}

void miscellaneous::on_pushButton_3D_On_clicked()
{
    coms.v3DOn();
}

void miscellaneous::on_pushButton_3D_Off_clicked()
{
    coms.v3DOff();
}

void miscellaneous::on_pushButton_3D_Status_clicked()
{
    coms.v3DStatus();
}

void miscellaneous::on_pushButton_Close_clicked()
{
    close();
}
