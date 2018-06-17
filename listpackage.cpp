#include "listpackage.h"
#include "ui_listpackage.h"
#include "inpost.h"

ListPackage::ListPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListPackage)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(managerFinished(QNetworkReply*)));

    tableViewModel = new QStandardItemModel(ui->tableView);
    ui->tableView->setModel(tableViewModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableViewModel->setColumnCount(2);
    tableViewModel->setHorizontalHeaderLabels({"Numer Paczki", "Status"});
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

ListPackage::~ListPackage()
{
    delete ui;
}

void ListPackage::setInPost(QString df, InPostStatusy statusy) {

    this->statusy = statusy;
    this->isInPost = true;
    QStringList lista = df.split("\n", QString::SkipEmptyParts);

    for(int i=0;i<lista.size();i++) {

       request.setUrl(QUrl("https://api-shipx-pl.easypack24.net/v1/tracking/"+lista[i]));
       manager->get(request);

    }


}


void ListPackage::setPP(QString pp) {

    this->isInPost = false;
    QStringList lista = pp.split("\n", QString::SkipEmptyParts);

    for(int i=0;i<lista.size();i++) {

       request.setUrl(QUrl("http://tt.poczta-polska.pl/Sledzenie/services/Sledzenie?wsdl"));
       request.setHeader(QNetworkRequest::ContentTypeHeader,"text/xml");
       QByteArray xmltext = QByteArray::fromStdString("<soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\r\n  <soap:Header>\r\n    <wsse:Security xmlns:wsse=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd\" xmlns:wsu=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\">\r\n      <wsse:UsernameToken>\r\n        <wsse:Username Type=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd\">sledzeniepp</wsse:Username>\r\n        <wsse:Password Type=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordText\">PPSA</wsse:Password>\r\n        <wsse:Nonce Type=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd\">aepfhvaepifha3p4iruaq349fu34r9q</wsse:Nonce>\r\n        <wsu:Created Type=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\">1523446111642</wsu:Created>\r\n      </wsse:UsernameToken>\r\n    </wsse:Security>\r\n  </soap:Header>\r\n  <soap:Body>\r\n  <sled:sprawdzPrzesylke xmlns:sled=\"http://sledzenie.pocztapolska.pl\">\r\n      <sled:numer>"+lista[i].toStdString()+"</sled:numer>\r\n    </sled:sprawdzPrzesylke>\r\n  </soap:Body>\r\n</soap:Envelope>");
       manager->post(request,xmltext);

    }


}

void ListPackage::managerFinished(QNetworkReply *reply) {

    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();


    if(isInPost) {

            QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
            QJsonObject jsonObject = jsonResponse.object();

            InPost paczka;

            paczka.read(jsonObject);

            listaPaczek.append(paczka);

            QList<InPostZdarzenie> zdar = paczka.getZdarzenia();
            qDebug() << zdar.size();
            InPostZdarzenie ostatnie = zdar[0];

            int index = tableViewModel->rowCount();
            tableViewModel->setRowCount(index + 1);

            QStandardItem *itemCountry = new QStandardItem(paczka.getNumer()); // tworzę element dla pierszej kolumny

            tableViewModel->setItem(index, 0, itemCountry); // dodaję do tabeli

            QStandardItem *itemCapital = new QStandardItem(fullNameStatusInPost(ostatnie.getStatus())+" "+QDateTime::fromString(ostatnie.getDataStatusu(),"yyyy-MM-ddTHH:mm:ss.zzz").toString("yyyy-MM-dd HH:mm")); // tworzę element dla drugiej kolumny

            tableViewModel->setItem(index, 1, itemCapital); // dodaję go do drugiej kolumny

    }

    else {

        PocztaPolska przesylka(answer);

        if(przesylka.getStatus() == 0 || przesylka.getStatus() == 1) {

            listaPaczek_pp.append(przesylka);
            QList<InPostZdarzenie> zdar = przesylka.getZdarzenia();
            InPostZdarzenie ostatnie = zdar[zdar.size()-1];

            int index = tableViewModel->rowCount();
            tableViewModel->setRowCount(index + 1);

            QStandardItem *itemCountry = new QStandardItem(przesylka.getNumer()); // tworzę element dla pierszej kolumny

            tableViewModel->setItem(index, 0, itemCountry); // dodaję do tabeli

            QStandardItem *itemCapital = new QStandardItem(ostatnie.getStatus()+" "+ostatnie.getDataStatusu()); // tworzę element dla drugiej kolumny

            tableViewModel->setItem(index, 1, itemCapital); // dodaję go do drugiej kolumny

        }

    }


}


QString ListPackage::fullNameStatusInPost(QString status) {

    foreach(InPostStatus stat, this->statusy.getLista()) {

        if(stat.getName() == status) return stat.getTitle();

    }

}

void ListPackage::on_tableView_doubleClicked(const QModelIndex &index)
{

    int ro = index.row();

    if(listaPaczek.size()>0) {

        InfoPackageInPost *details = new InfoPackageInPost;
        details->setPaczka(listaPaczek[ro], this->statusy);
        details->setWindowTitle(
                    "INPOST: "+listaPaczek[ro].getNumer());

        details->show();

    }

    else {

        InfoPackageInPost *details = new InfoPackageInPost;
        details->setPaczka(listaPaczek_pp[ro]);
        details->setWindowTitle(
                    "Poczta Polska: "+listaPaczek_pp[ro].getNumer());

        details->show();

    }


}
