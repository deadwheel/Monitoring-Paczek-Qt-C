#include "inpoststatus.h"

InPostStatus::InPostStatus(QString name, QString title, QString description)
{

    this->name = name;
    this->title = title;
    this->description = description;

}

QString InPostStatus::getName() {

    return this->name;

}

QString InPostStatus::getDescription() {

    return this->description;

}

QString InPostStatus::getTitle() {

    return this->title;

}
