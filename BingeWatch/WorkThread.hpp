#pragma once
#include "Thread.h"

//B站 工作线程
class BZhanThread :
    public Thread
{
protected:
    //提取UID
    virtual QString ExtractUID(cpr::Session* session, QString& url)
    {
        //判断url类型，短链接，直链
        if (url.contains("b23.tv"))
        {
            //访问短链接，获取返回头中的 location
            session->SetUrl(url.toStdString());
            cpr::Response resp = session->Get();

            url = resp.header["location"].c_str();
            //task.url = resp.url.c_str();
        }
        //提取url中的uid
        QRegularExpression regex("bilibili\\.com/(\\d+)");  // 匹配 "bilibili.com/" 后的数字
        QRegularExpressionMatch match = regex.match(url);
        if (match.hasMatch())
        {
            return match.captured(1);
        }
        return QString();
    }
    //获取作者信息
    virtual void GetAuthorInfo(QString szID, Config& cfg)
    {
        //https://api.bilibili.com/x/space/app/index?mid=167424883
        QString url = "https://www.bilibili.com/list/";
        if (szID.isEmpty())
        {
            return;
        }
        url += szID;
        session.SetUrl(url.toStdString());
        cpr::Response resp = session.Get();

        //html中取json字符串
        QRegularExpression regex("__INITIAL_STATE__=(.*?);");
        QRegularExpressionMatch match = regex.match(resp.text.c_str());
        //QString szJson = match.captured(1);

        QJsonObject jsObj = QJsonDocument::fromJson(match.captured(1).toUtf8()).object();
        cfg.szUserName = jsObj["upInfo"].toObject()["name"].toString();
        cfg.nNumber = jsObj["upInfo"].toObject()["archiveCount"].toInt();
        cfg.szID = szID;
    }
    //获取作品集
    virtual void GetWorks(const QString& szID, Content& content)
    {

    }
};

//抖音 工作线程
class DYinThread :public Thread
{
protected:
    //提取UID
    virtual QString ExtractUID(cpr::Session* session, QString& url)
    {
        //判断url类型，短链接，直链
        return QString();
    }
    //获取作者信息
    virtual void GetAuthorInfo(QString szID, Config& cfg)
    {
    }
    //获取作品集
    virtual void GetWorks(const QString& szID, Content& content)
    {

    }
};

//快手 工作线程
class KShouThread :public Thread
{
protected:
    //提取UID
    virtual QString ExtractUID(cpr::Session* session, QString& url)
    {
        //判断url类型，短链接，直链
        return QString();
    }
    //获取作者信息
    virtual void GetAuthorInfo(QString szID, Config& cfg)
    {
    }
    //获取作品集
    virtual void GetWorks(const QString& szID, Content& content)
    {

    }
};