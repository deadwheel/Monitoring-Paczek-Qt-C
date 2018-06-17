#ifndef LISTPACKAGE_H
#define LISTPACKAGE_H

#include <QDialog>
#include <inpost.h>
#include <inpostzdarzenie.h>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>
#include <QList>
#include <infopackageinpost.h>
#include <pocztapolska.h>
#include <inpoststatusy.h>

namespace Ui {
class ListPackage;
}

class ListPackage : public QDialog
{
    Q_OBJECT

public:
    explicit ListPackage(QWidget *parent = 0);
    ~ListPackage();
    void setInPost(QString df, InPostStatusy statusy);
    void setPP(QString pp);

private slots:
    void managerFinished(QNetworkReply *reply);
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::ListPackage *ui;
    bool isInPost;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QStandardItemModel *tableViewModel;
    QList<InPost> listaPaczek;
    QList<PocztaPolska> listaPaczek_pp;
    InPostStatusy statusy;
    QString fullNameStatusInPost(QString status);
};

#endif // LISTPACKAGE_H
