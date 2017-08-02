#include "instrument.h"
#include "Model/instsocket.h"
#include "utils.h"
#include <QDebug>
#include "Model/settings.h"
#include "Model/provider.h"

namespace Ps
{
    Instrument::Instrument(QObject *parent, InstSocket& sock) :
        QObject(parent),
        m_instSocket(sock),
        m_lastCommandSend("")
    {
        WireConnections();
    }

    Instrument::~Instrument()
    {
        Utils::DestructorMsg(this);
    }

    void Instrument::WireConnections()
    {
        connect(&m_instSocket, &InstSocket::NotifyConnected,
                this, &Instrument::onConnected);
        connect(&m_instSocket, &InstSocket::NotifyDisconnected,
                this, &Instrument::onDisconnected);
    }

    void Instrument::SetShortWaitMs(uint value)
    {
        m_instSocket.SetShortWaitMs(value);
    }

    void Instrument::SetLongWaitMs(uint value)
    {
        m_instSocket.SetLongWaitMs(value);
    }

    void Instrument::onHostNameChanged(const QString& hostName)
    {
        m_instSocket.SetHostName(hostName);
    }

    void Instrument::onPortChanged(quint16 port)
    {
        m_instSocket.SetPort(port);
    }

    void Instrument::Connect()
    {
        Disconnect();
        bool connected = m_instSocket.Connect();
        if (!connected)
            emit NotifyErrorDetected(tr("ERROR: Did not connect to the host"));
    }

    void Instrument::onConnected()
    {
        emit NotifyConnected();
    }

    void Instrument::Disconnect()
    {
        if (m_instSocket.IsOpen())
            m_instSocket.Disconnect();
        else
            emit NotifyDisconnected();
    }

    bool Instrument::IsConnected() const
    {
        return m_instSocket.IsOpen();
    }

    void Instrument::onDisconnected()
    {
        emit NotifyDisconnected();
    }

    QString Instrument::GetHostName() const
    {
        return m_instSocket.GetHostName();
    }

    quint16 Instrument::GetPort() const
    {
        return m_instSocket.GetPort();
    }

    void Instrument::onSendRequest(const QString& dataToSend)
    {
        m_lastCommandSend = dataToSend;
        qDebug() << "Instrument ready to send data: " << dataToSend;
        m_instSocket.WriteData(dataToSend);
        emit NotifyDataSent(dataToSend);
    }

    void Instrument::onReceiveRequest()
    {
        QString input_buffer = m_instSocket.ReadData();
        if (input_buffer.size() == 0)
            emit NotifyDataReceived("No data received.");
        else
            emit NotifyDataReceived(input_buffer);
    }

    void Instrument::onPulseWidthChanged(double value)
    {
        Settings& settings = Provider::GetSettingsAsSingleton();
        auto pw_cmd = settings.getPwCommand() + "%1;";
        auto full_cmd = pw_cmd.arg(value);
        m_instSocket.WriteData(full_cmd);
        emit NotifyStatusUpdated(full_cmd);
    }
}
