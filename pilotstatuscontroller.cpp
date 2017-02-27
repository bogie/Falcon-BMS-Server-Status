#include "pilotstatuscontroller.h"

PilotStatusController::PilotStatusController(QObject *parent, MemoryHandler *mH)
    : HttpRequestHandler(parent), mH(mH)
{

}

void PilotStatusController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type","application/json; charset=UTF-8");

    QString pilotName = QString(request.getPath()).split("/").at(2);
    int pilotStatus = mH->getPilotStatus(pilotName);
    QJsonObject json;
    if(pilotStatus<0) {
        json["error"] = "Error, pilot does not exist";
    } else {
        json["pilotName"] = pilotName;
        json["pilotStatus"] = pilotStatus;
    }

    QJsonDocument doc(json);
    response.write(doc.toJson(QJsonDocument::Indented),true);
}
