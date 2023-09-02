#ifndef SYSTEM_H
#define SYSTEM_H

#include "commands.h"
#include <QDialog>

namespace Ui {
class system;
}

class system : public QDialog
{
    Q_OBJECT

public:
    explicit system(QWidget *parent = nullptr);
    ~system();

private slots:
    void on_pushButton_Off_clicked();

    void on_pushButton_SOn_clicked();

    void on_pushButton_SOff_clicked();

    void on_pushButton_SysInfo_clicked();

    void on_pushButton_Services_clicked();

    void on_pushButton_SW_clicked();

    void on_pushButton_PwrState_clicked();

    void on_pushButton_Picture_clicked();

    void on_pushButton_Sound_clicked();

    void on_pushButton_TwinTv_clicked();

    void on_pushButton_Network_clicked();

    void on_pushButton_Option_clicked();

    void on_pushButton_Time_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::system *ui;

    commands coms;
};

#endif // SYSTEM_H
