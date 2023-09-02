#ifndef INPUT_H
#define INPUT_H

#include "commands.h"
#include <QDialog>
#include <QJsonArray>

namespace Ui {
class input;
}

class input : public QDialog
{
    Q_OBJECT

public:
    explicit input(QWidget *parent = nullptr);
    ~input();

public: signals:
    void reqRawData(QString, QString);

public slots:
    void receiveInputList(QJsonDocument inputList);

private slots:
    void on_pushButton_Refresh_clicked();

    void on_pushButton_Set_clicked();

    void on_pushButton_ViewRaw_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::input *ui;

    commands coms;
};

#endif // INPUT_H
