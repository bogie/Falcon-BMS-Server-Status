#ifndef BMSREQUESTCONTROLLER_H
#define BMSREQUESTCONTROLLER_H

#include "httprequesthandler.h"
#include "pilotlistcontroller.h"
#include "pilotstatuscontroller.h"
#include "memoryhandler.h"

using namespace stefanfrings;

class BMSRequestController : public HttpRequestHandler
{
    Q_OBJECT
public:
    BMSRequestController(QObject* parent=0, MemoryHandler* mH = NULL);
    void service(HttpRequest &request, HttpResponse &response);
private:
    MemoryHandler* mH;
    PilotListController pLController;
    PilotStatusController pSController;
};

#endif // BMSREQUESTCONTROLLER_H
