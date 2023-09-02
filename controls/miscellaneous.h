#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include "commands.h"
#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class miscellaneous;
}

class miscellaneous : public QDialog
{
    Q_OBJECT

public:
    explicit miscellaneous(QWidget *parent = nullptr);
    ~miscellaneous();

private slots:
    void on_pushButton_EnterText_clicked();

    void on_pushButton_Enter_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_YT_Open_clicked();

    void on_pushButton_Browser_Open_clicked();

    void on_pushButton_3D_On_clicked();

    void on_pushButton_3D_Off_clicked();

    void on_pushButton_3D_Status_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::miscellaneous *ui;

    commands coms;
};

#endif // MISCELLANEOUS_H
