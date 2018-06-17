#include "inpost.h"

InPost::InPost()
{

}

void InPost::read(const QJsonObject &json) {
    if (json.contains("tracking_number") && json["tracking_number"].isString())
        this->numer = json["tracking_number"].toString();


    if (json.contains("created_at") && json["created_at"].isString())
        this->dataNadania = json["created_at"].toString().left(json["created_at"].toString().length()-6);

    if (json.contains("type") && json["type"].isString()) {
        this->typPaczki = json["type"].toString();

            if(this->typPaczki=="inpost_locker_standard")

                this->typPaczki = "Przesyłka paczkomatowa standardowa";

            else if(this->typPaczki== "inpost_locker_allegro")

                this->typPaczki = "Przesyłka paczkomatowa Allegro Paczkomaty InPost";

            else if(this->typPaczki== "inpost_locker_pass_thru")

                this->typPaczki = "Przesyłka paczkomatowa Podaj Dalej";

            else if(this->typPaczki== "inpost_letter_allegro")

                this->typPaczki = "Minipaczka Allegro InPost";

            else if(this->typPaczki== "inpost_courier_allegro")

                this->typPaczki = "Przesyłka kurierska Allegro Kurier InPost";

            else if(this->typPaczki== "inpost_courier_standard")

                this->typPaczki = "Przesyłka kurierska standardowa";

            else if(this->typPaczki== "inpost_courier_express_1000")

                this->typPaczki = "Przesyłka kurierska z doręczeniem do 10:00";

            else if(this->typPaczki== "inpost_courier_express_1200")

                this->typPaczki = "Przesyłka kurierska z doręczeniem do 12:00";

            else if(this->typPaczki== "inpost_courier_express_1700")

                this->typPaczki = "Przesyłka kurierska z doręczeniem do 17:00";


            else if(this->typPaczki== "inpost_courier_palette")

                this->typPaczki = "Przesyłka kurierska Paleta Standard";

            else if(this->typPaczki== "inpost_courier_local_standard")

                this->typPaczki = "Przesyłka kurierska Lokalna Standardowa";

            else if(this->typPaczki== "inpost_courier_local_express")

                this->typPaczki = "Przesyłka kurierska Lokalna Expresowa";

            else if(this->typPaczki== "inpost_courier_local_super_express")

                this->typPaczki = "Przesyłka kurierska Lokalna Super Expresowa";

            else

                this->typPaczki = "Nieokreślony";

    }

    if (json.contains("custom_attributes") && json["custom_attributes"].isObject()) {

        QJsonObject customAttr = json["custom_attributes"].toObject();

        if (customAttr.contains("target_machine_id") && customAttr["target_machine_id"].isString())
            this->paczkomatOdbiorczy = customAttr["target_machine_id"].toString();

        if (customAttr.contains("size") && customAttr["size"].isString())
            this->gabaryt = customAttr["size"].toString();

    }


    if (json.contains("tracking_details") && json["tracking_details"].isArray()) {

        QJsonArray zdarz = json["tracking_details"].toArray();

        for (int i = 0; i < zdarz.size(); ++i) {

            QJsonObject zdarzenie = zdarz[i].toObject();
            InPostZdarzenie zd;

            if (zdarzenie.contains("status") && zdarzenie["status"].isString())
                zd.setStatus(zdarzenie["status"].toString());

            if (zdarzenie.contains("datetime") && zdarzenie["datetime"].isString())
                zd.setDataStatusu(zdarzenie["datetime"].toString().left(zdarzenie["datetime"].toString().length()-6));

            zdarzenia.append(zd);

        }
    }


}



QString InPost::getDataNadania() {

    return this->dataNadania;

}

QString InPost::getGabaryt() {

    return this->gabaryt;

}

QString InPost::getPaczkomatOdbiorczy() {

    return this->paczkomatOdbiorczy;

}

QString InPost::getTypPaczki() {

    return this->typPaczki;

}

QString InPost::getNumer() {

    return this->numer;

}

QList<InPostZdarzenie> InPost::getZdarzenia() {

    return this->zdarzenia;
}
