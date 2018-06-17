#include "inpoststatusy.h"

InPostStatusy::InPostStatusy()
{

}

QList<InPostStatus> InPostStatusy::getLista() {

    return this->lista_statusow;

}


void InPostStatusy::readJson(const QJsonObject &json) {

    if (json.contains("items") && json["items"].isArray()) {

        QJsonArray zdarz = json["items"].toArray();

        for (int i = 0; i < zdarz.size(); ++i) {

            QJsonObject zdarzenie = zdarz[i].toObject();

            if (zdarzenie.contains("name") && zdarzenie["name"].isString() && zdarzenie.contains("title") && zdarzenie["title"].isString() && zdarzenie.contains("description") && zdarzenie["description"].isString()) {
                InPostStatus status(zdarzenie["name"].toString(),zdarzenie["title"].toString(),zdarzenie["description"].toString());
                lista_statusow.append(status);
            }


        }
    }

}
