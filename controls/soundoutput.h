#ifndef SOUNDOUTPUT_H
#define SOUNDOUTPUT_H

#include "commands.h"
#include <QDialog>
#include <QJsonArray>

namespace Ui {
class soundOutput;
}

class soundOutput : public QDialog
{
    Q_OBJECT

public:
    explicit soundOutput(QWidget *parent = nullptr);
    ~soundOutput();

public: signals:
    void reqRawData(QString, QString);

public slots:
    void receiveSOutputList(QJsonDocument sOutputList);

private slots:
    void on_pushButton_Refresh_clicked();

    void on_pushButton_Set_clicked();

    void on_pushButton_ViewRaw_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::soundOutput *ui;

    commands coms;
};

#endif // SOUNDOUTPUT_H
