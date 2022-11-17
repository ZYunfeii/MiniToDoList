#include "SimpleReminder.h"

SimpleReminder::SimpleReminder(QWidget *parent)
    : QMainWindow(parent),
    ui_(new Ui::SimpleReminderClass),
    model_(nullptr),
    tableName_("record")
{
    ui_->setupUi(this);
    setWindowIcon(QIcon(":/SimpleReminder/images/icon.ico"));
   
    ui_->tableView->setShowGrid(true);
    ui_->tableView->setGridStyle(Qt::DotLine);
    model_ = new QStandardItemModel();
    QStringList labels = {u8"事项", u8"完成"};
    model_->setHorizontalHeaderLabels(labels);
    ui_->tableView->setModel(model_);
    ui_->tableView->show();
    
    ui_->tableView->setColumnWidth(0, 345);
    ui_->tableView->setColumnWidth(1, 40);
    ui_->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ui_->tableView->setContextMenuPolicy(Qt::CustomContextMenu);  //少这句，右键没有任何反应的。
    rightMenu_ = new QMenu(ui_->tableView);
    addAction_ = new QAction(u8"新增", ui_->tableView);
    deleteAction_ = new QAction(u8"删除", ui_->tableView);
    rightMenu_->addAction(addAction_);
    rightMenu_->addAction(deleteAction_);
    connect(addAction_, SIGNAL(triggered()), this, SLOT(addActionTriggered()));
    connect(deleteAction_, SIGNAL(triggered()), this, SLOT(deleteActionTriggered()));
    connect(ui_->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(clickedRightMenu(QPoint)));
    connect(ui_->tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(doubleClicked(const QModelIndex&)));

    // 数据库相关初始化放最后
    if (!dbInit()) {
        QMessageBox::warning(this, u8"警告", u8"数据库打开失败。");
    }
}

void SimpleReminder::addItem(const QString thing, bool done) {
    auto itemThing = new QStandardItem(thing);
    QString tmp = (done == true ? u8"√" : u8"×");
    auto itemDone = new QStandardItem(tmp);
    itemDone->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QList<QStandardItem*> itemList = { itemThing, itemDone };
    model_->appendRow(itemList);
}

void SimpleReminder::clickedRightMenu(const QPoint& pos) {
    QModelIndex index = ui_->tableView->indexAt(pos);//获取鼠标点击位置项的索引
    if (index.isValid()) {
        deleteIndex_ = index;
        addAction_->setEnabled(false);
        deleteAction_->setEnabled(true);
    }
    else {
        addAction_->setEnabled(true);
        deleteAction_->setEnabled(false);
    }
    rightMenu_->exec(QCursor::pos());
}

void SimpleReminder::doubleClicked(const QModelIndex& index) {
    if (index.isValid() && index.column() == 1) {
        QString origin = model_->data(index).toString();
        QString tmp = (origin.toStdString() == std::string(u8"√") ? u8"×" : u8"√");
        model_->setData(index, tmp);
    }
}

void SimpleReminder::addActionTriggered() {
    addItem("", false);
}

void SimpleReminder::deleteActionTriggered() {
    model_->removeRow(deleteIndex_.row());
}

bool SimpleReminder::dbInit() {
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(QString("record.db"));
    if (!db_.open()){
        return false;
    }
    QSqlQuery query(db_);
    query.exec(QString("create table %1 (record varchar, done int2)").arg(tableName_));
    query.exec(QString("select * from %1").arg(tableName_));
    while (query.next()) {
        QString record = query.value(0).toString();
        bool done = query.value(1).toInt();
        addItem(record, done);
    }
    return true;
}

bool SimpleReminder::insertDB(QString thing, bool done) {
    QSqlQuery query(db_);
    query.prepare(QString("INSERT INTO %1 (record, done)"
                  "VALUES (:thing, :done)").arg(tableName_));
    query.bindValue(":done", qint8(done));
    query.bindValue(":thing", thing);
    bool flag = query.exec();
    return flag; 
}

void SimpleReminder::closeEvent(QCloseEvent* e) {
    QSqlQuery query(db_);
    query.prepare(QString("delete from %1").arg(tableName_));
    if (!query.exec()) {
        QMessageBox::warning(this, u8"警告", u8"清理数据库失败。");
        e->accept();
        return;
    }
    int row = ui_->tableView->model()->rowCount();
    for (int i = 0; i < row; ++i) {
        QString thing = ui_->tableView->model()->index(i, 0).data().toString();
        QString tmp = ui_->tableView->model()->index(i, 1).data().toString();
        bool done = (tmp.toStdString() == std::string(u8"√") ? 1 : 0);
        if (!insertDB(thing, done)) {
            QMessageBox::warning(this, u8"警告", u8"数据库插入失败。");
            e->accept();
            return;
        }
    }
    e->accept();
}

SimpleReminder::~SimpleReminder(){
}
