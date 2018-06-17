#include "pocztapolska.h"

PocztaPolska::PocztaPolska() {


}

PocztaPolska::PocztaPolska(QString xml)
{

    QDomDocument document;
    QDomElement  root;

    document.setContent(xml);


    this->status = document.elementsByTagName("ax21:status").at(0).toElement().text().toInt();
    this->numer = document.elementsByTagName("ax21:numer").at(0).toElement().text();

    if(this->status == 0 || this->status == 1) {

        this->data_nadania = document.elementsByTagName("ax21:dataNadania").at(0).toElement().text();
        this->rodzaj = document.elementsByTagName("ax21:rodzPrzes").at(0).toElement().text();
        this->urzad_nadania = document.elementsByTagName("ax21:urzadNadania").at(0).toElement().elementsByTagName("ax21:nazwa").at(0).toElement().text();
        this->urzad_przeznaczenia = document.elementsByTagName("ax21:urzadPrzezn").at(0).toElement().elementsByTagName("ax21:nazwa").at(0).toElement().text();
        QDomNodeList  zdarz = document.elementsByTagName("ax21:zdarzenie");

        for(int index = 0; index < zdarz.count(); index++){

            QDomElement zd = zdarz.at(index).toElement();
            InPostZdarzenie zdarzenie;

            zdarzenie.setDataStatusu(zd.firstChildElement("ax21:czas").text());
            zdarzenie.setStatus(zd.firstChildElement("ax21:nazwa").text());
            zdarzenia.append(zdarzenie);

        }


    }

}

QString PocztaPolska::getNumer() {

    return this->numer;

}
QString PocztaPolska::getDataNadania() {

    return this->data_nadania;

}
QString PocztaPolska::getUrzadPrzeznaczenia() {

    return this->urzad_przeznaczenia;

}
QString PocztaPolska::getUrzadNadania() {

    return this->urzad_nadania;

}
QString PocztaPolska::getRodzaj() {

    return this->rodzaj;

}
QList<InPostZdarzenie> PocztaPolska::getZdarzenia() {

    return this->zdarzenia;

}
int PocztaPolska::getStatus() {

    return this->status;

}
