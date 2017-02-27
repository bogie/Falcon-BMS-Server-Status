#include "memoryhandler.h"

#define BUF_SIZE 256
TCHAR szName[]=TEXT("FalconSharedMemoryArea2");

MemoryHandler::MemoryHandler()
{
    isSharedMemoryMapped = false;
    hMapFileHeader = NULL;
    data = NULL;
    connect(&mapTimer, SIGNAL(timeout()),this, SLOT(retryMemoryMapping()));
    mapTimer.start(3000);
}


void MemoryHandler::initSharedMemory()
{
    if(hMapFileHeader != NULL) {
        //FIXME: _Close_ the old mapping and make a new one
    }
    qDebug() << "Trying to open file mapping...";
    hMapFileHeader = OpenFileMapping(FILE_MAP_READ, FALSE, szName);

    if(hMapFileHeader == NULL) {
        qDebug() << "Did you set g_bExportRTTTextures 1 in Falcon BMS 4.33\\User\\Config\\Falcon BMS.cfg? Shared Memory area could not be found...";
        return;
    }

    header = MapViewOfFile(hMapFileHeader, FILE_MAP_READ, 0, 0, 0);

    if(header == NULL) {
        qDebug() << "Could not ge a MapViewOfFile, wtf...";
        return;
    }
    qDebug() << "Shared Memory has been initialized!";
    isSharedMemoryMapped = true;

    data = (FlightData2*)header;
}

int MemoryHandler::getPilotsOnline()
{
    return (int)data->pilotsOnline;
}

QStringList MemoryHandler::getPilotNames()
{
    QStringList list;
    for(int i=0;i<(int)data->pilotsOnline;i++){
        list.append(data->pilotsCallsign[i]);
    }
    return list;
}

QMap<int, QString> MemoryHandler::getPilotList()
{
    QMap<int, QString> pilotList;
    for(int i=0; i<(int)data->pilotsOnline;i++){
        pilotList.insert(i,data->pilotsCallsign[i]);
    }
    return pilotList;
}

int MemoryHandler::getPilotStatus(QString pilotName)
{
    int pilotId = getPilotIdByName(pilotName);
    if(pilotId<0){
        return 5;
    }
    return (int)data->pilotsStatus[pilotId];
}

int MemoryHandler::getPilotStatus(int pilotId)
{
    return (int)data->pilotsStatus[pilotId];
}

int MemoryHandler::getCurrentTime()
{
    return data->currentTime;
}

int MemoryHandler::getPilotIdByName(QString pilotName)
{
    for(int i=0;i<(int)data->pilotsOnline;i++){
        if(data->pilotsCallsign[i] == pilotName){
            return i;
        }
    }
    return -1;
}

bool MemoryHandler::isBMSRunning(){
    QProcess tasklist;
    tasklist.start("tasklist", QStringList() << "/NH" << "/FO" << "CSV" << "/FI" << QString("IMAGENAME eq Falcon BMS.exe"));
    tasklist.waitForFinished();
    QString output = tasklist.readAllStandardOutput();
    return output.startsWith(QString("\"Falcon BMS.exe"));
}

void MemoryHandler::retryMemoryMapping()
{
    if(!isSharedMemoryMapped){
        qDebug() << "SharedMemory is not mapped, attempting reMap";
        if(!isBMSRunning()){
            qDebug() << "retryMemoryMapping: Error, BMS is not running";
            return;
        }
        initSharedMemory();
    }
}
