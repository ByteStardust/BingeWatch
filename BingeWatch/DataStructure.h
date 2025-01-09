#pragma once
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

struct Content
{
    //QString szUser;//�û���
    QString szVideoNick;//��Ƶ����
    QString szDuration;//ʱ��
    QString szVideoUrl;//��Ƶ����
    // ���ṹ��ת��Ϊ QJsonObject
    QJsonObject toJson() const {
        QJsonObject obj;
        obj["��Ƶ����"] = szVideoNick;
        obj["ʱ��"] = szDuration;
        obj["��ƵURL"] = szVideoUrl;
        return obj;
    }

    // �� QJsonObject ת��Ϊ�ṹ��
    static Content fromJson(const QJsonObject& obj) {
        Content content;
        content.szVideoNick = obj.value("��Ƶ����").toString();
        content.szDuration = obj.value("ʱ��").toString();
        content.szVideoUrl = obj.value("��ƵURL").toString();
        return content;
    }
};
struct Config
{
    QString szUserName;//�û���
    int nNumber;//��Ʒ����
    QString szMonitorUrl;//���url���ϼ�/���ߣ�
    QVector<Content> content;
    // ���ṹ��ת��Ϊ QJsonObject
    QJsonObject toJson() const {
        QJsonObject obj;
        obj["�û�"] = szUserName;
        obj["����"] = nNumber;
        obj["���URL"] = szMonitorUrl;

        QJsonArray contentArray;
        for (const auto& item : content) {
            contentArray.append(item.toJson());  // ���� Content �� toJson ����
        }
        obj["����"] = contentArray;

        return obj;
    }

    // �� QJsonObject ת��Ϊ�ṹ��
    static Config fromJson(const QJsonObject& obj) {
        Config config;
        config.szUserName = obj.value("�û�").toString();
        config.nNumber = obj.value("����").toInt();
        config.szMonitorUrl = obj.value("���URL").toString();

        QJsonArray contentArray = obj.value("����").toArray();
        for (const auto& value : contentArray) {
            if (value.isObject()) {
                config.content.append(Content::fromJson(value.toObject()));  // ���� Content �� fromJson ����
            }
        }
        return config;
    }
};