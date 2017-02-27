#include "memoryhandler.h"

#define BUF_SIZE 256
TCHAR dataName[]=TEXT("FalconSharedMemoryArea");
TCHAR data2Name[]=TEXT("FalconSharedMemoryArea2");

MemoryHandler::MemoryHandler()
{
    isSharedMemoryMapped = false;
    dataFileHeader = NULL;
    data2FileHeader = NULL;
    data = NULL;
    data2 = NULL;
    connect(&mapTimer, SIGNAL(timeout()),this, SLOT(retryMemoryMapping()));
    mapTimer.start(3000);
}


void MemoryHandler::initSharedMemory()
{
    if(data2FileHeader != NULL && dataFileHeader != NULL) {
        //FIXME: _Close_ the old mapping and make a new one
    }
    qDebug() << "Trying to open file mapping...";
    dataFileHeader = OpenFileMapping(FILE_MAP_READ, FALSE, dataName);
    data2FileHeader = OpenFileMapping(FILE_MAP_READ, FALSE, data2Name);

    if(data2FileHeader == NULL || dataFileHeader == NULL) {
        qDebug() << "Did you set g_bExportRTTTextures 1 in Falcon BMS 4.33\\User\\Config\\Falcon BMS.cfg? Shared Memory area could not be found...";
        return;
    }

    dataHeader = MapViewOfFile(dataFileHeader, FILE_MAP_READ, 0, 0, 0);
    data2Header = MapViewOfFile(data2FileHeader, FILE_MAP_READ, 0, 0, 0);

    if(dataHeader == NULL || data2Header == NULL) {
        qDebug() << "Could not ge a MapViewOfFile, wtf...";
        return;
    }
    qDebug() << "Shared Memory has been initialized!";
    isSharedMemoryMapped = true;

    data = (FlightData*)dataHeader;
    data2 = (FlightData2*)data2Header;
}

int MemoryHandler::getPilotsOnline()
{
    return (int)data2->pilotsOnline;
}

QStringList MemoryHandler::getPilotNames()
{
    QStringList list;
    for(int i=0;i<(int)data2->pilotsOnline;i++){
        list.append(data2->pilotsCallsign[i]);
    }
    return list;
}

QMap<int, QString> MemoryHandler::getPilotList()
{
    QMap<int, QString> pilotList;
    for(int i=0; i<(int)data2->pilotsOnline;i++){
        pilotList.insert(i,data2->pilotsCallsign[i]);
    }
    return pilotList;
}

int MemoryHandler::getPilotStatus(QString pilotName)
{
    int pilotId = getPilotIdByName(pilotName);
    if(pilotId<0){
        return -1;
    }
    return (int)data2->pilotsStatus[pilotId];
}

int MemoryHandler::getPilotStatus(int pilotId)
{
    return (int)data2->pilotsStatus[pilotId];
}

int MemoryHandler::getCurrentTime()
{
    return data2->currentTime;
}

int MemoryHandler::getPilotIdByName(QString pilotName)
{
    for(int i=0;i<(int)data2->pilotsOnline;i++){
        if(data2->pilotsCallsign[i] == pilotName){
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
