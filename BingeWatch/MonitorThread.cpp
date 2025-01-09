#include "MonitorThread.h"


MonitorThread::MonitorThread(const QString& monitorUrl)
{
    session = new cpr::Session;
    SetUrl(monitorUrl);
}

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
void MonitorThread::GetAuthorInfo(QString monitorUrl, Config& cfg)
{
    //https://api.bilibili.com/x/space/app/index?mid=167424883
    QString url = "https://www.bilibili.com/list/";
    if (monitorUrl.isEmpty())
    {
        return;
    }
    //判断url类型，短链接，直链
    if (monitorUrl.contains("b23.tv"))
    {
        //访问短链接，获取返回头中的 location
        session->SetUrl(monitorUrl.toStdString());
        cpr::Response resp = session->Get();
        monitorUrl = resp.header["location"].c_str();
    }
    //解析url中的uid
    QRegularExpression regex("bilibili\\.com/(\\d+)");  // 匹配 "bilibili.com/" 后的数字
    QRegularExpressionMatch match = regex.match(monitorUrl);
    if (match.hasMatch())
    {
        url += match.captured(1);
    }
    session->SetUrl(url.toStdString());
    cpr::Response resp = session->Get();
    //html中取json字符串
    regex = QRegularExpression("window.__INITIAL_STATE__=(.*?);");
    match = regex.match(resp.text.c_str());
    QString szJson = match.captured(1);
    QJsonDocument jsDoc = QJsonDocument::fromJson(szJson.toUtf8());
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

Config MonitorThread::SetUrl(const QString& monitorUrl)
{
    // 通过URL获取作者信息
    Config cfg;
    GetAuthorInfo(monitorUrl, cfg);
    cfg.szMonitorUrl = monitorUrl;

    m_vecCfg.append(cfg);
    return cfg;
}
