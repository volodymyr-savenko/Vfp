#include "setting.h"
#include <QDebug>
#include <QString>
#include <QDir>
#include <QFile>
#include <QString>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <utility>
#include <QJsonArray>
#include <QStringListModel>

namespace Ps
{

    static auto RESOURSE_PREFIX = QStringLiteral(":/json");
    Setting::Setting(QObject *parent, QString filename) :
        QObject(parent),
        m_filename(filename),
        m_modelCommands(*new QStringListModel())
    {
        ReadJsonFile();
    }


    void Setting::ParseJsonData(){
        QString raw_json = ReadJsonFile();
        if (raw_json.isEmpty())
            return;
        auto json_result = GetJsonObject(raw_json);
        auto json_err = json_result.second;
        if (json_err.error != QJsonParseError::NoError){
            //ShowJsonParseError();
        }
        auto json_obj = json_result.first;
        m_applicationName = json_obj["applicationName"].toString();
        m_appShortName = json_obj["appShortName"].toString();
        m_hostName = json_obj["hostName"].toString();
        m_waitMs = json_obj["tcpLongWaitMs"].toInt();
        m_portNumber = json_obj["port"].toInt();
        m_readWaitMs = json_obj["tcpShortWaitMs"].toInt();
        qDebug() << m_applicationName;
        qDebug() << m_appShortName;
        qDebug() << m_hostName;
        qDebug() << m_waitMs;
        qDebug() <<  m_portNumber;
        qDebug() << m_readWaitMs;
        SetupCommands(json_obj);
//        for (auto item: m_modelCommands){
//            qDebug() << item.toString();
//        }

    }

    JsonObjErrPair Setting::GetJsonObject(const QString& str){
        QJsonParseError json_parse_err;
        QJsonDocument json_doc = QJsonDocument::fromJson(str.toUtf8(), &json_parse_err);
        QJsonObject json_obj = json_doc.object();
        return std::make_pair(json_obj, json_parse_err);
    }
    void Setting::SetupCommands(QJsonObject json_obj){
        QJsonArray cmd_array = json_obj["commands"].toArray();
        QStringList cmd_list;
        for (auto item: cmd_array) {
            cmd_list.append(item.toString());
        }
        m_modelCommands.setStringList(cmd_list);
    }
    QString Setting::ReadJsonFile()
    {
        auto default_setting = ReadJsonFromInternalResource();
        return default_setting;
    }
    QString Setting::ReadJsonFromInternalResource()
    {
        QDir res_dir (RESOURSE_PREFIX);
        if (!res_dir.exists())
        {
            SendErrorMessage("Internal resource path missing " + res_dir.canonicalPath());
        }
        QString path = res_dir.filePath(m_filename);

        QFile res_file(path);
        if (!res_file.open(QFile::ReadOnly | QFile::Text))
        {
            SendErrorMessage("Could not open internal resource " + path);
        }
        QString settings = res_file.readAll();
        QStringList ls = settings.split(",",QString::SkipEmptyParts);
//        foreach(QString str, ls)
//        {
//            qDebug() << str ;
//        }
        return settings;
    }

    void Setting::SendErrorMessage(const QString &msg)
    {
        emit NotifyStatusMessage(msg);
    }

}
