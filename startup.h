#pragma once
#include <QObject>

namespace Ps{

    class Instrument;
    class SetupTab;
    class ControlTab;
    class MainView;
    class SetupViewManager;
    class ControlTabViewManager;

    class Startup final: public QObject
    {
        Q_OBJECT
    public:
        explicit Startup();
        ~Startup();
        void show() const;
    private:
        SetupTab* m_setupTab;
        ControlTab* m_controlTab;
        MainView* m_mainView;
        Instrument* m_instrument;
        SetupViewManager* m_setupVM;
        ControlTabViewManager* m_controlTabVM;
    };
}


