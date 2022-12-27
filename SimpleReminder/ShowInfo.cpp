#include "ShowInfo.h"

ShowInfo::ShowInfo(QWidget *parent)
	: QDialog(parent),
	ui_(new Ui::ShowInfoClass),
	idx_(0)
{
	ui_->setupUi(this);
	makeHead();
}

void ShowInfo::makeHead() {
	ui_->textBrowser->append(u8"昨天您完成了如下事务：");
}

void ShowInfo::append(QString& str) {
	idx_++;
	ui_->textBrowser->append(QString::number(idx_) + ":" + str);
}

void ShowInfo::append(TodoItem& item) {
	append(item.thing);
}

void ShowInfo::clear() {
	ui_->textBrowser->clear();
	makeHead();
	idx_ = 0;
}

ShowInfo::~ShowInfo()
{}
