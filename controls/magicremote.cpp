#include "magicremote.h"
#include "ui_magicremote.h"

magicRemote::magicRemote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::magicRemote)
{
    ui->setupUi(this);

    QLabel *track = new Trackpad("Trackpad\nLeft drag to move\nMiddle drag to scroll\nRight click to click", this);
    ui->gridLayout_Trackpad->layout()->addWidget(track);
}

QPoint lastMousePos(0, 0);
QString button;
double moveSen = 10;
double scrollSen = 10;
void Trackpad::mouseMoveEvent(QMouseEvent *event)
{
    QPoint currentMousePos = event->pos();

    double dx = currentMousePos.x() - lastMousePos.x();
    double dy = currentMousePos.y() - lastMousePos.y();

    if (button == "middle") {
        double dxS = dx / 20 * scrollSen * -1;
        double dyS = dy / 20 * scrollSen * -1;

        move.cursorScroll(QString::number(dxS), QString::number(dyS));
        lastMousePos = currentMousePos;
        return;
    }

    double dxM = dx / 10 * moveSen;
    double dyM = dy / 10 * moveSen;

    move.cursorMove(QString::number(dxM), QString::number(dyM), "1");

    lastMousePos = currentMousePos;
}
void Trackpad::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        button = "right";
        move.cursorClick();
    }
    if (event->button() == Qt::LeftButton) {button = "left";}
    if (event->button() == Qt::MiddleButton) {button = "middle";}
}
void Trackpad::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {button = "right";}
}

magicRemote::~magicRemote()
{
    delete ui;
}

void magicRemote::on_pushButton_StartService_clicked()
{
    coms.startRemote();
}

void magicRemote::on_pushButton_StopService_clicked()
{
    coms.stopRemote();
}

void magicRemote::on_pushButton_Off_clicked()
{
    coms.tvOff();
}

void magicRemote::on_pushButton_1_clicked()
{
    coms.cursorPress("1");
}

void magicRemote::on_pushButton_2_clicked()
{
    coms.cursorPress("2");
}

void magicRemote::on_pushButton_3_clicked()
{
    coms.cursorPress("3");
}

void magicRemote::on_pushButton_4_clicked()
{
    coms.cursorPress("4");
}

void magicRemote::on_pushButton_5_clicked()
{
    coms.cursorPress("5");
}

void magicRemote::on_pushButton_6_clicked()
{
    coms.cursorPress("6");
}

void magicRemote::on_pushButton_7_clicked()
{
    coms.cursorPress("7");
}

void magicRemote::on_pushButton_8_clicked()
{
    coms.cursorPress("8");
}

void magicRemote::on_pushButton_9_clicked()
{
    coms.cursorPress("9");
}

void magicRemote::on_pushButton_0_clicked()
{
    coms.cursorPress("0");
}

void magicRemote::on_pushButton_List_clicked()
{
    coms.cursorPress("LIST");
}

void magicRemote::on_pushButton_Info_clicked()
{
    coms.cursorPress("INFO");
}

void magicRemote::on_pushButton_VolUp_clicked()
{
    coms.cursorPress("VOLUMEUP");
}

void magicRemote::on_pushButton_VolDown_clicked()
{
    coms.cursorPress("VOLUMEDOWN");
}

void magicRemote::on_pushButton_Mute_clicked()
{
    coms.cursorPress("MUTE");
}

void magicRemote::on_pushButton_ChUp_clicked()
{
    coms.cursorPress("CHANNELUP");
}

void magicRemote::on_pushButton_ChDown_clicked()
{
    coms.cursorPress("CHANNELDOWN");
}

void magicRemote::on_pushButton_Home_clicked()
{
    coms.cursorPress("HOME");
}

void magicRemote::on_pushButton_Settings_clicked()
{
    coms.cursorPress("MENU");
}

void magicRemote::on_pushButton_Back_clicked()
{
    coms.cursorPress("BACK");
}

void magicRemote::on_pushButton_Exit_clicked()
{
    coms.cursorPress("EXIT");
}

void magicRemote::on_pushButton_Up_clicked()
{
    coms.cursorPress("UP");
}

void magicRemote::on_pushButton_Down_clicked()
{
    coms.cursorPress("DOWN");
}

void magicRemote::on_pushButton_Left_clicked()
{
    coms.cursorPress("LEFT");
}

void magicRemote::on_pushButton_Right_clicked()
{
    coms.cursorPress("RIGHT");
}

void magicRemote::on_pushButton_Ok_clicked()
{
    coms.cursorPress("ENTER");
}

void magicRemote::on_pushButton_Red_clicked()
{
    coms.cursorPress("RED");
}

void magicRemote::on_pushButton_Green_clicked()
{
    coms.cursorPress("GREEN");
}

void magicRemote::on_pushButton_Yellow_clicked()
{
    coms.cursorPress("YELLOW");
}

void magicRemote::on_pushButton_Blue_clicked()
{
    coms.cursorPress("BLUE");
}

void magicRemote::on_pushButton_YT_clicked()
{
    coms.startApp("youtube.leanback.v4");
}

void magicRemote::on_pushButton_Netflix_clicked()
{
    coms.startApp("netflix");
}

void magicRemote::on_pushButton_PrVideo_clicked()
{
    coms.startApp("amazon");
}

void magicRemote::on_pushButton_DisneyPlus_clicked()
{
    coms.startApp("com.disney.disneyplus-prod");
}

void magicRemote::on_pushButton_Rakuten_clicked()
{
    coms.startApp("ui30");
}

void magicRemote::on_pushButton_Play_clicked()
{
    coms.cursorPress("PLAY");
}

void magicRemote::on_pushButton_Pause_clicked()
{
    coms.cursorPress("PAUSE");
}

void magicRemote::on_pushButton_Stop_clicked()
{
    coms.cursorPress("PAUSE");
}

void magicRemote::on_pushButton_FastForward_clicked()
{
    coms.cursorPress("FASTFORWARD");
}

void magicRemote::on_pushButton_Rewind_clicked()
{
    coms.cursorPress("REWIND");
}

void magicRemote::on_pushButton_CustomBtn_clicked()
{
    QString btn = ui->lineEdit_CustomBtn->text();
    coms.cursorPress(btn);
}

void magicRemote::on_pushButton_Click_clicked()
{
    coms.cursorClick();
}

void magicRemote::on_pushButton_ScrollUp_clicked()
{
    coms.cursorScroll("0", "1");
}

void magicRemote::on_pushButton_ScrollDown_clicked()
{
    coms.cursorScroll("0", "-1");
}

void magicRemote::on_pushButton_Move_clicked()
{
    QString x = QString::number(ui->spinBox_X->value());
    QString y = QString::number(ui->spinBox_Y->value());

    coms.cursorMove(x, y, "1");
}

void magicRemote::on_pushButton_Guide_clicked()
{
    coms.cursorPress("GUIDE");
}

void magicRemote::on_pushButton_LegacyList_clicked()
{
    coms.cursorPress("DASH");
}

void magicRemote::on_pushButton_AD_clicked()
{
    coms.cursorPress("AD");
}

void magicRemote::on_pushButton_Language_clicked()
{
    coms.cursorPress("SAP");
}

void magicRemote::on_pushButton_CC_clicked()
{
    coms.cursorPress("CC");
}


void magicRemote::on_pushButton_Close_clicked()
{
    close();
}

void magicRemote::on_spinBox_Move_valueChanged(int arg1)
{
    moveSen = arg1;
}
void magicRemote::on_spinBox_Scroll_valueChanged(int arg1)
{
    scrollSen = arg1;
}
