#include "infopackageinpost.h"
#include "ui_infopackageinpost.h"

InfoPackageInPost::InfoPackageInPost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoPackageInPost)
{
    ui->setupUi(this);
    tableViewModel = new QStandardItemModel(ui->tableView);
       // podpinam model pod kontrolkę QTableView
    ui->tableView->setModel(tableViewModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableViewModel->setColumnCount(2); // ustaiam liczbę kolumn
       // ustawiam nagłówki kolumn
    tableViewModel->setHorizontalHeaderLabels({"Data", "Status"});
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // ustawiam zaznaczanie całych wierszy
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // ustawiam możliwość zaznaczania pojedynczego rekordu

}

void InfoPackageInPost::setPaczka(InPost paczka, InPostStatusy statusy) {

    this->paczka = paczka;
    this->statusy = statusy;
    if(this->paczka.getPaczkomatOdbiorczy() != "") {

        QLabel *label = new QLabel(this);
        label->setStyleSheet("font-size: 10pt; font-weight: bold;");
        label->setText("Paczkomat odbiorczy:");
        QLabel *label2 = new QLabel(this);
        label2->setText(this->paczka.getPaczkomatOdbiorczy());
        ui->formLayout->addRow(label,label2);

    }


    if(this->paczka.getGabaryt() != "") {

        QLabel *label3 = new QLabel(this);
        label3->setStyleSheet("font-size: 10pt; font-weight: bold;");
        label3->setText("Gabaryt:");
        QLabel *label4 = new QLabel(this);
        label4->setText(this->paczka.getGabaryt());
        ui->formLayout->addRow(label3,label4);

    }

    ui->numer->setText(this->paczka.getNumer());
    ui->nadana->setText(QDateTime::fromString(this->paczka.getDataNadania(),"yyyy-MM-ddTHH:mm:ss.zzz").toString("yyyy-MM-dd HH:mm"));
    ui->rodzaj->setText(this->paczka.getTypPaczki());

    foreach (InPostZdarzenie zdarzenie, this->paczka.getZdarzenia()) {

        int index = tableViewModel->rowCount();
        tableViewModel->setRowCount(index + 1);

        QStandardItem *dataZdarzenia = new QStandardItem(QDateTime::fromString(zdarzenie.getDataStatusu(),"yyyy-MM-ddTHH:mm:ss.zzz").toString("yyyy-MM-dd HH:mm")); // tworzę element dla pierszej kolumny

        tableViewModel->setItem(index, 0, dataZdarzenia); // dodaję do tabeli

        QStandardItem *status = new QStandardItem(fullNameStatusInPost(zdarzenie.getStatus())); // tworzę element dla drugiej kolumny

        tableViewModel->setItem(index, 1, status); // dodaję go do drugiej kolumny


    }


}

QString InfoPackageInPost::fullNameStatusInPost(QString status) {

    foreach(InPostStatus stat, this->statusy.getLista()) {

        if(stat.getName() == status) return stat.getTitle();

    }

}



void InfoPackageInPost::setPaczka(PocztaPolska paczka) {

    this->paczkaPP = paczka;
    QLabel *label = new QLabel(this);
    label->setStyleSheet("font-size: 10pt; font-weight: bold;");
    label->setText("Urząd nadania:");
    QLabel *label2 = new QLabel(this);
    label2->setText(this->paczkaPP.getUrzadNadania());
    QLabel *label3 = new QLabel(this);
    label3->setStyleSheet("font-size: 10pt; font-weight: bold;");
    label3->setText("Urząd przeznaczenia:");
    QLabel *label4 = new QLabel(this);
    label4->setText(this->paczkaPP.getUrzadPrzeznaczenia());
    ui->formLayout->addRow(label,label2);
    ui->formLayout->addRow(label3,label4);
    ui->numer->setText(this->paczkaPP.getNumer());
    ui->nadana->setText(this->paczkaPP.getDataNadania());
    ui->rodzaj->setText(this->paczkaPP.getRodzaj());

    foreach (InPostZdarzenie zdarzenie, this->paczkaPP.getZdarzenia()) {

        int index = tableViewModel->rowCount();
        tableViewModel->setRowCount(index + 1);

        QStandardItem *dataZdarzenia = new QStandardItem(zdarzenie.getDataStatusu()); // tworzę element dla pierszej kolumny

        tableViewModel->setItem(index, 0, dataZdarzenia); // dodaję do tabeli

        QStandardItem *status = new QStandardItem(zdarzenie.getStatus()); // tworzę element dla drugiej kolumny

        tableViewModel->setItem(index, 1, status); // dodaję go do drugiej kolumny


    }


}


InPost InfoPackageInPost::getPaczka() {

    return this->paczka;

}

PocztaPolska InfoPackageInPost::getPaczkaPP() {

    return this->paczkaPP;

}

InfoPackageInPost::~InfoPackageInPost()
{
    delete ui;
}
