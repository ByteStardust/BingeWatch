#pragma once
#include <QFile>
#include "Thread.h"

class FileHandle
{
private:
    QFile* m_file;
    const QString m_fileName = "data.bin";
    QMap<QString, MonitorThread*>* m_mpThread;
    
public:
    QMap<QString, Thread*>* m_mpThread;

    FileHandle();
    ~FileHandle();
    void InitConfig()const;
    void SaveConfig()const;
    Thread* GetThread(const QString& key);
};

