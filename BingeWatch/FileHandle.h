#pragma once
#include <QFile>
#include "MonitorThread.h"

class FileHandle
{
private:
    QFile* m_file;
    const QString m_fileName = "data.bin";
    QMap<QString, MonitorThread*>* m_mpThread;

public:

    FileHandle();
    ~FileHandle();
    void InitConfig()const;
    void SaveConfig()const;
    MonitorThread* GetThread(const QString& key);
};

