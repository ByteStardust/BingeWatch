#pragma once
#include <QThread>
#include <cpr/cpr.h>
#include "DataStructure.h"

class MonitorThread :public QThread
{
    Q_OBJECT
public:
    explicit MonitorThread(QObject* parent = nullptr) : QThread(parent) {
        session = new cpr::Session;
    }
    explicit MonitorThread(const QString& monitorUrl);
private:
    QVector<Config>  m_vecCfg;
    bool m_bIsAutoDL = false;//自动下载
    int m_nInterval = 600;//单位（秒）
    cpr::Session* session;

protected:
    void run() override;

public:

    void SetAutoDL(const bool bIsAutoDL);
    void SetInterval(int nInterval);
    QVector<Config>& GetVecCfg();
    Config SetUrl(const QString& monitorUrl);
    void GetAuthorInfo(QString monitorUrl, Config& cfg);//获取作者信息
    void GetWorks(const QString& monitorUrl, Content& content);//获取作品集
};

