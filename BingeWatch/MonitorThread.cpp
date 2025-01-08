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
                //网络请求，获取更新列表
                Content content;
                GetWorks(cfg.szMonitorUrl, content);
                cfg.content.append(content);
            }
        }
        QThread::sleep(m_nInterval);//等待时间
    }
}

//获取用户信息
void MonitorThread::GetAuthorInfo(const QString& monitorUrl, Config& cfg)
{
}

//获取用户作品集
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
    // 通过URL获取作者信息
    Config cfg;
    GetAuthorInfo(monitorUrl, cfg);
    cfg.szMonitorUrl = monitorUrl;

    m_vecCfg.append(cfg);
}
