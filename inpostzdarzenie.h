#ifndef INPOSTZDARZENIE_H
#define INPOSTZDARZENIE_H

#include <QString>

class InPostZdarzenie
{

    QString status;
    QString dataStatusu;

public:
    InPostZdarzenie();
    QString getStatus();
    QString getDataStatusu();
    void setStatus(QString status);
    void setDataStatusu(QString dataStatusu);

};

#endif // INPOSTZDARZENIE_H
