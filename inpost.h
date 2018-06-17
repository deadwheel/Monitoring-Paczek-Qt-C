#ifndef INPOST_H
#define INPOST_H

#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QList>
#include <inpostzdarzenie.h>

class InPost
{

    QString numer;
    QString dataNadania;
    QString typPaczki;
    QString gabaryt;
    QString paczkomatOdbiorczy;
    QList<InPostZdarzenie> zdarzenia;

public:
    InPost();
    void read(const QJsonObject &json);
    QString getNumer();
    QString getDataNadania();
    QString getTypPaczki();
    QString getGabaryt();
    QString getPaczkomatOdbiorczy();
    QList<InPostZdarzenie> getZdarzenia();
};

#endif // INPOST_H
