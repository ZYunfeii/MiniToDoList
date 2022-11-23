#pragma once

#include <QDialog>
#include "ui_PeriodDialog.h"

class PeriodDialog : public QDialog
{
	Q_OBJECT

public:
	PeriodDialog(QWidget *parent = nullptr);
	int getPeriod() const;
	~PeriodDialog();

private:
	Ui::PeriodDialogClass* ui_;
	int period_;
};
