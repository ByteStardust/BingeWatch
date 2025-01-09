#pragma once
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

struct Content
{
    //QString szUser;//用户名
    QString szVideoNick;//视频名称
    QString szDuration;//时长
    QString szVideoUrl;//视频链接
    // 将结构体转换为 QJsonObject
    QJsonObject toJson() const {
        QJsonObject obj;
        obj["视频名称"] = szVideoNick;
        obj["时长"] = szDuration;
        obj["视频URL"] = szVideoUrl;
        return obj;
    }

    // 从 QJsonObject 转换为结构体
    static Content fromJson(const QJsonObject& obj) {
        Content content;
        content.szVideoNick = obj.value("视频名称").toString();
        content.szDuration = obj.value("时长").toString();
        content.szVideoUrl = obj.value("视频URL").toString();
        return content;
    }
};
struct Config
{
    QString szUserName;//用户名
    int nNumber;//作品数量
    QString szMonitorUrl;//监控url（合集/作者）
    QVector<Content> content;
    // 将结构体转换为 QJsonObject
    QJsonObject toJson() const {
        QJsonObject obj;
        obj["用户"] = szUserName;
        obj["数量"] = nNumber;
        obj["监控URL"] = szMonitorUrl;

        QJsonArray contentArray;
        for (const auto& item : content) {
            contentArray.append(item.toJson());  // 调用 Content 的 toJson 方法
        }
        obj["内容"] = contentArray;

        return obj;
    }

    // 从 QJsonObject 转换为结构体
    static Config fromJson(const QJsonObject& obj) {
        Config config;
        config.szUserName = obj.value("用户").toString();
        config.nNumber = obj.value("数量").toInt();
        config.szMonitorUrl = obj.value("监控URL").toString();

        QJsonArray contentArray = obj.value("内容").toArray();
        for (const auto& value : contentArray) {
            if (value.isObject()) {
                config.content.append(Content::fromJson(value.toObject()));  // 调用 Content 的 fromJson 方法
            }
        }
        return config;
    }
};