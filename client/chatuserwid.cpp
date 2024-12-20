#include "chatuserwid.h"
#include "ui_chatuserwid.h"

ChatUserWid::ChatUserWid(QWidget *parent) :
    ListItemBase(parent),
    ui(new Ui::ChatUserWid)
{
    ui->setupUi(this);
    SetItemType(ListItemType::CHAT_USER_ITEM);
}

ChatUserWid::~ChatUserWid()
{
    delete ui;
}

QSize ChatUserWid::sizeHint() const
{
    return QSize(250, 70);
}

void ChatUserWid::SetInfo(QString name, QString head, QString msg)
{
    _name = name;
    _head = head;
    _msg = msg;

    QPixmap pixmap(_head);

    ui->icon_lb->setPixmap((pixmap.scaled(ui->icon_lb->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    ui->icon_lb->setScaledContents(true);

    QFontMetrics fontMetrics_name(ui->user_name_lb->font());
    QString nameText = fontMetrics_name.elidedText(_name, Qt::ElideRight, ui->user_name_lb->width());
    QFontMetrics fontMetrics_msg(ui->user_chat_lb->font());
    QString msgText = fontMetrics_msg.elidedText(_msg, Qt::ElideRight, ui->user_chat_lb->width());

    ui->user_name_lb->setText(nameText);
    ui->user_chat_lb->setText(msgText);
}


