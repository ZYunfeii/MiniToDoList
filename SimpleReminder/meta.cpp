#include "meta.h"

Meta* Meta::instance_ = nullptr;
std::mutex Meta::mtx_;
const std::string metaFileName = "meta";
const QString timeFormat = "yyyy-MM-dd";

Meta::Meta() {	
}

void Meta::metaInit() {
	ifs_.open(metaFileName, std::ios::in);
	if (!ifs_.is_open()) {
		ofs_.open(metaFileName, std::ios::out);
		QString time = QDateTime::currentDateTime().toString(timeFormat);
		ofs_ << time.toStdString();
		ofs_.close();
		ifs_.open(metaFileName, std::ios::in);
	}
	assert(ifs_.is_open() == true);
	char buf[1024];
	ifs_ >> buf;
	metaTime_ = QDateTime::fromString(buf, timeFormat);
	//std::string m = metaTime_.toString(timeFormat).toStdString();
}

Meta* Meta::getInstance() {
	if (instance_ == nullptr) {
		std::unique_lock<std::mutex> lk(mtx_);
		if (instance_ == nullptr) {
			instance_ = new Meta;
		}
	}
	return instance_;
}

int Meta::timeSinceLastUpdate() const {
	return metaTime_.daysTo(QDateTime::currentDateTime());
}

void Meta::setMetaTime(QDateTime&& time) {
	ofs_.open(metaFileName, std::ios::out);
	ofs_ << time.toString(timeFormat).toStdString();
	ofs_.close();
}

Meta::~Meta() {
	ifs_.close();
}
