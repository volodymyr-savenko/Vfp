#include "startup.h"
#include "utils.h"
#include "Model/setting.h"

namespace Ps
    {
    Startup::Startup():
        QObject(nullptr),
        pm_setupTab(new SetupTab(nullptr)),
        m_mainView(new MainView(nullptr, pm_setupTab))
    {
        Setting my_settings(this, "settings.json");
        my_settings.ParseJsonData();
    }
    Startup::~Startup()
    {
         Utils::DestructorMsg(this);
         delete m_mainView;
         delete pm_setupTab;
    }
    void Startup::show() const
    {
        m_mainView->show();
    }

}
