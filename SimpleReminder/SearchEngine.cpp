#include "SearchEngine.h"
#include <QDebug>
static constexpr int R = 256;
static constexpr long Q = 1658598167;

SearchEngine::SearchEngine(QList<TodoItem>& hideItemCache, QList<TodoItem>& temporaryCache, QWidget *parent)
	: QDialog(parent),
	ui_(new Ui::SearchEngineClass),
	hideItemCache_(hideItemCache),
	temporaryCache_(temporaryCache),
	clickedTag_(false)
{
	ui_->setupUi(this);
	connect(ui_->searchButton, &QPushButton::clicked, this, &SearchEngine::search);
}

void SearchEngine::search() {
	clickedTag_ = true;
	searchRes_.clear();
	QString pattern = ui_->searchText->text();
	doSearch(temporaryCache_, pattern);
	doSearch(hideItemCache_, pattern);
	this->hide();
}

void SearchEngine::doSearch(QList<TodoItem>& src, QString& pat) {
	std::for_each(src.begin(), src.end(), [this, &pat](TodoItem& it){
		if (rabinKarp(it.thing + it.createTime, pat)) {
			searchRes_.push_back(it);
		}
	});
}

// rabin karp字符串匹配算法 时间复杂度 O(N + L) 查找txt是否存在pat字串
bool SearchEngine::rabinKarp(QString txt, QString& pat) {
	int L = pat.size();
	long long RL = 1; // windows x64 long是4字节 long long 8字节
	for (int i = 1; i <= L - 1; ++i) {
		RL = (R * RL) % Q;
	}
	int left = 0, right = 0;
	long long windowHash = 0;
	long long patHash = 0;
	// 计算pat的hash值
	for (int i = 0; i < pat.size(); ++i) {
		patHash = ((R * patHash) % Q + pat[i].toLatin1()) % Q;
	}
	while (right < txt.size()) {
		QChar c = txt[right++];
		windowHash = ((windowHash * R) % Q + c.toLatin1()) % Q;
		if (right - left == L) {
			if (windowHash == patHash) {
				if (txt.mid(left, right - left) == pat) {
					return true;
				}
			}
			QChar d = txt[left++];
			windowHash = (windowHash - (RL * d.toLatin1()) % Q + Q) % Q;
		}
	}
	return false;
}

QList<TodoItem>& SearchEngine::getSearchRes() {
	clickedTag_ = false;
	return searchRes_;
}

bool SearchEngine::clicked() {
	return clickedTag_;
}

void SearchEngine::setCache(QList<TodoItem>& hideItemCache, QList<TodoItem>& temporaryCache) {
	hideItemCache_ = hideItemCache;
	temporaryCache_ = temporaryCache;
}

SearchEngine::~SearchEngine()
{}
