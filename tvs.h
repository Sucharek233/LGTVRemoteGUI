#ifndef TVS_H
#define TVS_H

#include "scanner.h"
#include <QDialog>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class tvs;
}

class tvs : public QDialog
{
    Q_OBJECT

public:
    explicit tvs(QWidget *parent = nullptr);
    ~tvs();

    void init();
    void addToConfig(QString name, QString ip, QString key, QString autoconnect);
    QStringList getConfig();

    void checkAutoconnect();

public: signals:
    void add(QString, bool);
    void dataForComs(QString, QString);
    void startHandshake();
    void disconnectTV();

public slots:
    void finished(QString key);

    void authScan(QString name, QString ip);

private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_Connect_clicked();

    void on_pushButton_Disconnect_clicked();

    void on_pushButton_Autoconnect_clicked();

    void on_pushButton_Scanner_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::tvs *ui;

    scanner scan;
};

#endif // TVS_H
