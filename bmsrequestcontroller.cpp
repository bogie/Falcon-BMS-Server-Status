#include "bmsrequestcontroller.h"

BMSRequestController::BMSRequestController(QObject *parent, MemoryHandler *mH)
    : HttpRequestHandler(parent), mH(mH), pLController(this,mH), pSController(this,mH)
{
}

void BMSRequestController::service(HttpRequest &request, HttpResponse &response){
    QByteArray path = request.getPath();

    if(!mH->isSharedMemoryMapped || !mH->isBMSRunning()){
        response.setHeader("Content-Type","application/json; charset=UTF-8");
        QJsonObject json;
        json["error"] = "Falcon BMS Server is down";
        QJsonDocument doc(json);
        qDebug() << doc.toJson();
        response.write(doc.toJson(QJsonDocument::Indented),true);
    } else {
        if(path == "/" || path == "/playerlist") {
            pLController.service(request,response);
        } else if(QString(path).startsWith("/pilotstatus/")) {
            pSController.service(request,response);
        }else if(QString(path).startsWith("/currenttime")){
            response.setHeader("Content-Type","application/json; charset=UTF-8");
            QJsonObject json;
            json["currentTime"] = mH->getCurrentTime();
            QJsonDocument doc(json);
            response.write(doc.toJson(QJsonDocument::Indented),true);
        } else {
            response.setStatus(404,"Not found");
            response.write("The supplied URL could not be found.");
        }
    }
}
