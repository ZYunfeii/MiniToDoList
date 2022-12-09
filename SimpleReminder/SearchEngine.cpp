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
	temItemSelectedIdx_ = doSearch(temporaryCache_, pattern);
	hideItemSelectedIdx_ = doSearch(hideItemCache_, pattern);
	this->hide();
}

QVector<int> SearchEngine::doSearch(QList<TodoItem>& src, QString& pat) {
	int idx = 0;
	QVector<int> v;
	std::for_each(src.begin(), src.end(), [this, &pat, &idx, &v](TodoItem& it){
		if (rabinKarp(it.thing + it.createTime, pat)) {
			searchRes_.push_back(it);
			v.push_back(idx);
		}
		idx++;
	});
	return v;
}

// rabin karp�ַ���ƥ���㷨 ʱ�临�Ӷ� O(N + L) ����txt�Ƿ����pat�ִ�
bool SearchEngine::rabinKarp(QString txt, QString& pat) {
	int L = pat.size();
	long long RL = 1; // windows x64 long��4�ֽ� long long 8�ֽ�
	for (int i = 1; i <= L - 1; ++i) {
		RL = (R * RL) % Q;
	}
	int left = 0, right = 0;
	long long windowHash = 0;
	long long patHash = 0;
	// ����pat��hashֵ
	for (int i = 0; i < pat.size(); ++i) {
		patHash = ((R * patHash) % Q + pat[i].toLatin1()) % Q;
	}
	while (right < txt.size()) {
		QChar c = txt[right++];
		windowHash = ((windowHash * R) % Q + c.toLatin1()) % Q;
		if (right - left == L) {
			if (windowHash == patHash) {
				if (txt.mid(left, right - left) == pat) { // O(L) ���٣��ʲ���
					return true;
				}
			}
			QChar d = txt[left++];
			windowHash = (windowHash - (RL * d.toLatin1()) % Q + Q) % Q;
		}
	}
	return false;
}

bool SearchEngine::updateItem(QVector<TodoItem>& v) {
	if (v.size() != temItemSelectedIdx_.size() + hideItemSelectedIdx_.size()) {
		return false;
	}
	for (int i = 0, idx1 = 0, idx2 = 0; i < v.size(); ++i) {
		if (i < temItemSelectedIdx_.size()) {
			temporaryCache_[temItemSelectedIdx_[idx1++]] = v[i];
		}
		else {
			if (!v[i].done) {
				// ������������޸����Ƿ���ɣ���δ��ɸ�Ϊ���
				temporaryCache_.push_back(v[i]);
				hideItemCache_.removeAt(hideItemSelectedIdx_[idx2++]);
				continue;
			}
			hideItemCache_[hideItemSelectedIdx_[idx2++]] = v[i];
		}
	}
	return true;
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

const QVector<int>& SearchEngine::getTemItemSelectedIdx() {
	return temItemSelectedIdx_;
}

const QVector<int>& SearchEngine::getHideItemSelectedIdx() {
	return hideItemSelectedIdx_;
}

SearchEngine::~SearchEngine()
{}
