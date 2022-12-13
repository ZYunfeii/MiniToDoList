#include "SimpleReminder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
#ifdef _WIN32
    //! Windows netword DLL init
    WORD version = MAKEWORD(2, 2);
    WSADATA data;

    if (WSAStartup(version, &data) != 0) {
        std::cerr << "WSAStartup() failure" << std::endl;
        return -1;
    }
#endif /* _WIN32 */

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
