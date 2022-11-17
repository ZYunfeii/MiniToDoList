#include "SimpleReminder.h"

SimpleReminder::SimpleReminder(QWidget *parent)
    : QMainWindow(parent),
    ui_(new Ui::SimpleReminderClass),
    model_(nullptr),
    tableName_("record"),
    hideTag_(false)
{
    ui_->setupUi(this);
    setWindowIcon(QIcon(":/SimpleReminder/images/icon.ico"));
   
    ui_->tableView->setShowGrid(true);
    ui_->tableView->setGridStyle(Qt::DotLine);
    model_ = new QStandardItemModel();
    QStringList labels = {u8"����", u8"���"};
    model_->setHorizontalHeaderLabels(labels);
    ui_->tableView->setModel(model_);
    ui_->tableView->show();
    
    ui_->tableView->setColumnWidth(0, 345);
    ui_->tableView->setColumnWidth(1, 40);
    ui_->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ui_->tableView->setContextMenuPolicy(Qt::CustomContextMenu);  //����䣬�Ҽ�û���κη�Ӧ�ġ�
    rightMenu_ = new QMenu(ui_->tableView);
    addAction_ = new QAction(u8"����", ui_->tableView);
    deleteAction_ = new QAction(u8"ɾ��", ui_->tableView);
    hideAction_ = new QAction(u8"����", ui_->tableView);
    showAllAction_ = new QAction(u8"����", ui_->tableView);
    rightMenu_->addAction(addAction_);
    rightMenu_->addAction(deleteAction_);
    rightMenu_->addAction(hideAction_);
    rightMenu_->addAction(showAllAction_);
    connect(addAction_, SIGNAL(triggered()), this, SLOT(addActionTriggered()));
    connect(deleteAction_, SIGNAL(triggered()), this, SLOT(deleteActionTriggered()));
    connect(hideAction_, SIGNAL(triggered()), this, SLOT(hideActionTriggered()));
    connect(showAllAction_, SIGNAL(triggered()), this, SLOT(showAllActionTriggered()));
    connect(ui_->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(clickedRightMenu(QPoint)));
    connect(ui_->tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(doubleClicked(const QModelIndex&)));

    // ���ݿ���س�ʼ�������
    if (!dbInit()) {
        QMessageBox::warning(this, u8"����", u8"���ݿ��ʧ�ܡ�");
    }
    updateThingsCount();
}

void SimpleReminder::addItem(const QString thing, bool done) {
    auto itemThing = new QStandardItem(thing);
    QString tmp = (done == true ? u8"��" : u8"��");
    auto itemDone = new QStandardItem(tmp);
    itemDone->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QList<QStandardItem*> itemList = { itemThing, itemDone };
    model_->appendRow(itemList);
}

void SimpleReminder::clickedRightMenu(const QPoint& pos) {
    QModelIndex index = ui_->tableView->indexAt(pos);//��ȡ�����λ���������
    if (index.isValid()) {
        deleteIndex_ = index;
        addAction_->setEnabled(false);
        deleteAction_->setEnabled(true);
    }
    else {
        addAction_->setEnabled(true);
        deleteAction_->setEnabled(false);
    }
    if (!hideTag_) {
        hideAction_->setEnabled(true);
        showAllAction_->setEnabled(false);
    }
    else {
        hideAction_->setEnabled(false);
        showAllAction_->setEnabled(true);
    }
    

    rightMenu_->exec(QCursor::pos());
}

void SimpleReminder::doubleClicked(const QModelIndex& index) {
    if (index.isValid() && index.column() == 1) {
        QString origin = model_->data(index).toString();
        QString tmp = (origin.toStdString() == std::string(u8"��") ? u8"��" : u8"��");
        model_->setData(index, tmp);
    }
    updateThingsCount();
}

void SimpleReminder::addActionTriggered() {
    addItem("", false);
    updateThingsCount();
}

void SimpleReminder::deleteActionTriggered() {
    model_->removeRow(deleteIndex_.row());
    updateThingsCount();
}

void SimpleReminder::hideActionTriggered() {
    for (int i = 0; i < ui_->tableView->model()->rowCount(); ++i) {
        QString thing = ui_->tableView->model()->index(i, 0).data().toString();
        QString tmp = ui_->tableView->model()->index(i, 1).data().toString();
        bool done = (tmp.toStdString() == std::string(u8"��") ? 1 : 0);
        if (done) {
            TodoItem item{ thing, done };
            hideItemCache_.push_back(item);
            model_->removeRow(i);
            i--;
        }
    }
    hideTag_ = true;
}

void SimpleReminder::showAllActionTriggered() {
    if (!hideTag_) {
        return;
    }
    for (auto& item : hideItemCache_) {
        addItem(item.thing, item.done);
    }
    hideItemCache_.clear();
    hideTag_ = false;
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
        QMessageBox::warning(this, u8"����", u8"�������ݿ�ʧ�ܡ�");
        e->accept();
        return;
    }
    int row = ui_->tableView->model()->rowCount();
    // �Ȳ���δ��ɵģ��ٲ�����ɵ�
    QVector<QString> notDone;
    for (int i = 0; i < row; ++i) {
        QString thing = ui_->tableView->model()->index(i, 0).data().toString();
        QString tmp = ui_->tableView->model()->index(i, 1).data().toString();
        bool done = (tmp.toStdString() == std::string(u8"��") ? 1 : 0);
        if (done) {
            notDone.push_back(thing);
            continue;
        }
        if (!insertDB(thing, false)) {
            QMessageBox::warning(this, u8"����", u8"���ݿ����ʧ�ܡ�");
        }
    }
    for (int i = 0; i < notDone.size(); ++i) {
        if (!insertDB(notDone[i], true)) {
            QMessageBox::warning(this, u8"����", u8"���ݿ����ʧ�ܡ�");
        }
    }
    // �����ػ����е��������������ݿ�
    for (int i = 0; i < hideItemCache_.size(); ++i) {
        if (!insertDB(hideItemCache_[i].thing, hideItemCache_[i].done)) {
            QMessageBox::warning(this, u8"����", u8"���ݿ����ʧ�ܡ�");
        }
    }
    e->accept();
}

void SimpleReminder::updateThingsCount() {
    int row = ui_->tableView->model()->rowCount();
    int total = 0, completed = 0;
    for (int i = 0; i < row; ++i) {
        QString thing = ui_->tableView->model()->index(i, 0).data().toString();
        QString tmp = ui_->tableView->model()->index(i, 1).data().toString();
        bool done = (tmp.toStdString() == std::string(u8"��") ? 1 : 0);
        if (done) completed++;
        total++;
    }
    for (auto& item : hideItemCache_) {
        if (item.done) completed++;
        total++;
    }
    ui_->total->setText(QString::number(total));
    ui_->completed->setText(QString::number(completed));
}

SimpleReminder::~SimpleReminder(){
}
