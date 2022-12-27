#pragma once

#include <QDialog>
#include "ui_ShowInfo.h"
#include "item.h"

class ShowInfo : public QDialog
{
	Q_OBJECT

public:
	ShowInfo(QWidget *parent = nullptr);
	~ShowInfo();
	void append(QString& str);
	void append(TodoItem& item);
	void clear();

private:
	void makeHead();
	Ui::ShowInfoClass* ui_;
	uint32_t idx_;
};
