#include "pilotlistcontroller.h"

PilotListController::PilotListController(QObject *parent, MemoryHandler *mH)
    : HttpRequestHandler(parent), mH(mH)
{

}

void PilotListController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type","application/json; charset=UTF-8");
    QJsonObject json;
    QJsonArray pilots;


    QMapIterator<int,QString> it(mH->getPilotList());
    while(it.hasNext()){
        it.next();
        QString pilotName = it.value();
        qDebug() << "found pilot: " << pilotName;
        QJsonObject pilot;
        pilot["name"] = pilotName;
        pilot["status"] = mH->getPilotStatus(it.key());
        pilots.append(pilot);
    }
    json["pilotsOnline"] = (int)mH->getPilotsOnline();
    json["pilots"] = pilots;

    QJsonDocument doc(json);
    qDebug() << doc.toJson();
    response.write(doc.toJson(QJsonDocument::Indented),true);
}
