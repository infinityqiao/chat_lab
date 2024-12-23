QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RC_ICONS = icon.ico
DESTDIR = ./bin

SOURCES += \
    adduseritem.cpp \
    applyfriend.cpp \
    applyfrienditem.cpp \
    applyfriendlist.cpp \
    applyfriendpage.cpp \
    authenfriend.cpp \
    bubbleframe.cpp \
    chatdialog.cpp \
    chatitembase.cpp \
    chatpage.cpp \
    chatuserlist.cpp \
    chatuserwid.cpp \
    chatview.cpp \
    clickedbtn.cpp \
    clickedlabel.cpp \
    clickedoncelabel.cpp \
    contactuserlist.cpp \
    conuseritem.cpp \
    customizeedit.cpp \
    findfaildlg.cpp \
    findsuccessdlg.cpp \
    friendinfopage.cpp \
    friendlabel.cpp \
    global.cpp \
    grouptipitem.cpp \
    httpmgr.cpp \
    listitembase.cpp \
    loadingdlg.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    messagetextedit.cpp \
    picturebubble.cpp \
    registerdialog.cpp \
    resetdialog.cpp \
    searchlist.cpp \
    statewidget.cpp \
    tcpmgr.cpp \
    textbubble.cpp \
    timerbtn.cpp \
    userdata.cpp \
    usermgr.cpp

HEADERS += \
    adduseritem.h \
    applyfriend.h \
    applyfrienditem.h \
    applyfriendlist.h \
    applyfriendpage.h \
    authenfriend.h \
    bubbleframe.h \
    chatdialog.h \
    chatitembase.h \
    chatpage.h \
    chatuserlist.h \
    chatuserwid.h \
    chatview.h \
    clickedbtn.h \
    clickedlabel.h \
    clickedoncelabel.h \
    contactuserlist.h \
    conuseritem.h \
    customizeedit.h \
    findfaildlg.h \
    findsuccessdlg.h \
    friendinfopage.h \
    friendlabel.h \
    global.h \
    grouptipitem.h \
    httpmgr.h \
    listitembase.h \
    loadingdlg.h \
    logindialog.h \
    mainwindow.h \
    messagetextedit.h \
    picturebubble.h \
    registerdialog.h \
    resetdialog.h \
    searchlist.h \
    singleton.h \
    statewidget.h \
    tcpmgr.h \
    textbubble.h \
    timerbtn.h \
    userdata.h \
    usermgr.h

FORMS += \
    adduseritem.ui \
    applyfriend.ui \
    applyfrienditem.ui \
    applyfriendpage.ui \
    authenfriend.ui \
    chatdialog.ui \
    chatpage.ui \
    chatuserwid.ui \
    conuseritem.ui \
    findfaildlg.ui \
    findsuccessdlg.ui \
    friendinfopage.ui \
    friendlabel.ui \
    grouptipitem.ui \
    loadingdlg.ui \
    logindialog.ui \
    mainwindow.ui \
    registerdialog.ui \
    resetdialog.ui

TRANSLATIONS += \
    chat_lab_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc

DISTFILES += \
    config.ini \
    res/head_10.jpg \
    res/head_11.jpg \
    res/head_12.jpg \
    res/head_13.jpg \
    res/head_14.jpg \
    res/head_15.jpg \
    res/head_16.jpg \
    res/head_3.jpg \
    res/head_4.jpg \
    res/head_5.jpg \
    res/head_6.jpg \
    res/head_7.jpg \
    res/head_8.jpg \
    res/head_9.jpg

CONFIG(debug, debug | release) {
    TargetConfig = $${PWD}/config.ini
    TargetConfig = $$replace(TargetConfig, /, \\)
    OutputDir =  $${OUT_PWD}/$${DESTDIR}
    OutputDir = $$replace(OutputDir, /, \\)
    QMAKE_POST_LINK += copy /Y \"$$TargetConfig\" \"$$OutputDir\" &

    # static path file
    StaticDir = $${PWD}/static
    StaticDir = $$replace(StaticDir, /, \\)
    QMAKE_POST_LINK += xcopy /Y /E /I \"$$StaticDir\" \"$$OutputDir\\static\\\"
} else {
    TargetConfig = $${PWD}/config.ini
    TargetConfig = $$replace(TargetConfig, /, \\)
    OutputDir =  $${OUT_PWD}/$${DESTDIR}
    OutputDir = $$replace(OutputDir, /, \\)
    QMAKE_POST_LINK += copy /Y \"$$TargetConfig\" \"$$OutputDir\" &

    # static path file
    StaticDir = $${PWD}/static
    StaticDir = $$replace(StaticDir, /, \\)
    QMAKE_POST_LINK += xcopy /Y /E /I \"$$StaticDir\" \"$$OutputDir\\static\\\"
}

win32-msvc*:QMAKE_CXXFLAGS += /wd"4819" /utf-8
