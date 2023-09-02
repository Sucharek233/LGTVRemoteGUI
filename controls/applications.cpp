#include "applications.h"
#include "ui_applications.h"

QStringList appIdList;

QString responses;
QPlainTextEdit *payload;
QPlainTextEdit *response;
QLineEdit *appId;

applications::applications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::applications)
{
    ui->setupUi(this);

    setUpDialog();
}

applications::~applications()
{
    delete ui;
}

void applications::receiveAppList(QJsonDocument appList)
{
    ui->listWidget_Apps->clear();
    appIdList.clear();

    QJsonObject root = appList.object();
    QJsonObject payload = root["payload"].toObject();
    QJsonArray appListArray = payload["apps"].toArray();
    for (const QJsonValue &appValue : appListArray) {
        QJsonObject app = appValue.toObject();
        QString appName;
        QString appId;
        if (!app.contains("id")) {continue;}
        if (app.contains("title")) {
            appId = app["id"].toString();
            appName = app["title"].toString() + " (" + appId + ")";
            if (app["title"].toString() == appId) {appName = appId;}
            if (appName.simplified().isEmpty()) {appName = appId;}
        } else {
            appName = app["id"].toString();
            appId = app["id"].toString();
        }

        appIdList.append(appId);

        QListWidgetItem *item = new QListWidgetItem;
        item->setText(appName);
        ui->listWidget_Apps->addItem(item);
    }
}

void applications::on_pushButton_Refresh_clicked()
{
    coms.getAppList();
}

void applications::on_pushButton_Start_clicked()
{
    int app = ui->listWidget_Apps->currentRow();
    if (app < 0) {return;}

    coms.startApp(appIdList.at(app));
}

void applications::on_pushButton_Close_clicked()
{
    int app = ui->listWidget_Apps->currentRow();
    if (app < 0) {return;}

    coms.closeApp(appIdList.at(app));
}

void applications::on_pushButton_StartPd_clicked()
{
    if (!appIdList.isEmpty()) {
        int app = ui->listWidget_Apps->currentRow();
        if (app > -1) {
            appId->setText(appIdList.at(app));
        }
    }

    dialog.exec();
}
void applications::setUpDialog()
{
    dialog.setWindowTitle("Start App With Payload");

    QLabel *appLabel = new QLabel("Application ID", &dialog);

    appId = new QLineEdit(&dialog);
    QLabel *payloadLabel = new QLabel("Payload", &dialog);
    payload = new QPlainTextEdit(&dialog);
    QPushButton *send = new QPushButton("Send", &dialog);
    QLabel *responseLabel = new QLabel("Response", &dialog);
    response = new QPlainTextEdit(&dialog);
    QPushButton *close = new QPushButton("Close", &dialog);

    response->setReadOnly(true);
    payload->setPlaceholderText("Example of payload of starting a youtube video:\n\n{\n    \"params\":{\n        "
                                "\"contentTarget\":\"https://www.youtube.com/watch?v=dQw4w9WgXcQ\"\n    }\n}");

    connect(send, &QPushButton::clicked, this, &applications::sendPd);
    connect(close, &QPushButton::clicked, &dialog, &QDialog::close);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    mainLayout->addWidget(appLabel);
    mainLayout->addWidget(appId);
    mainLayout->addWidget(payloadLabel);
    mainLayout->addWidget(payload);
    mainLayout->addWidget(send);
    mainLayout->addWidget(responseLabel);
    mainLayout->addWidget(response);
    mainLayout->addWidget(close);

    dialog.setLayout(mainLayout);
}
void applications::receiveResponse(QString Response)
{
    qDebug() << "appending" << Response;
    response->appendPlainText(Response);
}
void applications::sendPd()
{
    QString pd = payload->toPlainText();
    QString id = appId->text();

    QJsonParseError error;
    QJsonDocument payload = QJsonDocument::fromJson(pd.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        QMessageBox badJson;
        badJson.setWindowTitle("Invalid Payload");
        badJson.setText("Invalid Payload.\nPlease check your payload and correct any mistakes.\n\nError:\n" + error.errorString());
        badJson.exec();
        return;
    }

    coms.startAppPd(payload.object(), id);
}

void applications::on_pushButton_Info_clicked()
{
    coms.getCurrAppInfo();
}

void applications::on_pushButton_LaunchPoints_clicked()
{
    coms.listLaunchPoints();
}

void applications::on_pushButton_Close_W_clicked()
{
    close();
}
