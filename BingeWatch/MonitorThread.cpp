#include "MonitorThread.h"
#include <cpr/cpr.h>

void MonitorThread::run()
{
    while (true)
    {
        if (!m_vecCfg.isEmpty())
        {
            for (Config& cfg : m_vecCfg)
            {
                //�������󣬻�ȡ�����б�
                Content content;
                GetWorks(cfg.szMonitorUrl, content);
                cfg.content.append(content);
            }
        }
        QThread::sleep(m_nInterval);//�ȴ�ʱ��
    }
}

//��ȡ�û���Ϣ
void MonitorThread::GetAuthorInfo(const QString& monitorUrl, Config& cfg)
{
}

//��ȡ�û���Ʒ��
void MonitorThread::GetWorks(const QString& monitorUrl, Content& content)
{
}

void MonitorThread::SetAutoDL(const bool bIsAutoDL)
{
    m_bIsAutoDL = bIsAutoDL;
}

void MonitorThread::SetInterval(int nInterval)
{
    m_nInterval = nInterval;
}

QVector<Config>& MonitorThread::GetVecCfg()
{
    return m_vecCfg;
}

void MonitorThread::SetVecCfg(const QString& monitorUrl)
{
    // ͨ��URL��ȡ������Ϣ
    Config cfg;
    GetAuthorInfo(monitorUrl, cfg);
    cfg.szMonitorUrl = monitorUrl;

    m_vecCfg.append(cfg);
}
