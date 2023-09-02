#ifndef RAWDATAVIEWER_H
#define RAWDATAVIEWER_H

#include <QDialog>

namespace Ui {
class rawDataViewer;
}

class rawDataViewer : public QDialog
{
    Q_OBJECT

public:
    explicit rawDataViewer(QWidget *parent = nullptr);
    ~rawDataViewer();

public slots:
    void load(QString type, QString data);

private slots:
    void on_pushButton_Close_clicked();

private:
    Ui::rawDataViewer *ui;
};

#endif // RAWDATAVIEWER_H
