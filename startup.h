#pragma once
#include <QObject>
#include "View/setuptab.h"
#include "View/mainview.h"

namespace Ps{

    class Startup final: public QObject
    {
        Q_OBJECT
    public:
        explicit Startup();
        ~Startup();
        void show() const;
    private:
        //SetupTab& m_setuptab;
        SetupTab* pm_setupTab;
        MainView* m_mainView;
    };
}


