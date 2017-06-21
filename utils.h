#pragma once
#include <QWidget>

namespace Ps{
    class Utils
    {
    public:
        static void DestructorMsg(const QString& value);
        static void DestructorMsg(QObject* object);
    private:

    };
    }


