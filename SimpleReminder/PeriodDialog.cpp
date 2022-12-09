#include "PeriodDialog.h"

PeriodDialog::PeriodDialog(QWidget *parent)
	: QDialog(parent),
	ui_(new Ui::PeriodDialogClass), 
	period_(-1)
{
	ui_->setupUi(this);
	connect(ui_->periodButton, &QPushButton::clicked, this, [this]() {
		if (ui_->periodEdit->text().isEmpty()) {
			period_ = -1;
			return;
		}
		period_ = ui_->periodEdit->text().toInt();
		if (period_ <= 0 && period_ != -1) {
			period_ = -1;
			QMessageBox::warning(this, u8"警告", "周期不能设置为小于等于0且不为-1的值（-1默认无周期）！");
			return;
		}
		this->hide();
	});
}

int PeriodDialog::getPeriod() const {
	return period_;
}

PeriodDialog::~PeriodDialog()
{}
