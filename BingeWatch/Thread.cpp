#include <QDateTime>
#include "Thread.h"


void Thread::run()
{
    qint64 curTs = QDateTime::currentSecsSinceEpoch();//获取时间戳（秒）
    while (m_bIsRun)
    {
        if (!m_vecCfg.isEmpty() &&
            QDateTime::currentSecsSinceEpoch() - curTs < m_nInterval)//间隔时间
        {
            for (Config& cfg : m_vecCfg)
            {
                //网络请求，获取更新列表
                Content content;
                GetWorks(cfg.szID, content);
                cfg.content.append(content);
            }
            curTs = QDateTime::currentSecsSinceEpoch();//获取时间戳（秒）
        }
        mutex.lock();//上锁
        if (!m_queUrl.isEmpty())
        {
            Task task = m_queUrl.dequeue();
            mutex.unlock();//开锁

            Config cfg = SetUrl(ExtractUID(&session, task.url));
            //加入表格显示
            int nIdx = task.m_tb->rowCount();
            task.m_tb->insertRow(nIdx);
            task.m_tb->setItem(nIdx, 0, new QTableWidgetItem(cfg.szID));
            task.m_tb->setItem(nIdx, 1, new QTableWidgetItem(QString::number(cfg.nNumber)));
            task.m_tb->setItem(nIdx, 2, new QTableWidgetItem(cfg.szUserName));
        }
        else
        {
            mutex.unlock();//开锁
        }

        QThread::msleep(10);
    }
}

void Thread::SetRunning(const bool isRun)
{
    m_bIsRun = isRun;
}
void Thread::SetAutoDL(const bool bIsAutoDL)
{
    m_bIsAutoDL = bIsAutoDL;
}

void Thread::SetInterval(int nInterval)
{
    m_nInterval = nInterval;
}

void Thread::PushConfig(const Config& cfg)
{
    m_vecCfg.append(cfg);
}

QVector<Config>& Thread::GetVecCfg()
{
    return m_vecCfg;
}

Config Thread::SetUrl(const QString& szID)
{
    // 通过URL获取作者信息
    Config cfg;
    GetAuthorInfo(szID, cfg);
    m_vecCfg.append(cfg);
    return cfg;
}

void Thread::SetUrl(const QString& monitorUrl, QTableWidget* tb)
{
    mutex.tryLock();
    m_queUrl.enqueue({ monitorUrl,tb });
    mutex.unlock();
}

