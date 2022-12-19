#include "login.h"

login::login(QWidget *parent)
	: QDialog(parent),
	ui_(new Ui::loginClass)
{
	ui_->setupUi(this);
	redisInit();
	connect(ui_->loginButton, &QPushButton::clicked, this, [this]() {
		if (!checkValid()) {
			QMessageBox::information(this, u8"提示", u8"请输入用户名！");
			return;
		}
		std::string passWord;
		bool ifExist = false;
		redisClient_->get(ui_->userName->text().toStdString(), [this, &passWord, &ifExist](cpp_redis::reply& reply) {
			if (!reply.is_null()) {
				passWord = reply.as_string();
				ifExist = true;
			}
		});
		redisClient_->sync_commit();
		if (!ifExist) result_ = false;
		else result_ = passWord == ui_->passWord->text().toStdString();
		if (result_) {
			redisTopic_ = makeRedisTopic();
			this->close();
		}
		else {
			QMessageBox::information(this, u8"提示", u8"密码错误！");
		}
	});
	connect(ui_->signupButton, &QPushButton::clicked, this, [this]() {
		if (!checkValid()) {
			QMessageBox::information(this, u8"提示", u8"请输入用户名！");
			return;
		}
		bool ifExist = false;
		redisClient_->exists({ ui_->userName->text().toStdString() }, [this, &ifExist](cpp_redis::reply& reply) {
			if (reply.as_integer()) {
				ifExist = true;
			}
		});
		redisClient_->sync_commit();
		if (ifExist) {
			QMessageBox::information(this, u8"提示", u8"用户已经存在，请直接登录！");
			return;
		}
		bool signupTag = false;
		redisClient_->set(ui_->userName->text().toStdString(), ui_->passWord->text().toStdString(), [this, &signupTag](cpp_redis::reply& reply) {
			if (reply.ok()) {
				signupTag = true;
				return;
			}
		});
		redisClient_->sync_commit();
		if (signupTag) {
			QMessageBox::information(this, u8"提示", u8"注册成功！");
		}
	});
}

bool login::checkIPLive() {
	return Utils::IPLive(QString::fromStdString(redisIP_), redisPort_);
}

void login::redisInit() {
	bool ipLive = checkIPLive();
	if (!ipLive) {
		QMessageBox::warning(this, u8"警告", u8"请检查网络后重启！");
		exit(1);
	}

	cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);
	redisClient_ = new cpp_redis::client;
	redisClient_->connect(redisIP_, redisPort_, [this](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
		if (status == cpp_redis::client::connect_state::dropped) {
			QMessageBox::warning(this, u8"警告", u8"Redis连接错误！");
			exit(1);
		}
	});
	// 校验密码
	redisClient_->auth(redisPassword_, [](cpp_redis::reply& reply) {
		// qDebug() << "auth info: " << reply ;
	});
}

cpp_redis::client* login::getRedisConn() {
	return redisClient_;
}

bool login::getRes() {
	return result_;
}

std::string login::getRedisTopic() {
	return redisTopic_;
}

inline std::string login::makeRedisTopic() {
	return "todolist:" + ui_->userName->text().toStdString();
}

bool login::checkValid() {
	if (ui_->userName->text() == "") {
		return false;
	}
	return true;
}

login::~login()
{}
