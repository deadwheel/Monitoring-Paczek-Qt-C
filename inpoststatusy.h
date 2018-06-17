#ifndef INPOSTSTATUSY_H
#define INPOSTSTATUSY_H

#include <inpoststatus.h>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


class InPostStatusy
{

    QList<InPostStatus> lista_statusow;

public:
    InPostStatusy();
    QList<InPostStatus> getLista();
    void readJson(const QJsonObject &json);
};

#endif // INPOSTSTATUSY_H
