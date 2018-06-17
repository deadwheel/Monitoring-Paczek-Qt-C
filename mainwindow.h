#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <listpackage.h>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDomElement>
#include <QDomDocument>
#include <inpoststatus.h>
#include <inpoststatusy.h>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void managerFinished2(QNetworkReply *reply);

    void on_numery_textChanged();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager2;
    QNetworkRequest request2;
    bool pobrane;
    InPostStatusy statusy;
};

#endif // MAINWINDOW_H
