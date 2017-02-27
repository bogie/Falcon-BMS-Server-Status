#include "pilotstatuscontroller.h"

PilotStatusController::PilotStatusController(QObject *parent, MemoryHandler *mH)
    : HttpRequestHandler(parent), mH(mH)
{

}

void PilotStatusController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type","application/json; charset=UTF-8");

    QString pilotName = QString(request.getPath()).split("/").at(2);
    QJsonObject json;
    json["pilotName"] = pilotName;
    json["pilotStatus"] = mH->getPilotStatus(pilotName);

    QJsonDocument doc(json);
    response.write(doc.toJson(QJsonDocument::Indented),true);
}
