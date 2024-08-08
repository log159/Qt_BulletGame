#-------------------------------------------------
#
# Project created by QtCreator 2023-02-04T08:28:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BulletGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Boss/boss.cpp \
    Boss/bossbullet.cpp \
    Enemy/enemy.cpp \
    Enemy/enemybullet.cpp \
    Hero/hero.cpp \
    Hero/herobullet.cpp \
    Others/boom.cpp \
    Others/edition.cpp \
    Others/map.cpp \
    Others/mycircular.cpp \
    Others/mycoordinate.cpp \
    Others/special.cpp \
    Others/specialrotate.cpp \
    Boss/bossbulletway.cpp \
    GameWidget/widget.cpp \
    GameWidget/gamewidget_1.cpp \
    GameWidget/gamewidget_2.cpp \
    Boss/boss_1.cpp \
    Boss/boss_2.cpp \
    Others/mylabel.cpp \
    GameWidget/mainwidget.cpp \
    GameWidget/startwidget.cpp \
    GameWidget/selectwidget.cpp \
    Config/cutimg.cpp \
    Enemy/enemybulletway.cpp \
    Others/bulletinformation.cpp \
    Others/enemyinformation.cpp \
    GameWidget/widgetsendway.cpp \
    GameWidget/sidebarwidget.cpp \
    Others/myimglabel.cpp \
    Others/prop.cpp

HEADERS += \
    Boss/boss.h \
    Boss/bossbullet.h \
    Config/config.h \
    Enemy/enemy.h \
    Enemy/enemybullet.h \
    Hero/hero.h \
    Hero/herobullet.h \
    Others/boom.h \
    Others/edition.h \
    Others/map.h \
    Others/mycircular.h \
    Others/mycoordinate.h \
    Others/myrect.h \
    Others/special.h \
    Others/specialrotate.h \
    Boss/bossbulletway.h \
    GameWidget/widget.h \
    GameWidget/gamewidget_1.h \
    GameWidget/gamewidget_2.h \
    Boss/boss_1.h \
    Boss/boss_2.h \
    Others/mylabel.h \
    GameWidget/mainwidget.h \
    GameWidget/startwidget.h \
    GameWidget/selectwidget.h \
    Config/cutimg.h \
    Config/config.h \
    Enemy/enemybulletway.h \
    Others/bulletinformation.h \
    Others/enemyinformation.h \
    Others/mathfunc.h \
    GameWidget/widgetsendway.h \
    GameWidget/sidebarwidget.h \
    Others/myimglabel.h \
    Others/prop.h

RESOURCES += \
    res.qrc



