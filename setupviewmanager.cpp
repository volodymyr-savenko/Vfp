#include "setupviewmanager.h"
#include "utils.h"
#include "Model/instrument.h"
#include "View/setuptab.h"

namespace Ps
{
    SetupViewManager::SetupViewManager(QObject *parent, SetupTab& tab,
                                       Instructor& inst, Settings& settings):
        QObject(parent),
        m_setupTab(tab),
        m_instrument(inst)
    {

    }

}
