#ifndef PILOTLISTCONTROLLER_H
#define PILOTLISTCONTROLLER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include <httprequesthandler.h>
#include <memoryhandler.h>

using namespace stefanfrings;

class PilotListController : public HttpRequestHandler
{
    Q_OBJECT
public:
    PilotListController(QObject* parent=0, MemoryHandler* mH = NULL);
    void service(HttpRequest& request, HttpResponse& response);
private:
    MemoryHandler* mH;
};

#endif // PILOTISTCONTROLLER_H
