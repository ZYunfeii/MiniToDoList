#pragma once
#include <mutex>
#include <fstream>
#include <qdatetime.h>
class Meta {
public:
	~Meta();
	static Meta* getInstance();
	int timeSinceLastUpdate() const;
	void setMetaTime(QDateTime&& time);
	void metaInit();
private:
	Meta();
	static Meta* instance_;
	static std::mutex mtx_;
	std::ifstream ifs_;
	std::ofstream ofs_;
	QDateTime metaTime_;
};

extern const std::string metaFileName;
extern const QString timeFormat;

