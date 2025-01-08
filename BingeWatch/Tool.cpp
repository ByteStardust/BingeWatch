#include "Tool.h"
#include <QMessageBox>
#include <cstdlib>


Tool::Tool()
{
    m_file = new QFile(m_fileName);
    //判断文件是否存在，否则创建
    if (!QFile::exists(m_fileName))
    {
        m_file->open(QIODevice::WriteOnly | QIODevice::Text);
        m_file->close();
    }

    //打开文件
    if (!m_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "错误", "数据文件无法打开\n请检查后重启程序");
        std::exit(500);//退出程序
    }
    InitConfig();
}

Tool::~Tool()
{
    //判断文件是否打开
    if (m_file->isOpen())
    {
        //保存文件
        SaveConfig();

        //关闭文件
        m_file->close();
    }
}

void Tool::InitConfig() const
{
    //读取数据
    m_file->seek(0);
    QByteArray data = m_file->readAll();

    //解析json
    m_jsDoc->fromJson(data);

}

void Tool::SaveConfig() const
{
    m_file->seek(0);
    m_file->write(m_jsDoc->toJson(QJsonDocument::Indented));
}

QJsonArray* Tool::GetAryCfg(const QString& key) const
{
    return &m_jsDoc->object()[key].toArray();
}

Config Tool::GetConfig(const QString& key, const QString& monitorUrl) const
{
    QJsonArray* aryJson = GetAryCfg(key);
    return GetConfig(aryJson, monitorUrl);
}

Config Tool::GetConfig(QJsonArray* aryJson, const QString& monitorUrl) const
{
    for (int i = 0; i < aryJson->size(); i++)
    {
        QJsonObject json = aryJson->at(i).toObject();
        if (json["监控URL"] == monitorUrl)
        {
            return Config::fromJson(json);
        }
    }
    return {};
}

void Tool::SetConfig(const Config* cfg) const
{
}
