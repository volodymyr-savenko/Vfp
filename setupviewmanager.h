#pragma once
#include <QObject>

namespace Ps{
    class SetupTab;
    class Instrument;
    class Settings;

    class SetupViewManager : public QObject
    {
        Q_OBJECT
    public:
        explicit SetupViewManager(QObject *parent, SetupTab& tab,
                                  Instrument& inst, Settings& config);

        ~SetupViewManager();
    private:
        SetupTab& m_setupTab;
        Instrument& m_instrument;
        Settings& config;

        explicit SetupViewManager(const SetupViewManager& rhs) = delete;
        SetupViewManager& operator= (const SetupViewManager& rhs) = delete;
    };
}


