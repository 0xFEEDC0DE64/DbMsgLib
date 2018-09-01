#include <QCoreApplication>
#include <QDebug>

#include "messages/mymessage.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    MyMessage original("Daniel", QDate(1996, 11, 12), QDateTime::currentDateTime(), 21, 80);
    MyMessage copy(original);

    original.setName("Peter");

    QVariantMap delta;
    original.copyTouchedTo(delta);
    original.setTouched(false);

    qDebug() << "before applying delta";
    copy.debug();

    copy.apply(delta);

    qDebug() << "after applying delta";
    copy.debug();

    return app.exec();
}
