#pragma once
#include <QString>
struct TodoItem {
    QString thing = "";
    bool done = false;
    QString createTime = "";
    int period = -1; // �������ڣ���λ�죬-1������
    int expire = -1; // ����ʱ�䣬��λ�죬-1�޵���
};