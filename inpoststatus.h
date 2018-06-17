#ifndef INPOSTSTATUS_H
#define INPOSTSTATUS_H

#include <QString>


class InPostStatus
{

    QString name;
    QString title;
    QString description;

public:
    InPostStatus(QString name, QString title, QString description);
    QString getName();
    QString getTitle();
    QString getDescription();
};

#endif // INPOSTSTATUS_H
