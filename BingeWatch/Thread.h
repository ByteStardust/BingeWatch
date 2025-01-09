#pragma once
#include <QThread>
#include <QTableWidget>
#include <cpr/cpr.h>
#include <QMutex>
#include <QQueue>
#include "DataStructure.h"

struct Task {
    QString url;
    QTableWidget* m_tb = nullptr;
};

class Thread :public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject* parent = nullptr) : QThread(parent) {
        session.SetHeader({
            {"user-agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36"},
            {"accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7"}
            });
        session.SetRedirect(cpr::Redirect(false));//关闭自动重定向
    }
private:
    QVector<Config>  m_vecCfg;
    bool m_bIsAutoDL = false;//自动下载
    int m_nInterval = 600;//单位（秒）
    QQueue<Task> m_queUrl;//url队列
    QMutex mutex;
    bool m_bIsRun = true;

protected:
    cpr::Session session;//创建一个http客户端

    void run() override;
    virtual QString ExtractUID(cpr::Session* session, QString& url) = 0;//提取UID
    virtual void GetAuthorInfo(QString szID, Config& cfg) = 0;//获取作者信息
    virtual void GetWorks(const QString& szID, Content& content) = 0;//获取作品集

public:
    void SetRunning(const bool isRun);
    void SetAutoDL(const bool bIsAutoDL);
    void SetInterval(int nInterval);
    void PushConfig(const Config& cfg);
    QVector<Config>& GetVecCfg();
    Config SetUrl(const QString& monitorUrl);
    void SetUrl(const QString& monitorUrl, QTableWidget* tb);

};

