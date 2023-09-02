#include "system.h"
#include "ui_system.h"

system::system(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::system)
{
    ui->setupUi(this);
}

system::~system()
{
    delete ui;
}

void system::on_pushButton_Off_clicked()
{
    coms.tvOff();
}

void system::on_pushButton_SOn_clicked()
{
    coms.screenOn();
}

void system::on_pushButton_SOff_clicked()
{
    coms.screenOff();
}

void system::on_pushButton_SysInfo_clicked()
{
    coms.sysInfo();
}

void system::on_pushButton_Services_clicked()
{
    coms.getServices();
}

void system::on_pushButton_SW_clicked()
{
    coms.getSwInfo();
}

void system::on_pushButton_PwrState_clicked()
{
    coms.getPwrState();
}

void system::on_pushButton_Picture_clicked()
{
    coms.getSettings("picture");
}

void system::on_pushButton_Sound_clicked()
{
    coms.getSettings("sound");
}

void system::on_pushButton_TwinTv_clicked()
{
    coms.getSettings("twinTv");
}

void system::on_pushButton_Network_clicked()
{
    coms.getSettings("network");
}

void system::on_pushButton_Option_clicked()
{
    coms.getSettings("option");
}

void system::on_pushButton_Time_clicked()
{
    coms.getSettings("time");
}

void system::on_pushButton_Close_clicked()
{
    close();
}
