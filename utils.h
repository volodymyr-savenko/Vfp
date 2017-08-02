#pragma once
#include <QWidget>
#include <memory>

namespace Ps{
    class Utils
    {
    public:
        static void DestructorMsg(const QString& value);
        static void DestructorMsg(QObject* object);

        template<typename T, typename... Args>
        static std::unique_ptr<T> make_unique(Args&&... args){
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }

    private:
        Utils(const Utils& rhs) = delete;
        Utils& operator= (const Utils& rhs) = delete;
    };
}


