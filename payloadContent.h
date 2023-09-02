#ifndef PAYLOADCONTENT_H
#define PAYLOADCONTENT_H

#endif // PAYLOADCONTENT_H

#include <QJsonDocument>
#include <QFile>

class payloadContent
{
public:
    QJsonDocument getPayload()
    {
        QFile payloadFile(":/json/payload.json");
        payloadFile.open(QIODevice::ReadOnly);
        QString payloadData = payloadFile.readAll();
        payloadFile.close();

        QJsonDocument data = QJsonDocument::fromJson(payloadData.toUtf8());

        return data;
    }
};
