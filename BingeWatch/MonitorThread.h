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
    bool m_bIsAutoDL = false;//�Զ�����
    int m_nInterval = 600;//��λ���룩

protected:
    void run() override;
    void GetAuthorInfo(const QString& monitorUrl, Config& cfg);//��ȡ������Ϣ
    void GetWorks(const QString& monitorUrl, Content& content);//��ȡ��Ʒ��

public:
    void SetAutoDL(const bool bIsAutoDL);
    void SetInterval(int nInterval);
    QVector<Config>& GetVecCfg();
    void SetVecCfg(const QString& monitorUrl);
};

