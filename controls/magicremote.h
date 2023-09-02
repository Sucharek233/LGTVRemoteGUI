#ifndef MAGICREMOTE_H
#define MAGICREMOTE_H

#include "commands.h"
#include <QDialog>
#include <QStatusBar>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>

class Trackpad : public QLabel
{
    Q_OBJECT

public:
    Trackpad(const QString &text, QWidget *parent = nullptr) : QLabel(text, parent) {
        setFrameStyle(QFrame::Box | QFrame::Plain);
        setLineWidth(2);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setAlignment(Qt::AlignCenter);
        QFont size; size.setPointSize(11); setFont(size);
    }

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    commands move;
};


namespace Ui {
class magicRemote;
}

class magicRemote : public QDialog
{
    Q_OBJECT

public:
    explicit magicRemote(QWidget *parent = nullptr);
    ~magicRemote();

private slots:
    void on_pushButton_StartService_clicked();

    void on_pushButton_StopService_clicked();

    void on_pushButton_Off_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_List_clicked();

    void on_pushButton_Info_clicked();

    void on_pushButton_VolUp_clicked();

    void on_pushButton_VolDown_clicked();

    void on_pushButton_Mute_clicked();

    void on_pushButton_ChUp_clicked();

    void on_pushButton_ChDown_clicked();

    void on_pushButton_Home_clicked();

    void on_pushButton_Settings_clicked();

    void on_pushButton_Back_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Up_clicked();

    void on_pushButton_Down_clicked();

    void on_pushButton_Left_clicked();

    void on_pushButton_Right_clicked();

    void on_pushButton_Ok_clicked();

    void on_pushButton_Red_clicked();

    void on_pushButton_Green_clicked();

    void on_pushButton_Yellow_clicked();

    void on_pushButton_Blue_clicked();

    void on_pushButton_YT_clicked();

    void on_pushButton_Netflix_clicked();

    void on_pushButton_PrVideo_clicked();

    void on_pushButton_DisneyPlus_clicked();

    void on_pushButton_Rakuten_clicked();

    void on_pushButton_Play_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_FastForward_clicked();

    void on_pushButton_Rewind_clicked();

    void on_pushButton_CustomBtn_clicked();

    void on_pushButton_Click_clicked();

    void on_pushButton_ScrollUp_clicked();

    void on_pushButton_ScrollDown_clicked();

    void on_pushButton_Move_clicked();

    void on_pushButton_Guide_clicked();

    void on_pushButton_LegacyList_clicked();

    void on_pushButton_AD_clicked();

    void on_pushButton_Language_clicked();

    void on_pushButton_CC_clicked();

    void on_pushButton_Close_clicked();

    void on_spinBox_Move_valueChanged(int arg1);

    void on_spinBox_Scroll_valueChanged(int arg1);

private:
    Ui::magicRemote *ui;

    QStatusBar *statusbar;

    commands coms;
};

#endif // MAGICREMOTE_H
