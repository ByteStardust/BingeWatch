#pragma once
#include <QFile>
#include "DataStructure.h"


class Tool
{
private:
    //QMap<QString, QVector<Config>> m_mpCfg;
    QJsonDocument* m_jsDoc = new QJsonDocument;
    QFile* m_file;
    const QString m_fileName = "data.bin";

public:
    Tool();
    ~Tool();
    void InitConfig()const;
    void SaveConfig()const;
    QJsonArray* GetAryCfg(const QString& key)const;//key等于平台 名称（B站，抖音，快手）
    //Config& GetConfig(const QString& monitorUrl)const;//根据监控Url获取
    Config GetConfig(const QString& key, const QString& monitorUrl)const;//根据监控Url获取
    Config GetConfig(QJsonArray* aryJson, const QString& monitorUrl)const;//根据监控Url获取
    void SetConfig(const Config* cfg)const;

};

