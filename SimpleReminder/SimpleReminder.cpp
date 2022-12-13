#include "SimpleReminder.h"

SimpleReminder::SimpleReminder(QWidget *parent)
    : QMainWindow(parent),
    ui_(new Ui::SimpleReminderClass),
    model_(nullptr),
    tableName_("record"),
    detailTag_(false),
    timeDetailTag_(false),
    modifyTag_(false),
    searchTag_(false),
    isVisable_(true),
    timer_(nullptr),
    persistenceTimer_(nullptr),
    expireTimer_(nullptr),
    redisClient_(nullptr),
    redisIP_("43.143.229.22"),
    redisPort_(6379),
    redisTopic_("todolist"),
    feature_(RightArea),
    periodDialog_(new PeriodDialog),
    searchEngine_(new SearchEngine(hideItemCache_, temporaryCache_))
{
    ui_->setupUi(this);
    setWindowOpacity(0.9);
    setMouseTracking(true);
    setWindowIcon(QIcon(":/SimpleReminder/images/icon.ico"));
    //setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint); // 置顶
    // 初始化
    tableInit();
    redisInit();
    actionInit();
    timerInit();
    // 数据库相关初始化放最后
    if (!dbInit()) {
        QMessageBox::warning(this, u8"警告", u8"数据库打开失败。");
    }
    updateThingsCount();
    Meta::getInstance()->metaInit(); // 元数据初始化
    hideActionTriggered(); // 默认隐藏完成事务

    // debug
}

void SimpleReminder::addItem(TodoItem&& item,  int pos) {
    auto itemThing = new QStandardItem(item.thing);
    QString tmp = (item.done == true ? u8"√" : u8"×");
    auto itemDone = new QStandardItem(tmp);
    itemDone->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    auto createTime = new QStandardItem(item.createTime);
    createTime->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    auto p = new QStandardItem(QString::number(item.period));
    p->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    auto e = new QStandardItem(QString::number(item.expire));
    e->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QList<QStandardItem*> itemList = { itemThing, itemDone, createTime, p , e};
    if (pos == -1) { // 默认放最后一行
        model_->appendRow(itemList);
    }
    else {
        model_->insertRow(pos, itemList);
    }   
}

void SimpleReminder::clickedRightMenu(const QPoint& pos) {
    QModelIndex index = ui_->tableView->indexAt(pos);//获取鼠标点击位置项的索引
 
    if (index.isValid()) {
        selectedIndex_ = index;
        addAction_->setEnabled(true);
        deleteAction_->setEnabled(true);
        periodAction_->setEnabled(true);
    }
    else {
        addAction_->setEnabled(true);
        deleteAction_->setEnabled(false);
        periodAction_->setEnabled(false);
    }

    if (checkIfNecessaryForHide()) hideAction_->setEnabled(true);
    else hideAction_->setEnabled(false);

    searchAction_->setEnabled(true);
    
    if (model_->rowCount() != 0) {
        detailAction_->setEnabled(true);
        timeShowAction_->setEnabled(true);
        showAllAction_->setEnabled(true);
    }
    else {
        detailAction_->setEnabled(false);
        timeShowAction_->setEnabled(false);
        showAllAction_->setEnabled(false);
    }

    if (searchTag_) {
        for (QAction* qa : actionVec_) {
            if (qa == searchAction_ || qa == timeShowAction_ || qa == detailAction_) continue;
            qa->setEnabled(false);
        }
    }

    rightMenu_->exec(QCursor::pos());
}

bool SimpleReminder::checkIfNecessaryForHide() {
    if (model_->rowCount() == 0) return false;
    for (int i = 0; i < model_->rowCount(); ++i) {
        QString tmp = ui_->tableView->model()->index(i, DONE).data().toString();
        bool done = (tmp.toStdString() == std::string(u8"√") ? 1 : 0);
        if (done) return true;
    }
    return false;
}

void SimpleReminder::doubleClicked(const QModelIndex& index) {
    if (index.isValid() && index.column() == DONE) {
        QString origin = model_->data(index).toString();
        QString tmp = (origin.toStdString() == std::string(u8"√") ? u8"×" : u8"√");
        model_->setData(index, tmp);
        updateThingsCount();
        updateOrder(index.row(), tmp.toStdString() == std::string(u8"√"));
        modifyTag_ = true;
    } 
}

void SimpleReminder::addActionTriggered() {
    TodoItem item;
    item.createTime = QDateTime::currentDateTime().toString(timeFormat);
    addItem(std::move(item), 0);
    updateThingsCount();
    modifyTag_ = true;
}

void SimpleReminder::deleteActionTriggered() {
    model_->removeRow(selectedIndex_.row());
    updateThingsCount();
    modifyTag_ = true;
}

TodoItem SimpleReminder::getItemFromTableRow(int row) {
    QString thing = ui_->tableView->model()->index(row, THING).data().toString();
    QString tmp = ui_->tableView->model()->index(row, DONE).data().toString();
    bool done = (tmp.toStdString() == std::string(u8"√") ? 1 : 0);
    QString createTime = ui_->tableView->model()->index(row, CREATE_TIME).data().toString();
    int period = ui_->tableView->model()->index(row, PERIOD).data().toString().toInt();
    int expire = ui_->tableView->model()->index(row, EXPIRE).data().toString().toInt();
    return TodoItem{ thing, done, createTime, period, expire };
}

void SimpleReminder::hideActionTriggered() {
    bool backOrFrontTag = hideItemCache_.empty()? false : true; // back
    for (int i = 0; i < ui_->tableView->model()->rowCount(); ++i) {
        TodoItem it = getItemFromTableRow(i);
        if (it.done) {
            if (!backOrFrontTag) hideItemCache_.push_back(it);
            else hideItemCache_.push_front(it);
            model_->removeRow(i);
            i--;
        }
    }
    updateThingsCount();
}

void SimpleReminder::showAllActionTriggered() {
    for (auto& item : hideItemCache_) {
        addItem(std::move(item), -1);
    }
    hideItemCache_.clear();
    updateThingsCount();
}

void SimpleReminder::periodActionTriggered() {
    periodDialog_->show();
    periodDialog_->exec();
    int period = periodDialog_->getPeriod();
    model_->setItem(selectedIndex_.row(), PERIOD, new QStandardItem(QString::number(period)));
    model_->setItem(selectedIndex_.row(), EXPIRE, new QStandardItem(QString::number(period)));
    hideAllColumn();
    modifyTag_ = true;
}

void SimpleReminder::detailActionTriggered() {
    if (!detailTag_) {
        showAllColumn();
        ui_->tableView->setColumnWidth(THING, WIDTH_RECORD_2);
        detailTag_ = true;
    }
    else {
        hideAllColumn();
        ui_->tableView->setColumnWidth(THING, WIDTH_RECORD_1);
        detailTag_ = false;
    }  
}

void SimpleReminder::timeShowTriggered() {
    if (!timeDetailTag_) {
        showTimeColumn();
        ui_->tableView->setColumnWidth(THING, WIDTH_RECORD_2);
        timeDetailTag_ = true;
    }
    else {
        hideTimeColumn();
        ui_->tableView->setColumnWidth(THING, WIDTH_RECORD_1);
        timeDetailTag_ = false;
    }
}

void SimpleReminder::copyToTemCache() {
    for (int i = 0; i < ui_->tableView->model()->rowCount(); ++i) {
        auto it = getItemFromTableRow(i);
        temporaryCache_.push_back(it);
    }
}
void SimpleReminder::pullFromTemCache() {
    std::for_each(temporaryCache_.begin(), temporaryCache_.end(), [this](auto& it) {
        addItem(std::move(it));
    });
    temporaryCache_.clear();
}


void SimpleReminder::searchActionTriggered() {
    if (searchTag_ == false) {
        copyToTemCache();
        searchEngine_->setCache(hideItemCache_, temporaryCache_);
        searchEngine_->show();
        searchEngine_->exec();
        if (searchEngine_->clicked()) {
            QList<TodoItem>& searchRes = searchEngine_->getSearchRes();
            if (searchRes.empty()) {
                QMessageBox::warning(this, u8"提示", u8"没有对应事项！");
                temporaryCache_.clear();
                searchActionTriggered(); // 递归
            }
            else {
                searchTag_ = true;
                model_->removeRows(0, model_->rowCount());
                std::for_each(searchRes.begin(), searchRes.end(), [this](auto& it) {
                    addItem(std::move(it));
                });
                updateThingsCount();
            }
        }
        else {
            temporaryCache_.clear();
        }
    }
    else {
        searchTag_ = false;
        QVector<TodoItem> v;
        for (int i = 0; i < model_->rowCount(); ++i) {
            v.push_back(getItemFromTableRow(i));
        }
        bool succ = searchEngine_->updateItem(v);
        assert(succ);
        model_->removeRows(0, model_->rowCount());
        pullFromTemCache();
        updateThingsCount(); // 可能对搜索内容修改
    }
}

bool SimpleReminder::dbInit() {
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(QString(DBNAME));
    if (!db_.open()){
        return false;
    }
    QSqlQuery query(db_);
    query.exec(QString("create table %1 (record varchar, done int2, create_time varchar,period int, expire int)").arg(tableName_));
    if (!REDIS_OR_DISK) {
        query.exec(QString("select * from %1").arg(tableName_));
        while (query.next()) {
            QString record = query.value(THING).toString();
            bool done = query.value(DONE).toInt();
            QString createTime = query.value(CREATE_TIME).toString();
            int period = query.value(PERIOD).toInt();
            int expire = query.value(EXPIRE).toInt();
            addItem(TodoItem{ record, done, createTime, period, expire }, -1);
        }
    }
    return true;
}

void SimpleReminder::redisInit() {

    cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);
    redisClient_ = new cpp_redis::client;
    redisClient_->connect(redisIP_, redisPort_, [](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
        if (status == cpp_redis::client::connect_state::dropped) {
            qDebug() << "client disconnected";
        }
    });
    // auth,password
    redisClient_->auth("yunfei", [](cpp_redis::reply& reply) {
        qDebug() << "auth info: " << reply ;
    });

    if (!REDIS_OR_DISK) return;
    // 拉取redis记录
    redisClient_->lrange(redisTopic_, 0, -1, [this](cpp_redis::reply& reply) {
        if (reply.is_array()) {
            auto v = reply.as_array();
            for (int i = 0; i < v.size(); ++i) {
                TodoItem item;
                if (v[i].is_string()) {
                    std::string itemJson = v[i].as_string();
                    QJsonDocument doc = QJsonDocument::fromJson(QString::fromStdString(itemJson).toUtf8());
                    QJsonObject obj = doc.object();
                    QStringList keys = obj.keys();
                    for (int i = 0; i < keys.size(); i++) {
                        QString key = keys.at(i);
                        QJsonValue value = obj.value(key);
                        if (key == "thing") {
                            item.thing = value.toVariant().toString();
                        }
                        else if (key == "done") {
                            item.done = value.toVariant().toBool();
                        }
                        else if (key == "createTime") {
                            item.createTime = value.toVariant().toString();
                        }
                        else if (key == "period") {
                            item.period = value.toVariant().toInt();
                        }
                        else if (key == "expire") {
                            item.expire = value.toVariant().toInt();
                        }
                    }
                    addItem(std::move(item));
                }
            }
        }
    });
    redisClient_->sync_commit();
}

void SimpleReminder::timerInit() {
    expireTimer_ = new QTimer(this);
    connect(expireTimer_, SIGNAL(timeout()), this, SLOT(expireUpdate()));
    expireTimer_->start(1000 * 60 * EXPIRE_TIMER_INTERVAL);

    persistenceTimer_ = new QTimer(this);
    if (SAVE_DISK) connect(persistenceTimer_, SIGNAL(timeout()), this, SLOT(dataPersistence()));
    connect(persistenceTimer_, SIGNAL(timeout()), this, SLOT(redisPersistence()));
    persistenceTimer_->start(1000 * 60 * PERSISTENCE_INTERVAL);
}

void SimpleReminder::dataPersistence() {

    QSqlQuery query(db_);
    query.prepare(QString("delete from %1").arg(tableName_));
    if (!query.exec()) {
        QMessageBox::warning(this, u8"警告", u8"清理数据库失败。");
        return;
    }
    int row = ui_->tableView->model()->rowCount();
    // 先插入未完成的，再插入完成的
    QVector<TodoItem> doneCache;
    for (int i = 0; i < row; ++i) {
        TodoItem item = getItemFromTableRow(i);
        if (item.done) {
            doneCache.push_back(item);
            continue;
        }
        if (!insertDB(std::move(item))) {
            QMessageBox::warning(this, u8"警告", u8"数据库插入失败。");
        }
    }
    for (int i = 0; i < doneCache.size(); ++i) {
        if (!insertDB(std::move(doneCache[i]))) {
            QMessageBox::warning(this, u8"警告", u8"数据库插入失败。");
        }
    }
    // 将临时缓存中的完成事项插入数据库
    for (int i = 0; i < temporaryCache_.size(); ++i) {
        if (!insertDB(std::move(temporaryCache_[i]))) {
            QMessageBox::warning(this, u8"警告", u8"数据库插入失败。");
        }
    }
    // 将隐藏缓存中的完成事项插入数据库
    for (int i = 0; i < hideItemCache_.size(); ++i) {
        if (!insertDB(std::move(hideItemCache_[i]))) {
            QMessageBox::warning(this, u8"警告", u8"数据库插入失败。");
        }
    }
    modifyTag_ = false;

}

void SimpleReminder::redisPersistence() {
    // 清理话题
    redisClient_->del({ redisTopic_ });

    int row = ui_->tableView->model()->rowCount();
    // 先插入未完成的，再插入完成的
    QVector<TodoItem> doneCache;
    QVector<TodoItem> notDoneCache;
    std::vector<std::string> sendVec;
    for (int i = 0; i < row; ++i) {
        TodoItem item = getItemFromTableRow(i);
        if (item.done) {
            doneCache.push_back(item);
            continue;
        }
        notDoneCache.push_back(item);
    }
    for (int i = 0; i < notDoneCache.size(); ++i) {
        QByteArray qb = makeJson(notDoneCache[i]);
        sendVec.push_back(qb.toStdString());
    }
    for (int i = 0; i < doneCache.size(); ++i) {
        QByteArray qb = makeJson(doneCache[i]);
        sendVec.push_back(qb.toStdString());
    }
    // 将临时缓存中的完成事项插入数据库
    for (int i = 0; i < temporaryCache_.size(); ++i) {
        QByteArray qb = makeJson(temporaryCache_[i]);
        sendVec.push_back(qb.toStdString());
    }
    // 将隐藏缓存中的完成事项插入数据库
    for (int i = 0; i < hideItemCache_.size(); ++i) {
        QByteArray qb = makeJson(hideItemCache_[i]);
        sendVec.push_back(qb.toStdString());
    }
    redisClient_->rpush(redisTopic_, sendVec, [](cpp_redis::reply& reply) {
        std::cout << "rpush reply: " << reply << std::endl;
    });
    redisClient_->sync_commit();
    modifyTag_ = false;
}

QByteArray SimpleReminder::makeJson(TodoItem& item) {
    QJsonObject obj;
    obj.insert("thing", item.thing);
    obj.insert("done", item.done);
    obj.insert("createTime", item.createTime);
    obj.insert("period", item.period);
    obj.insert("expire", item.expire);
    QJsonDocument doc(obj);
    QByteArray json = doc.toJson();
    return json;
}

void SimpleReminder::expireUpdate() {
    int intervalDay = Meta::getInstance()->timeSinceLastUpdate();
    if (intervalDay < 1) return;
    Meta::getInstance()->metaInit(); // 元数据初始化
    int row = ui_->tableView->model()->rowCount();
    int period, expire, tmp;
    for (int i = 0; i < row; ++i) {
        QString doneStr = ui_->tableView->model()->index(i, 1).data().toString();
        bool done = (doneStr.toStdString() == std::string(u8"√") ? 1 : 0);
        period = ui_->tableView->model()->index(i, PERIOD).data().toString().toInt();
        if (period == -1) continue;
        expire = ui_->tableView->model()->index(i, EXPIRE).data().toString().toInt();
        tmp = expire - intervalDay;
        model_->setItem(i, 3, new QStandardItem(QString::number(period - intervalDay % period)));
        if (tmp <= 0 && done) { // 定期事务到期并且目前处于完成状态
            model_->setItem(i, 1, new QStandardItem(u8"×"));
            updateOrder(i, false);
        }
        hideAllColumn();
    }

    for (int i = 0; i < hideItemCache_.size(); ++i) {
        auto item = hideItemCache_[i];
        if (item.period == -1) continue;
        tmp = item.expire - intervalDay;
        item.expire = item.period - intervalDay % item.period;
        if (tmp <= 0 && item.done) {
            item.done = false;
            addItem(std::move(item), 0);
            hideItemCache_.removeAt(i);
            i--;
        }
    }
    updateThingsCount();
    Meta::getInstance()->setMetaTime(QDateTime::currentDateTime());
    modifyTag_ = true;
}

void SimpleReminder::hideAllColumn() {
    ui_->tableView->setColumnHidden(2, true); 
    ui_->tableView->setColumnHidden(3, true); 
    ui_->tableView->setColumnHidden(4, true); 
}

void SimpleReminder::showAllColumn() {
    ui_->tableView->setColumnHidden(2, false);
    ui_->tableView->setColumnHidden(3, false);
    ui_->tableView->setColumnHidden(4, false);
}

void SimpleReminder::hideTimeColumn() {
    ui_->tableView->setColumnHidden(2, true);
}

void SimpleReminder::showTimeColumn() {
    ui_->tableView->setColumnHidden(2, false);
}

void SimpleReminder::actionInit() {
    ui_->tableView->setContextMenuPolicy(Qt::CustomContextMenu);  //少这句，右键没有任何反应的。
    rightMenu_ = new QMenu(ui_->tableView);
    addAction_ = new QAction(u8"新增", ui_->tableView);
    deleteAction_ = new QAction(u8"删除", ui_->tableView);
    hideAction_ = new QAction(u8"隐藏", ui_->tableView);
    showAllAction_ = new QAction(u8"所有", ui_->tableView);
    periodAction_ = new QAction(u8"周期", ui_->tableView);
    detailAction_ = new QAction(u8"详（略）", ui_->tableView);
    timeShowAction_ = new QAction(u8"时间显示", ui_->tableView);
    searchAction_ = new QAction(u8"搜索与退出", ui_->tableView);
    rightMenu_->addAction(addAction_);
    rightMenu_->addAction(deleteAction_);
    rightMenu_->addAction(hideAction_);
    rightMenu_->addAction(showAllAction_);
    rightMenu_->addAction(periodAction_);
    rightMenu_->addAction(detailAction_);
    rightMenu_->addAction(timeShowAction_);
    rightMenu_->addAction(searchAction_);
    connect(addAction_, SIGNAL(triggered()), this, SLOT(addActionTriggered()));
    connect(deleteAction_, SIGNAL(triggered()), this, SLOT(deleteActionTriggered()));
    connect(hideAction_, SIGNAL(triggered()), this, SLOT(hideActionTriggered()));
    connect(showAllAction_, SIGNAL(triggered()), this, SLOT(showAllActionTriggered()));
    connect(periodAction_, SIGNAL(triggered()), this, SLOT(periodActionTriggered()));
    connect(detailAction_, SIGNAL(triggered()), this, SLOT(detailActionTriggered()));
    connect(timeShowAction_, SIGNAL(triggered()), this, SLOT(timeShowTriggered()));
    connect(searchAction_, SIGNAL(triggered()), this, SLOT(searchActionTriggered()));

    actionVec_ = { addAction_ , deleteAction_ , hideAction_ , showAllAction_ , 
                   periodAction_ , detailAction_,  timeShowAction_ , searchAction_ };
}

void SimpleReminder::tableInit() {
    ui_->tableView->setShowGrid(true);
    ui_->tableView->setGridStyle(Qt::DotLine);
    model_ = new QStandardItemModel();
    QStringList labels = { u8"事项", u8"完成" ,u8"创建", u8"周期", u8"到期"};
    model_->setHorizontalHeaderLabels(labels);
    ui_->tableView->setModel(model_);
    ui_->tableView->show();

    ui_->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 隐藏滚动条
    ui_->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui_->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); 
    ui_->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);

    ui_->tableView->setColumnWidth(THING, WIDTH_RECORD_1);

    hideAllColumn();

    connect(ui_->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(clickedRightMenu(QPoint)));
    connect(ui_->tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(doubleClicked(const QModelIndex&)));

}

bool SimpleReminder::insertDB(TodoItem&& item) {
    QSqlQuery query(db_);
    query.prepare(QString("INSERT INTO %1 (record, done, create_time, period, expire)"
                  "VALUES (:thing, :done, :create_time, :period, :expire)").arg(tableName_));
    query.bindValue(":thing", item.thing);
    query.bindValue(":done", qint8(item.done));
    query.bindValue(":create_time", item.createTime);
    query.bindValue(":period", item.period);
    query.bindValue(":expire", item.expire);
    bool flag = query.exec();
    return flag; 
}

void SimpleReminder::updateThingsCount() {
    int row = ui_->tableView->model()->rowCount();
    int total = 0, incompleted = 0;
    for (int i = 0; i < row; ++i) {
        QString thing = ui_->tableView->model()->index(i, 0).data().toString();
        QString tmp = ui_->tableView->model()->index(i, 1).data().toString();
        bool done = (tmp.toStdString() == std::string(u8"√") ? 1 : 0);
        if (!done) incompleted++;
        total++;
    }
    if (!searchTag_) {
        for (auto& item : hideItemCache_) {
            if (!item.done) incompleted++;
            total++;
        }
    }
    ui_->total->setText(QString::number(total));
    ui_->incompleted->setText(QString::number(incompleted));
    ui_->hide->setText(searchTag_ ?  "0" : QString::number(hideItemCache_.size()));
}

void SimpleReminder::updateOrder(int row, bool done) {
    TodoItem item = getItemFromTableRow(row);
    model_->removeRow(row);
    if (!done) {
        addItem(std::move(item), 0);
        return;
    }
    int idx = row;
    for (; idx < model_->rowCount(); ++idx) {
        if (ui_->tableView->model()->index(idx, 1).data().toString().toStdString() == std::string(u8"√")) {
            break;
        }
    }
    addItem(std::move(item), idx);
}

void SimpleReminder::closeEvent(QCloseEvent* e) {
    if (!modifyTag_) e->accept(); // 上次持久化后没有进行修改，则无需在退出时持久化
    else {
        this->hide(); // 营造快速退出假象（实际还未持久化233）
        if(SAVE_DISK) dataPersistence();
        redisPersistence();
        e->accept();
    } 
}

void SimpleReminder::moveWindow(const QPoint& start, const QPoint& end, unsigned int step)
{
    QPoint distance = end - start;
    QPoint stepPos, stepOne;
    if (end.x() == start.x())
    {
        stepOne.setY(step * (distance.y() > 0 ? 1 : -1));
    }
    else
    {
        stepOne.setX(step * (distance.x() > 0 ? 1 : -1));
    }
    stepPos = stepOne;

    int disLenght = distance.manhattanLength();
    while (stepPos.manhattanLength() <= disLenght)
    {
        move(start + stepPos);
        stepPos += stepOne;
    }

    move(end);

    recoverPosition_ = start;
}

void SimpleReminder::showDockWidget() {
    if (isVisable_)
    {
        return;
    }

    isVisable_ = true;

    int curHeight = height();
    int curWidth = width();

    QDesktopWidget* desktop = qApp->desktop();
    QRect rect = desktop->screenGeometry(this);
    QRect frameRect = frameGeometry();

    if (frameRect.left() == recoverPosition_.x() - (curWidth - HIDE_BORDER)
        && TEST_BIT(feature_, LeftArea))
    {
        moveWindow(pos(), recoverPosition_);
    }
    else if (frameRect.left() == recoverPosition_.x() + (curWidth - HIDE_BORDER)
        && TEST_BIT(feature_, RightArea))
    {
        moveWindow(pos(), recoverPosition_);
    }
    else if (frameRect.top() == recoverPosition_.y() - (curHeight - HIDE_BORDER)
        && TEST_BIT(feature_, TopArea))
    {
        moveWindow(pos(), recoverPosition_);
    }
    else
    {
        isVisable_ = false;
    }
}

void SimpleReminder::hideDockWidget() {
    if (isVisable_ == false) {
        return;
    }

    isVisable_ = false;

    int curHeight = height();
    int curWidth = width();

    QDesktopWidget* desktop = qApp->desktop();
    QRect rect = desktop->screenGeometry(this);

    if (frameGeometry().left() - CHECK_BORDER <= rect.top()
        && TEST_BIT(feature_, LeftArea))
    {
        moveWindow(pos(), pos() - QPoint(curWidth - HIDE_BORDER, 0));
    }
    else if (frameGeometry().right() + CHECK_BORDER >= rect.right()
        && TEST_BIT(feature_, RightArea))
    {
        moveWindow(pos(), pos() + QPoint(curWidth - HIDE_BORDER, 0));
    }
    else if (frameGeometry().top() - CHECK_BORDER <= rect.top()
        && TEST_BIT(feature_, TopArea))
    {
        moveWindow(pos(), pos() - QPoint(0, curHeight - HIDE_BORDER));
    }
    else
    {
        isVisable_ = true;
    }

    if (isVisable_ == false)
    {
        if (timer_ && timer_->isActive())
        {
            timer_->stop();
        }
    }
}

void SimpleReminder::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton)
    {
        dragPosition_ = e->globalPos() - frameGeometry().topLeft();
        e->accept();
    }
}

void SimpleReminder::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint pos = event->globalPos() - dragPosition_;

        QDesktopWidget* desktop = qApp->desktop();
        QRect rect = desktop->screenGeometry(QCursor::pos());
        QRect frameRect = frameGeometry();
        if (rect.top() >= pos.y())//修正顶端位置
        {
            pos.setY(rect.top());
        }

        if (rect.left() >= pos.x())//修正左侧位置
        {
            int leftScreenNumber = desktop->screenNumber(pos - QPoint(width(), 0));
            if (desktop->screenGeometry(leftScreenNumber).contains((pos - QPoint(width(), 0))) == false)
            {
                pos.setX(rect.left());
            }
        }

        if (rect.right() <= pos.x() + frameRect.width())//修正右侧位置
        {
            int rightScreenNumber = desktop->screenNumber(pos + QPoint(width(), 0));
            if (desktop->screenGeometry(rightScreenNumber).contains((pos + QPoint(width(), 0))) == false)
            {
                pos.setX(rect.right() - frameRect.width());
            }
        }
        move(pos);

        event->accept();
    }
}

void SimpleReminder::mouseReleaseEvent(QMouseEvent* event) {
    QWidget::mouseReleaseEvent(event);
}

void SimpleReminder::leaveEvent(QEvent* e) {
    QPoint mousePos = mapFromGlobal(QCursor::pos());
    if (rect().contains(mousePos) == false && mousePos.x() != rect().width()) {
        hideDockWidget();
    }
    else
    {
        if (timer_ == nullptr)
        {
            timer_ = new QTimer(this);
            connect(timer_, &QTimer::timeout, this, [this] {
                QPoint mousePos = mapFromGlobal(QCursor::pos());
                if (this->rect().contains(mousePos) == false && mousePos.x() != rect().width())
                {
                    hideDockWidget();
                }
                });
        }
        timer_->start(500);
    }
    QWidget::leaveEvent(e);
}

void SimpleReminder::enterEvent(QEvent* e) {
    if (timer_ && timer_->isActive()) {
        timer_->stop();
    }
    showDockWidget();
    QWidget::enterEvent(e);
}

SimpleReminder::~SimpleReminder(){
}
