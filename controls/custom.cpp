#include "custom.h"
#include "ui_custom.h"

custom::custom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::custom)
{
    ui->setupUi(this);

    ui->plainTextEdit_Json->setPlaceholderText("Example of setting the volume to 12:\n{\n    \"id:\":\"setvol_0\", (optional)\n    "
                                               "\"type\":\"request\",\n    \"uri\":\"ssap://audio/setVolume\",\n    "
                                               "\"payload\":{\n        \"volume\":12\n    }\n}");
}

custom::~custom()
{
    delete ui;
}

void custom::receiveResponse(QString response)
{
    ui->plainTextEdit_Response->appendPlainText(response);
}

void custom::on_pushButton_Send_clicked()
{
    QString json = ui->plainTextEdit_Json->toPlainText();

    QJsonParseError error;
    QJsonDocument jsonConverted = QJsonDocument::fromJson(json.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        QMessageBox badJson;
        badJson.setWindowTitle("Invalid JSON");
        badJson.setText("Invalid JSON.\nPlease check your JSON and correct any mistakes.\n\nError:\n" + error.errorString());
        badJson.exec();
        return;
    }
    coms.customCall(jsonConverted.object());
}

void custom::on_pushButton_Close_clicked()
{
    close();
}
