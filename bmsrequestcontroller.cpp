#include "bmsrequestcontroller.h"

BMSRequestController::BMSRequestController(QObject *parent, MemoryHandler *mH)
    : HttpRequestHandler(parent), mH(mH), pLController(this,mH)
{
}

void BMSRequestController::service(HttpRequest &request, HttpResponse &response){
    QByteArray path = request.getPath();

    if(path == "/" || path == "/playerlist") {
        pLController.service(request,response);
    } else {
        response.setStatus(404,"Not found");
        response.write("The supplied URL could not be found.");
    }
}
