#include "controltabviewmanager.h"
#include "Model/instrument.h"
#include "View/controltab.h"
#include "utils.h"

namespace Ps
{
    ControlTabViewManager::ControlTabViewManager(QObject *parent,
                                                 ControlTab& ctrTab,
                                                 Instrument& inst) :
        QObject(parent),
        m_controlTab(ctrTab),
        m_instrument(inst)
    {
        WireControls();
        WireConnected();
    }

    ControlTabViewManager::~ControlTabViewManager()
    {
        Utils::DestructorMsg(this);
    }

    void ControlTabViewManager::WireControls()
    {
        connect(&m_controlTab, &ControlTab::NotifyPulseWidthChanged,
                &m_instrument, &Instrument::onPulseWidthChanged);

    }

    void ControlTabViewManager::WireConnected()
    {
        connect(&m_instrument, &Instrument::NotifyConnected,
                this, &ControlTabViewManager::onConnected);
        connect(&m_instrument, &Instrument::NotifyDisconnected,
                this, &ControlTabViewManager::onDisconnected);
    }

    void ControlTabViewManager::onConnected()
    {
        m_controlTab.EnablePanel(true);
    }
    void ControlTabViewManager::onDisconnected()
    {
        m_controlTab.EnablePanel(false);
    }
}
