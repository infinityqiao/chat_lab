#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>
#include <QRegularExpression>
#include "QStyle"
#include <memory>
#include <iostream>
#include <mutex>
#include <QByteArray>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QSettings>
/******************************************************************************
 *
 * @file       global.h
 * @brief      repolish 用来刷新qss
 *
 * @author     infinity
 * @date       2024/12/14
 *****************************************************************************/
extern std::function<void(QWidget*)> repolish;

extern std::function<QString(QString)> xorString;

enum ReqId{
    ID_GET_VARIFY_CODE = 1001, // 获取验证码
    ID_REG_USER = 1002, // 注册用户
    ID_RESET_PWD = 1003, // 重置密码
    ID_LOGIN_USER = 1004, // 用户登录
    ID_CHAT_LOGIN = 1005, // 登陆聊天服务器
    ID_CHAT_LOGIN_RSP= 1006, // 登陆聊天服务器回包
    ID_SEARCH_USER_REQ = 1007, // 用户搜索请求
    ID_SEARCH_USER_RSP = 1008, // 搜索用户回包
    ID_ADD_FRIEND_REQ = 1009,  // 添加好友申请
    ID_ADD_FRIEND_RSP = 1010, // 申请添加好友回复
    ID_NOTIFY_ADD_FRIEND_REQ = 1011,  // 通知用户添加好友申请
    ID_AUTH_FRIEND_REQ = 1013,  // 认证好友请求
    ID_AUTH_FRIEND_RSP = 1014,  // 认证好友回复
    ID_NOTIFY_AUTH_FRIEND_REQ = 1015, // 通知用户认证好友申请
    ID_TEXT_CHAT_MSG_REQ  = 1017,  // 文本聊天信息请求
    ID_TEXT_CHAT_MSG_RSP  = 1018,  // 文本聊天信息回复
    ID_NOTIFY_TEXT_CHAT_MSG_REQ = 1019, // 通知用户文本聊天信息
};

enum Modules{
    REGISTERMOD = 0,
    RESETMOD = 1,
    LOGINMOD = 2,
};

enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1, // json 解析失败
    ERR_NETWORK = 2, // 网络错误
};

enum TipErr{
    TIP_SUCCESS = 0,
    TIP_EMAIL_ERR = 1,
    TIP_PWD_ERR = 2,
    TIP_CONFIRM_ERR = 3,
    TIP_PWD_CONFIRM = 4,
    TIP_VARIFY_ERR = 5,
    TIP_USER_ERR = 6
};

enum ClickLbState{
    Normal = 0,
    Selected = 1
};

extern QString gate_url_prefix;

struct ServerInfo{
    QString Host;
    QString Port;
    QString Token;
    int Uid;
};

// 聊天界面几种模式
enum ChatUIMode{
    SearchMode, // 搜索模式
    ChatMode, // 聊天模式
    ContactMode, // 联系模式
};

// 自定义QListWidgetItem的几种类型
enum ListItemType{
    CHAT_USER_ITEM, // 聊天用户
    CONTACT_USER_ITEM, // 联系人用户
    SEARCH_USER_ITEM, // 搜索到的用户
    ADD_USER_TIP_ITEM, // 提示添加用户
    INVALID_ITEM,  // 不可点击条目
    GROUP_TIP_ITEM, // 分组提示条目
    LINE_ITEM,  // 分割线
    APPLY_FRIEND_ITEM, // 好友申请
};

// 聊天角色
enum class ChatRole
{
    Self,   // 他人
    Other   // 自身
};

struct MsgInfo{
    QString msgFlag; // "text, image, file"
    QString content; // 表示文件和图像的 url ,文本信息
    QPixmap pixmap; // 文件和图片的缩略图
};

// 申请好友标签输入框最低长度
const int MIN_APPLY_LABEL_ED_LEN = 40;

const QString add_prefix = "添加标签 ";

const int  tip_offset = 5;

const std::vector<QString> strs ={
    "我好想吃草莓啊，可是草莓太贵了",
    "Man！What Can I say？",
    "Mamba Out！See u again",
    "那我问你那我问你，你是男的女的",
    "白银说的话，就像是癌症晚期说的话，他都这样了，你为什么不顺从他呢。",
    "你说得对，但这就是奎桑提，4700HP，300护甲，200魔抗",
    "无论你是跑酷大神，还是PVP大佬，还是PVP大佬，还是PVP大佬，还是PVP大佬，",
    "兄弟，兄弟，你好香",
    "打开你的电视机，大·家·们·的欲望之友，田中时价购物网",
    "时代少年团，我们喜欢你，我们喜欢马嘉祺丁程鑫宋亚轩",
    "大香蕉，一条大香蕉，你的感觉真的很奇妙~",
    "我是逆蝶，逆风飞翔的蝶，哪怕轰轰烈烈",
    "你是抱着怎样的决心说出这句话的，你能够肩负起别人的人生吗？"
    "莲瓣入水而不苦根，勿执着，安存法度之外，或不失于梦幻泡影，奇妙"
};

const std::vector<QString> heads = {
    ":/res/head_6.jpg",
    ":/res/head_7.jpg",
    ":/res/head_8.jpg",
    ":/res/head_9.jpg",
    ":/res/head_10.jpg",
    ":/res/head_11.jpg",
    ":/res/head_12.jpg",
    ":/res/head_13.jpg",
    ":/res/head_14.jpg",
    ":/res/head_15.jpg",
    ":/res/head_16.jpg"
};

const std::vector<QString> names = {
    "曼波",
    "柯洁",
    "五条悟",
    "特雷西娅",
    "咸鱼梦想家",
    "魂5",
    "星野爱",
    "奶龙",
    "阿诺",
    "otto",
    "last丶炫",
    "阿梓从小就很可爱",
    "范小勤",
    "科比·布莱恩特",
    "墨茶official",
    "奎隆",
};

const int CHAT_COUNT_PER_PAGE = 13;

#endif // GLOBAL_H
