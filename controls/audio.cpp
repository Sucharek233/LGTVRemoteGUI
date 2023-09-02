#include "audio.h"
#include "ui_audio.h"

audio::audio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::audio)
{
    ui->setupUi(this);
}

audio::~audio()
{
    delete ui;
}

void audio::on_pushButton_Up_clicked()
{
    coms.volumeUp();
}

void audio::on_pushButton_Down_clicked()
{
    coms.volumeDown();
}

void audio::on_pushButton_Mute_clicked()
{
    coms.mute(true);
}

void audio::on_pushButton_Unmute_clicked()
{
    coms.mute(false);
}

void audio::on_horizontalSlider_Volume_valueChanged(int value)
{
    coms.setVolume(value);
}

void audio::on_pushButton_Play_clicked()
{
    coms.play();
}

void audio::on_pushButton_Pause_clicked()
{
    coms.pause();
}

void audio::on_pushButton_Stop_clicked()
{
    coms.stop();
}

void audio::on_pushButton_Rewind_clicked()
{
    coms.rewind();
}

void audio::on_pushButton_FF_clicked()
{
    coms.fastForward();
}

void audio::on_pushButton_Status_clicked()
{
    coms.audioStatus();
}

void audio::on_pushButton_Close_clicked()
{
    close();
}
