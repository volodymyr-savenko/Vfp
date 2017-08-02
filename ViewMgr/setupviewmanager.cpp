#include "setupviewmanager.h"
#include "utils.h"
#include "Model/instrument.h"
#include "Model/settings.h"
#include "View/setuptab.h"

namespace Ps
{
    SetupViewManager::SetupViewManager(QObject *parent,
                                       SetupTab& tab,
                                       Instrument& inst,
                                       Settings& config):
        QObject(parent),
        m_setupTab(tab),
        m_instrument(inst)
    {
        WireSettings(config);
        config.ParseJsonData();
        WireHostAndPort();
        WireMessages();
        WireButtons();
        WireDisplayUpdate();

        m_setupTab.SetHostName(config.getHostName());
        m_setupTab.SetPort(config.getPortNumber());
        m_setupTab.SetCommands(config.getCommandsAsModel());
        auto long_wait = config.getLongWaitMs();
        auto short_wait = config.getShortWaitMs();
        m_instrument.SetLongWaitMs(long_wait);
        m_instrument.SetShortWaitMs(short_wait);
        emit NotifyStatusUpdate(tr("Long Wait Ms: %1").arg(long_wait));
        emit NotifyStatusUpdate(tr("Short Wait Ms: %1").arg(short_wait));
    }

    SetupViewManager::~SetupViewManager()
    {
        Utils::DestructorMsg(this);
    }

    void SetupViewManager::WireSettings(Settings& config)
    {
        connect(&config, &Settings::NotifyStatusMessage,
                &m_setupTab, &SetupTab::onStatusUpdated);
    }

    void SetupViewManager::WireButtons()
    {
        connect(&m_setupTab, &SetupTab::NotifyConnectClicked,
                &m_instrument, &Instrument::Connect);
        connect(&m_instrument, &Instrument::NotifyConnected,
                &m_setupTab, &SetupTab::onConnected);

        connect(&m_instrument, &Instrument::NotifyConnected,
                this, &SetupViewManager::onConnected);
        connect(&m_instrument, &Instrument::NotifyDisconnected,
                this, &SetupViewManager::onDisconnected);


        connect(&m_setupTab, &SetupTab::NotifyDisconnectClicked,
                &m_instrument, &Instrument::Disconnect);
        connect(&m_instrument, &Instrument::NotifyDisconnected,
                &m_setupTab, &SetupTab::onDisconnected);

        connect(&m_setupTab, &SetupTab::NotifySendClicked,
                &m_instrument, &Instrument::onSendRequest);
        connect(&m_setupTab, &SetupTab::NotifyReceiveClicked,
                &m_instrument, &Instrument::onReceiveRequest);

        connect(&m_instrument, &Instrument::NotifyDataReceived,
                &m_setupTab, &SetupTab::onDataReceived);
        connect(&m_instrument, &Instrument::NotifyDataSent,
                &m_setupTab, &SetupTab::onDataSent);

    }

    void SetupViewManager::WireDisplayUpdate()
    {
        connect(this, &SetupViewManager::NotifyConnectEnabled,
                &m_setupTab, &SetupTab::onConnectEnabled);
        connect(this, &SetupViewManager::NotifyDisconnectEnabled,
                &m_setupTab, &SetupTab::onDisconnectEnabled);

        connect(this, &SetupViewManager::NotifyDirectCommandsEnabled,
                &m_setupTab, &SetupTab::onDirectCommandsEnabled);
        connect(this, &SetupViewManager::NotifyControlTabEnabled,
                &m_setupTab, &SetupTab::onControlTabEnabled);
    }

    void SetupViewManager::WireHostAndPort()
    {
        connect(&m_setupTab, &SetupTab::NotifyHostNameChanged,
                &m_instrument, &Instrument::onHostNameChanged);
        connect(&m_setupTab, &SetupTab::NotifyPortChanged,
                &m_instrument, &Instrument::onPortChanged);
    }

    void SetupViewManager::WireMessages(){
        connect(&m_instrument, &Instrument::NotifyErrorDetected,
                &m_setupTab, &SetupTab::onStatusUpdated);
        connect(&m_instrument, &Instrument::NotifyStatusUpdated,
                &m_setupTab, &SetupTab::onStatusUpdated);
        connect(this, &SetupViewManager::NotifyStatusUpdate,
                &m_setupTab, &SetupTab::onStatusUpdated);
    }

    void SetupViewManager::onConnected()
    {
        emit NotifyConnectEnabled(false);
        emit NotifyDisconnectEnabled(true);
        emit NotifyDirectCommandsEnabled(true);
        emit NotifyControlTabEnabled(true);
    }

    void SetupViewManager::onDisconnected()
    {
        emit NotifyConnectEnabled(true);
        emit NotifyDisconnectEnabled(false);
        emit NotifyDirectCommandsEnabled(false);
        emit NotifyControlTabEnabled(false);
    }

}
