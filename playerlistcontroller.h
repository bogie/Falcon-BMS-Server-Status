#ifndef PLAYERLISTCONTROLLER_H
#define PLAYERLISTCONTROLLER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include <httprequesthandler.h>
#include <memoryhandler.h>

using namespace stefanfrings;

class PlayerListController : public HttpRequestHandler
{
    Q_OBJECT
public:
    PlayerListController(QObject* parent=0, MemoryHandler* mH = NULL);
    void service(HttpRequest& request, HttpResponse& response);
private:
    MemoryHandler* mH;
};

#endif // PLAYERLISTCONTROLLER_H
