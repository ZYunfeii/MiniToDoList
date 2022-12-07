#pragma once
#include <QString>
struct TodoItem {
    QString thing = "";
    bool done = false;
    QString createTime = "";
    int period = -1; // 任务周期，单位天，-1无周期
    int expire = -1; // 到期时间，单位天，-1无到期
};