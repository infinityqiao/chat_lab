#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmgr.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->password_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);
    ui->error_tip->setProperty("state", "normal");
    repolish(ui->error_tip);
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);

    initHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_get_code_btn_clicked()
{
    auto email = ui->email_edit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if (match) {
        showTip(tr("邮箱地址正确"), true);
        // 发送 http 验证码
    } else {
        showTip(tr("邮箱地址不正确"), false);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS) {
        showTip(tr("网络请求错误"), false);
        return;
    }

    // 解析 JSON 字符串
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()) {
        showTip(tr("json解析失败"), false);
        return;
    }
    // JSON 解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析失败"), false);
        return;
    }

    _handlers[id](jsonDoc.object());
    return;
}

void RegisterDialog::initHttpHandlers()
{
    // 注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"), false);
            return;
        }

        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱，注意查收"), true);
        qDebug() << "email is" << email;
    });
}

void RegisterDialog::showTip(QString str, bool b_ok)
{
    if(b_ok){
        ui->error_tip->setProperty("state", "normal");
    } else {
        ui->error_tip->setProperty("state", "error");
    }
    ui->error_tip->setText(str);

    repolish(ui->error_tip);
}
