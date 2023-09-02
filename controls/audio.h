#ifndef AUDIO_H
#define AUDIO_H

#include "commands.h"
#include <QDialog>

namespace Ui {
class audio;
}

class audio : public QDialog
{
    Q_OBJECT

public:
    explicit audio(QWidget *parent = nullptr);
    ~audio();

private slots:
    void on_pushButton_Up_clicked();

    void on_pushButton_Down_clicked();

    void on_pushButton_Mute_clicked();

    void on_pushButton_Unmute_clicked();

    void on_horizontalSlider_Volume_valueChanged(int value);

    void on_pushButton_Play_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Rewind_clicked();

    void on_pushButton_FF_clicked();

    void on_pushButton_Status_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::audio *ui;

    commands coms;
};

#endif // AUDIO_H
