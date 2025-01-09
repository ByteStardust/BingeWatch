#include "FileHandle.h"
#include <QMessageBox>
#include <cstdlib>
#include "WorkThread.hpp"

FileHandle::FileHandle()
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
    m_mpThread = new QMap<QString, Thread*>;
    InitConfig();
}

FileHandle::~FileHandle()
{
    //关闭所有线程
    for (auto thread : m_mpThread->values())
    {
        //thread->m_bIsRun = false;
        thread->SetRunning(false);
        thread->terminate();//强行终止
    }

    //判断文件是否打开
    if (m_file->isOpen())
    {
        //保存文件
        SaveConfig();

        //关闭文件
        m_file->close();
    }
}

void FileHandle::InitConfig() const
{
    //读取数据
    m_file->seek(0);
    QByteArray data = m_file->readAll();

    //解析json
    QJsonDocument jsDoc = QJsonDocument::fromJson(data);
    if (jsDoc.isEmpty())
    {
        QJsonObject jsObj;
        QJsonArray jsAry;

        //jsAry.append(Config().toJson());
        jsObj.insert("B站", jsAry);
        jsObj.insert("抖音", jsAry);
        jsObj.insert("快手", jsAry);
        jsDoc.setObject(jsObj);
    }
    QJsonObject jsObj = jsDoc.object();

    for (auto key : jsObj.keys())
    {
        Thread* thread = nullptr;
        if (key == "B站")
        {
            thread = new BZhanThread;
        }else if (key == "抖音")
        {
            thread = new DYinThread;
        }
        else if (key == "快手")
        {
            thread = new KShouThread;
        }
        else
        {
            continue;
        }
        //初始化线程
        if (!jsObj.value(key).isNull())
        {
            for (auto val : jsObj.value(key).toArray())
            {
                thread->PushConfig(Config::fromJson(val.toObject()));
            }
        }
        //启动线程
        m_mpThread->insert(key, thread);
        thread->start();
        //m_mpThread->value(key)->start();
    }
}

void FileHandle::SaveConfig() const
{
    QJsonObject jsObj;

    //从线程中拉取
    for (auto key : m_mpThread->keys())
    {
        QJsonArray jsAry;
        auto ts = m_mpThread->value(key);
        auto cfgs = ts->GetVecCfg();
        //遍历平台
        for (auto cfg : cfgs)
        {
            QJsonObject jsCfg;
            QJsonArray jsAryContent;
            jsCfg.insert("用户", cfg.szUserName);
            jsCfg.insert("数量", cfg.nNumber);
            jsCfg.insert("ID", cfg.szID);
            //遍历用户作品内容
            for (auto content : cfg.content)
            {
                QJsonObject jsContent;
                jsContent.insert("视频名称", content.szVideoNick);
                jsContent.insert("时长", content.szDuration);
                jsContent.insert("URL", content.szVideoUrl);
                jsAryContent.append(jsContent);
            }
            jsAry.append(jsCfg);
        }
        jsObj.insert(key, jsAry);
    }

    //写入文件
    m_file->seek(0);
    m_file->write(QJsonDocument(jsObj).toJson());
}

Thread* FileHandle::GetThread(const QString& key)
{
    return m_mpThread->value(key);
}
