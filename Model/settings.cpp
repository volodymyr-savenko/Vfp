#include "settings.h"
#include <QDebug>
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

    static const int PW_CMD_INDEX = 5;
    static auto RESOURSE_PREFIX = QStringLiteral(":/json");
    Settings::Settings(QObject *parent, QString filename) :
        QObject(parent),
        m_filename(filename),
        m_modelCommands(*new QStringListModel())
    {
        ReadJsonFile();
    }


    void Settings::ParseJsonData(){
        QString raw_json = ReadJsonFile();
        if (raw_json.isEmpty()) return;

        auto json_result = GetJsonObject(raw_json);
        auto json_err = json_result.second;
        if (json_err.error != QJsonParseError::NoError){
            //ShowJsonParseError();
        }
        auto json_obj = json_result.first;

        m_applicationName = json_obj["applicationName"].toString();
        m_appShortName = json_obj["appShortName"].toString();
        m_hostName = json_obj["hostName"].toString();
        m_portNumber = json_obj["port"].toInt();
        m_waitMs = json_obj["tcpLongWaitMs"].toInt();
        m_readWaitMs = json_obj["tcpShortWaitMs"].toInt();
        SetupCommands(json_obj);
    }

    QString Settings::getHostName()
    {
        return m_hostName;
    }

    quint16 Settings::getPortNumber()
    {
        return m_portNumber;
    }

    QStringListModel& Settings::getCommandsAsModel()
    {
        return m_modelCommands;
    }

    uint Settings::getLongWaitMs()
    {
        return m_waitMs;
    }

    uint Settings::getShortWaitMs()
    {
        return m_readWaitMs;
    }

    JsonObjErrPair Settings::GetJsonObject(const QString& str){
        QJsonParseError json_parse_err;
        QJsonDocument json_doc = QJsonDocument::fromJson(str.toUtf8(), &json_parse_err);
        QJsonObject json_obj = json_doc.object();
        return std::make_pair(json_obj, json_parse_err);
    }
    void Settings::SetupCommands(QJsonObject json_obj){
        QJsonArray cmd_array = json_obj["commands"].toArray();
        QStringList cmd_list;
        qDebug() << cmd_list;
        for (auto item: cmd_array) {
            cmd_list.append(item.toString());
        }
        m_modelCommands.setStringList(cmd_list);

        auto index = m_modelCommands.index(PW_CMD_INDEX);
        auto test_cmd = m_modelCommands.data(index, Qt::DisplayRole);
        qDebug() << "Test Command the hard way " << test_cmd.toString();

        if (PW_CMD_INDEX < cmd_list.size()){
            m_pwCommand = cmd_list.at(PW_CMD_INDEX);

        }
        else{
            emit NotifyStatusMessage("Unable to get pulse width command");
        }

    }
    QString Settings::ReadJsonFile()
    {
        auto default_settings = ReadJsonFromInternalResource();
        return default_settings;
    }
    QString Settings::ReadJsonFromInternalResource()
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
        return settings;
    }

    void Settings::SendErrorMessage(const QString &msg)
    {
        emit NotifyStatusMessage(msg);
    }

}
