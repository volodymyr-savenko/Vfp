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
    class Settings : public QObject
    {
        Q_OBJECT
    public:

        explicit Settings(QObject *parent, QString filename);
        void ParseJsonData();
        QString getApplicationName() const {return m_applicationName;}
        QString getAppShortName() const {return m_appShortName;}
        QString getHostName();
        quint16 getPortNumber();
        uint getLongWaitMs();
        uint getShortWaitMs();
        QStringListModel &getCommandsAsModel();
        QString getPwCommand() const {return m_pwCommand;}

    signals:
        void NotifyStatusMessage(QString message);

    private:
        QString m_filename;
        QString m_applicationName;
        QString m_appShortName;
        QString m_hostName;
        uint m_portNumber;
        uint m_waitMs;
        uint m_readWaitMs;
        QStringListModel& m_modelCommands;
        QString m_pwCommand;


        QString ReadJsonFile();
        QString ReadJsonFromInternalResource();

        explicit Settings(const Settings& rhs) = delete;
        Settings& operator= (const Settings& rhs) = delete;

        void SendErrorMessage(const QString& msg);

        JsonObjErrPair GetJsonObject(const QString &str);
        void SetupCommands(QJsonObject json_obj);
    };
}


