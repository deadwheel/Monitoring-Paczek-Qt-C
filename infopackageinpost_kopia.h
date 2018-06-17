#ifndef INFOPACKAGEINPOST_H
#define INFOPACKAGEINPOST_H

#include <QDialog>
#include <inpost.h>
#include <inpostzdarzenie.h>
#include <QStandardItem>
#include <QDebug>
#include <QDateTime>

namespace Ui {
class InfoPackageInPost;
}

class InfoPackageInPost : public QDialog
{
    Q_OBJECT

public:
    explicit InfoPackageInPost(QWidget *parent = 0);
    void setPaczka(InPost paczka);
    InPost getPaczka();
    ~InfoPackageInPost();

private:
    Ui::InfoPackageInPost *ui;
    QStandardItemModel *tableViewModel;
    InPost paczka;

};

#endif // INFOPACKAGEINPOST_H
