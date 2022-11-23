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
		this->hide();
	});
}

int PeriodDialog::getPeriod() const {
	return period_;
}

PeriodDialog::~PeriodDialog()
{}
