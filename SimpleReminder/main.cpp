#include "SimpleReminder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleReminder w;
    w.show();
    return a.exec();
}
