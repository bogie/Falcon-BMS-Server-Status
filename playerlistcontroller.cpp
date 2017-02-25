#include "playerlistcontroller.h"

PlayerListController::PlayerListController(QObject *parent, MemoryHandler *mH)
    : HttpRequestHandler(parent), mH(mH)
{

}

void PlayerListController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type","application/json; charset=UTF-8");


    if(!mH->isSharedMemoryMapped){
        QJsonObject json;
        json["error"] = "Falcon BMS Server is down";
        QJsonDocument doc(json);
        qDebug() << doc.toJson();
        response.write(doc.toJson(QJsonDocument::Indented),true);
    } else {
        QJsonObject json;
        QJsonArray pilots;
        foreach (QString pilot, mH->getPilotNames()) {
            qDebug() << "found pilot: " << pilot;
            QJsonObject name;
            name["name"] = pilot;
            pilots.append(name);
        }
        json["pilotsOnline"] = (int)mH->getPilotsOnline();
        json["pilots"] = pilots;

        QJsonDocument doc(json);
        qDebug() << doc.toJson();
        response.write(doc.toJson(QJsonDocument::Indented),true);
    }
}
