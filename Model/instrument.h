#pragma once
#include <QObject>

namespace Ps{
    class InstSocket;

    class Instrument : public QObject
    {
        Q_OBJECT
    public:
        explicit Instrument(QObject *parent, InstSocket& sock);
        virtual ~Instrument();

        void Connect();
        void Disconnect();
        bool IsConnected() const;
        QString GetHostName() const;
        quint16 GetPort() const;
        void SetLongWaitMs(uint value);
        void SetShortWaitMs(uint value);
    signals:
        void NotifyConnected();
        void NotifyDisconnected();
        void NotifyDataSent(const QString& dataSent);
        void NotifyDataReceived(const QString& readData);
        void NotifyErrorDetected(const QString&  errorMsg);
        void NotifyStatusUpdated(const QString&  statusMsg);

    public slots:
        void onHostNameChanged(const QString&  hostName);
        void onPortChanged(quint16);
        void onConnected();
        void onDisconnected();
        void onSendRequest(const QString&  dataToSend);
        void onReceiveRequest();
        void onPulseWidthChanged(double value);

    private:
        InstSocket& m_instSocket;
        QString m_lastCommandSend;

        void WireConnections();
        explicit Instrument(const Instrument& rhs) = delete;
        Instrument& operator= (const Instrument& rhs) = delete;
    };
}


