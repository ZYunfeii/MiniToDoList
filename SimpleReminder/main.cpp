#include "SimpleReminder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSharedMemory shared("onlyOne");
    if (shared.attach()) {
        return 0;
    }
    shared.create(1);
    SimpleReminder w;
    w.show();
    return a.exec();
}
