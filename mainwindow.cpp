#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->pobrane = false;
    manager2 = new QNetworkAccessManager(this);
    QObject::connect(manager2,SIGNAL(finished(QNetworkReply*)),this,SLOT(managerFinished2(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    qDebug() << QSslSocket::supportsSsl();
    qDebug()<<"SSL version use for build: "<<QSslSocket::sslLibraryBuildVersionString();
    qDebug()<<"SSL version use for run-time: "<<QSslSocket::sslLibraryVersionNumber();
    qDebug()<<QCoreApplication::libraryPaths();

    if(this->pobrane) {

        ListPackage *sub = new ListPackage;
        sub->setInPost(ui->numery->toPlainText(), this->statusy);
        sub->setWindowTitle("Przesyłki InPost");
        sub->show();


        ListPackage *pp = new ListPackage;
        pp->setPP(ui->numery->toPlainText());
        pp->setWindowTitle("Przesyłki Poczta Polska");
        pp->show();

    }

    else {
        request2.setUrl(QUrl("https://api-shipx-pl.easypack24.net/v1/statuses"));
        manager2->get(request2);
    }


}


void MainWindow::managerFinished2(QNetworkReply *reply) {

    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

//    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
//    qDebug() << QVariant(statusCode).toString();

//    qDebug() << QSslSocket::supportsSsl();
//    qDebug() << reply->readAll();
//    qDebug() << reply->errorString();

    QString answer = reply->readAll();
    qDebug() << answer;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    this->statusy.readJson(jsonObject);
    this->pobrane = true;

    ui->pushButton->click();

//    ListPackage *sub = new ListPackage;
//    sub->setInPost(ui->numery->toPlainText());
//    sub->setWindowTitle("Przesyłki InPost");
//    sub->show();


//    ListPackage *pp = new ListPackage;
//    pp->setPP(ui->numery->toPlainText());
//    pp->setWindowTitle("Przesyłki Poczta Polska");
//    pp->show();

}

void MainWindow::on_numery_textChanged()
{
    if(ui->numery->toPlainText().length() >=6) ui->pushButton->setEnabled(true);
    else ui->pushButton->setEnabled(false);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "C:/",
                                                    tr("Text files (*.txt)"));

    if(fileName != "") {

        qDebug() << fileName;
        QFile f(fileName);

        if (!f.open(QFile::ReadOnly | QFile::Text)) return;

        QTextStream in(&f);
        QString numery = in.readAll();
        qDebug() << numery;
        ui->numery->document()->setPlainText(numery);
        qDebug() << ui->numery->toPlainText();

    }

}
