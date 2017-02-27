#include <QCoreApplication>
#include <memoryhandler.h>
#include <QDebug>
#include <QSettings>
#include <QDir>

#include <httplistener.h>
#include <bmsrequestcontroller.h>

using namespace stefanfrings;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSettings* listenerSettings = new QSettings(QCoreApplication::applicationDirPath()+"/etc/http.ini", QSettings::IniFormat, &a);
    MemoryHandler *mH = new MemoryHandler();

    listenerSettings->beginGroup("listener");

    new HttpListener(listenerSettings,new BMSRequestController(&a,mH),&a);
    return a.exec();
}
