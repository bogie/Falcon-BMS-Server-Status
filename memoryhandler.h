#ifndef MEMORYHANDLER_H
#define MEMORYHANDLER_H

#include <QObject>
#include <QDebug>
#include "FlightData.h"
#include <windows.h>
#include <tchar.h>
#include <conio.h>
#include <QStringList>
#include <QTimer>
#include <QProcess>
#include <QMap>

class MemoryHandler : public QObject
{
    Q_OBJECT
public:
    MemoryHandler();
    bool isSharedMemoryMapped;
    void initSharedMemory();
    int getPilotsOnline();
    QStringList getPilotNames();
    QMap<int,QString> getPilotList();
    int getPilotStatus(QString pilotName);
    int getPilotStatus(int pilotId);
    int getCurrentTime();
    bool isBMSRunning();
private:
    HANDLE dataFileHeader;
    HANDLE data2FileHeader;
    LPVOID dataHeader;
    LPVOID data2Header;
    FlightData* data;
    FlightData2* data2;
    QTimer mapTimer;

    int getPilotIdByName(QString pilotName);
public slots:
    void retryMemoryMapping();
};

#endif // MEMORYHANDLER_H
