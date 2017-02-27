#ifndef PILOTSTATUSCONTROLLER_H
#define PILOTSTATUSCONTROLLER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <httprequesthandler.h>
#include <memoryhandler.h>

using namespace stefanfrings;


class PilotStatusController : public HttpRequestHandler
{
    Q_OBJECT
public:
    PilotStatusController(QObject* parent=0, MemoryHandler* mH = NULL);
    void service(HttpRequest &request, HttpResponse &response);
private:
    MemoryHandler* mH;
};

#endif // PILOTSTATUSCONTROLLER_H
