#pragma once
#include <QObject>

class QString;
class QStringListModel;
class QJsonParseError;
class QJsonObject;
class QFile;
class QDir;

namespace Ps{
    typedef std::pair<QJsonObject, QJsonParseError> JsonObjErrPair;
    class Setting : public QObject
    {
        Q_OBJECT
    public:

        explicit Setting(QObject *parent, QString filename);

        void ParseJsonData();
    signals:
        void NotifyStatusMessage(QString message);
    private:
        QString m_filename;
        QString m_applicationName;
        QString m_appShortName;
        QString m_hostName;
        QString m_portNumber;
        int m_waitMs;
        int m_readWaitMs;
        QStringListModel& m_modelCommands;



        QString ReadJsonFile();
        QString ReadJsonFromInternalResource();

        explicit Setting(const Setting& rhs) = delete;
        Setting& operator= (const Setting& rhs) = delete;

        void SendErrorMessage(const QString& msg);

        JsonObjErrPair GetJsonObject(const QString &str);
        void SetupCommands(QJsonObject json_obj);
    };
}


