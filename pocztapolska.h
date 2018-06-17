#ifndef POCZTAPOLSKA_H
#define POCZTAPOLSKA_H

#include <QString>
#include <QList>
#include <inpostzdarzenie.h>
#include <QDomDocument>
#include <QDomElement>

class PocztaPolska
{

    QString numer;
    QString rodzaj;
    QString data_nadania;
    QString urzad_przeznaczenia;
    QString urzad_nadania;
    QList<InPostZdarzenie> zdarzenia;
    int status;


public:
    PocztaPolska();
    PocztaPolska(QString xml);
    QString getNumer();
    QString getDataNadania();
    QString getUrzadPrzeznaczenia();
    QString getUrzadNadania();
    QString getRodzaj();
    QList<InPostZdarzenie> getZdarzenia();
    int getStatus();
};

#endif // POCZTAPOLSKA_H
