#pragma once

#include <QTcpSocket>

class Utils {
public:
    static bool IPLive(QString ip, int port, int timeout = 1000) {
        QTcpSocket tcpClient;
        tcpClient.abort();
        tcpClient.connectToHost(ip, port);
        //100����û�����������жϲ�����
        return tcpClient.waitForConnected(timeout);
    }
};
