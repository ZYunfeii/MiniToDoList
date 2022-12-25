#pragma once

#include <QtWidgets/QMainWindow>
#include <qstandarditemmodel.h>
#include <qaction.h>
#include <qmenu.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QCloseEvent> 
#include <QScrollBar>
#include <QtWidgets/QDesktopWidget>
#include <QSharedMemory>
#include <QTimer>
#include <QDebug>
#include <qdatetime.h>
#include "qjsonarray.h"
#include "qjsonobject.h"
#include "qjsondocument.h"
#include <algorithm>
#include <thread>
#include <cpp_redis/cpp_redis>
#include <qmessagebox.h>
#include "ui_SimpleReminder.h"
#include "PeriodDialog.h"
#include "SearchEngine.h"
#include "meta.h"
#include "item.h"
#include "login.h"
#include "ShowInfo.h"

#ifdef _WIN32  
#include <Winsock2.h>  
#endif /* _WIN32 */  

#define TEST_BIT(a, b) a & b
#define HIDE_BORDER 30 //隐藏时显示border
#define CHECK_BORDER 10 //边界检测宽度
#define EXPIRE_TIMER_INTERVAL 5 // 刷新过期时间 单位：分钟
#define PERSISTENCE_INTERVAL 1 // 自动持久化 单位：分钟
#define ONLINE_NUM_UPDATE 2 / 60 // 在线人数刷新 2秒钟
#define NEW_DAY_DETEC_INTERVAL 0.1 // 新的一天检测间隔
#define WIDTH_RECORD_1 340
#define WIDTH_RECORD_2 200
#define SAVE_DISK 0  // 是否持久化到本地数据库 0否（默认redis存储）
#define REDIS_OR_DISK 1 // 从哪加载数据 1:redis 0：本地
#define DBNAME "record.db"
#define TOPIC_ONLINE_NUM "todolistOnlineNum"


class SimpleReminder : public QMainWindow {
    Q_OBJECT

public:
    SimpleReminder(QWidget *parent = nullptr);
    ~SimpleReminder();

private:
    enum FloatingFeature {
        NoArea = 0x0,
        TopArea = 0x1,
        BottomArea = 0x2,
        LeftArea = 0x4,
        RightArea = 0x8,
        RightAndTopArea = 0x81,
        AllArea = 0xf,
    };

    enum TableIndex {
        THING = 0,
        DONE,
        CREATE_TIME,
        PERIOD,
        EXPIRE
    };

    Ui::SimpleReminderClass* ui_;
    QMenu* rightMenu_;  //右键菜单
    QAction* addAction_;  
    QAction* deleteAction_; 
    QAction* hideAction_;
    QAction* showAllAction_;
    QAction* periodAction_;
    QAction* detailAction_;
    QAction* timeShowAction_;
    QAction* searchAction_;
    QStandardItemModel* model_;

    QPoint dragPosition_;
    QPoint recoverPosition_;
    FloatingFeature feature_;
    QTimer* timer_;
    QTimer* expireTimer_;
    QTimer* persistenceTimer_;
    QTimer* onlineNumTimer_;
    QTimer* newDayDetecTimer_;

    std::string redisTopic_;

    QModelIndex selectedIndex_;
    QSqlDatabase db_;
    QString tableName_;

    PeriodDialog* periodDialog_;
    SearchEngine* searchEngine_;

    QList<TodoItem> hideItemCache_;
    QList<TodoItem> temporaryCache_;
    QVector< QAction*> actionVec_;

    login* lg_;
    ShowInfo* si_;

    uint32_t onlineNum_;

    bool isVisable_;
    bool detailTag_;
    bool timeDetailTag_;
    bool modifyTag_; // 若持久化后无修改表结构为false，否则为true，用于判断closeEvent时是否再次持久化
    bool searchTag_;
    bool firstLogInTag_;

    QDateTime newDayModifiedTime_;

    bool dbInit();
    void actionInit();
    void tableInit();
    void timerInit();
    void pullFromRedis();
    void addItem(TodoItem&& item, int pos = -1);
    bool insertDB(TodoItem&& item);
    void updateThingsCount();
    void updateOrder(int row, bool done); 
    void moveWindow(const QPoint& start, const QPoint& end, unsigned int step = 5);
    void hideAllColumn();
    void showAllColumn();
    void hideTimeColumn();
    void showTimeColumn();
    void copyToTemCache();
    void pullFromTemCache();
    bool checkIfNecessaryForHide();
    void logInProc();
    void decrOnlineNum();
    void showYesterdayThing(QDateTime now);
    TodoItem getItemFromTableRow(int row);
    QByteArray makeJson(TodoItem& item);

public slots:
    void clickedRightMenu(const QPoint& pos);  //右键信号槽函数
    void addActionTriggered();
    void deleteActionTriggered();
    void hideActionTriggered();
    void showAllActionTriggered();
    void periodActionTriggered();
    void detailActionTriggered();
    void timeShowTriggered();
    void searchActionTriggered();
    void doubleClicked(const QModelIndex&);
    void showDockWidget();
    void hideDockWidget();
    void expireUpdate();
    void dataPersistence();
    void redisPersistence();
    void onlineNumGet();
    void newDay();

protected:
    void closeEvent(QCloseEvent* e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent* e) Q_DECL_OVERRIDE;
    void enterEvent(QEvent* e) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent* event)Q_DECL_OVERRIDE;
};
