#pragma once
#include <QWidget>
#include <memory>


namespace Ps{

    class Settings;

    class Provider final
    {
    public:
        static Settings& GetSettingsAsSingleton();
        explicit Provider(const Provider& rhs) = delete;
        Provider& operator= (const Provider& rhs) = delete;

    private:
        static std::unique_ptr<Settings> m_instanceSettings;
    };
}


