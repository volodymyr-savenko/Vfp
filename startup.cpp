#include "startup.h"
#include "utils.h"
#include "View/setuptab.h"
#include "View/controltab.h"
#include "Model/settings.h"
#include "Model/provider.h"
#include "Model/instrument.h"
#include "Model/instsocket.h"
#include "View/mainview.h"
#include "ViewMgr/setupviewmanager.h"
#include "ViewMgr/controltabviewmanager.h"

namespace Ps
{
    Startup::Startup():
        QObject(nullptr),
        m_setupTab(new SetupTab(nullptr)),
        m_controlTab(new ControlTab(nullptr)),
        m_mainView(new MainView(nullptr, m_setupTab, m_controlTab)),
        m_instrument(new Instrument(this, *new InstSocket(this))),
        m_setupVM(new SetupViewManager(this,
                                       *m_setupTab,
                                       *m_instrument,
                                       Provider::GetSettingsAsSingleton())),
        m_controlTabVM(new ControlTabViewManager(this,
                                                 *m_controlTab,
                                                 *m_instrument))
    {
        m_instrument->Disconnect();
    }
    Startup::~Startup()
    {
        Utils::DestructorMsg(this);
        delete m_mainView;
        //delete m_setupTab;
    }
    void Startup::show() const
    {
        m_mainView->show();
    }

}
