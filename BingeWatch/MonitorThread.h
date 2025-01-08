#pragma once
#include <QThread>
#include "DataStructure.h"

class MonitorThread :public QThread
{
    Q_OBJECT
public:
    explicit MonitorThread(QObject* parent = nullptr) : QThread(parent) {}
private:
    QVector<Config>  m_vecCfg;
    bool m_bIsAutoDL = false;//自动下载
    int m_nInterval = 600;//单位（秒）

protected:
    void run() override;
    void GetAuthorInfo(const QString& monitorUrl, Config& cfg);//获取作者信息
    void GetWorks(const QString& monitorUrl, Content& content);//获取作品集

public:
    void SetAutoDL(const bool bIsAutoDL);
    void SetInterval(int nInterval);
    QVector<Config>& GetVecCfg();
    void SetVecCfg(const QString& monitorUrl);
};

