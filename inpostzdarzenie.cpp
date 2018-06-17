#include "inpostzdarzenie.h"

InPostZdarzenie::InPostZdarzenie()
{

}

void InPostZdarzenie::setDataStatusu(QString dataStatusu) {

    this->dataStatusu = dataStatusu;

}


void InPostZdarzenie::setStatus(QString status) {

    this->status = status;
}

QString InPostZdarzenie::getDataStatusu() {

    return this->dataStatusu;
}

QString InPostZdarzenie::getStatus() {

    return this->status;
}
