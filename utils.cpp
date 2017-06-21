#include "utils.h"
#include <QString>
#include <QDebug>
#include <QObject>

namespace Ps
{
    static QString DESTRUCTOR_MESSAGE = QString("Call from %1");
    void Utils::DestructorMsg(const QString& value)
    {
        qDebug() << DESTRUCTOR_MESSAGE.arg(value);

    }
    void Utils::DestructorMsg(QObject* obj)
    {
        DestructorMsg(obj->metaObject()->className());
    }

}
