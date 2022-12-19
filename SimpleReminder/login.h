#pragma once

#include <QDialog>
#include "ui_login.h"
#include <cpp_redis/cpp_redis>
#include <QMessageBox>
#include "utils.h"

class login : public QDialog
{
	Q_OBJECT

public:
	login(QWidget *parent = nullptr);
	~login();
	bool getRes();
	bool checkIPLive();
	std::string getRedisTopic();
	cpp_redis::client* getRedisConn();
	
private:
	Ui::loginClass* ui_;
	bool checkValid();
	bool result_ = false;
	std::string redisTopic_ = "";
	const std::string redisIP_ = "43.143.229.22";
	uint32_t redisPort_ = 6379;
	const std::string redisPassword_ = "yunfei";
	cpp_redis::client* redisClient_ = nullptr;

	inline std::string makeRedisTopic();
	void redisInit();
};
