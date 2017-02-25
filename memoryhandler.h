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

class MemoryHandler : public QObject
{
    Q_OBJECT
public:
    MemoryHandler();
    bool isSharedMemoryMapped;
    void initSharedMemory();
    int getPilotsOnline();
    QStringList getPilotNames();
    int getCurrentTime();
private:
    HANDLE hMapFileHeader;
    HANDLE hMapFileData;
    LPVOID header;
    FlightData2* data;
    QTimer mapTimer;
public slots:
    void retryMemoryMapping();
};

#endif // MEMORYHANDLER_H
