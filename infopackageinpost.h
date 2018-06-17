#ifndef INFOPACKAGEINPOST_H
#define INFOPACKAGEINPOST_H

#include <QDialog>
#include <inpost.h>
#include <inpostzdarzenie.h>
#include <QStandardItem>
#include <QDebug>
#include <QDateTime>
#include <pocztapolska.h>
#include <inpoststatusy.h>
#include <inpoststatus.h>

namespace Ui {
class InfoPackageInPost;
}

class InfoPackageInPost : public QDialog
{
    Q_OBJECT

public:
    explicit InfoPackageInPost(QWidget *parent = 0);
    void setPaczka(InPost paczka, InPostStatusy statusy);
    void setPaczka(PocztaPolska paczka);
    InPost getPaczka();
    PocztaPolska getPaczkaPP();
    ~InfoPackageInPost();

private:
    Ui::InfoPackageInPost *ui;
    QStandardItemModel *tableViewModel;
    InPost paczka;
    PocztaPolska paczkaPP;
    InPostStatusy statusy;
    QString fullNameStatusInPost(QString status);

};

#endif // INFOPACKAGEINPOST_H
