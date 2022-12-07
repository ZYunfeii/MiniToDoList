#pragma once

#include <QDialog>
#include <algorithm>
#include "ui_SearchEngine.h"
#include "item.h"

class SearchEngine : public QDialog
{
	Q_OBJECT

public:
	SearchEngine(QList<TodoItem>& hideItemCache, QList<TodoItem>& temporaryCache, QWidget *parent = nullptr);
	~SearchEngine();

	void setCache(QList<TodoItem>& hideItemCache, QList<TodoItem>& temporaryCache);
	bool rabinKarp(QString txt, QString& pat);
	QList<TodoItem>& getSearchRes();
	bool clicked();

public slots:
	void search();
	void doSearch(QList<TodoItem>& src, QString& pat);
	

private:
	Ui::SearchEngineClass* ui_;

	QList<TodoItem>& hideItemCache_;
	QList<TodoItem>& temporaryCache_;

	QList<TodoItem> searchRes_;
	bool clickedTag_;
};
