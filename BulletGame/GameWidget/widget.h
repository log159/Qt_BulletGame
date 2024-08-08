#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <ctime>
#include <Others/boom.h>
#include <QPixmap>
#include <QImage>
#include <QPushButton>
#include <QVector>
#include <QDebug>

#include "Config/config.h"
#include "Others/map.h"
#include "Others/edition.h"
#include "Others/bulletinformation.h"
#include "Others/enemyinformation.h"
#include "sidebarwidget.h"
#include "widgetsendway.h"

#include "Hero/hero.h"
#include "Boss/boss.h"
#include "Enemy/enemy.h"

class Widget : public QWidget
{
    Q_OBJECT

public:

    //主要成员类
    Map *m_Map;//地图指针
    Hero *m_Hero;//主角指针
    Boss *m_Boss;//Boss指针
    Enemy*m_Enemy;//怪物数组指针

    //边栏
    SidebarWidget * m_SidebarPtr;

    WidgetSendWay* enSendWay;//出怪方法

    //特效类
    //Boom指针
    Boom *m_BoomPtr;

    //Hero 方向键计时器
    QTimer *m_HeroTimerUp;
    QTimer *m_HeroTimerLeft;
    QTimer *m_HeroTimerDown;
    QTimer *m_HeroTimerRight;
    QTimer *m_HeroTimerBoom;

    //Hero 弹幕键计时器
    QTimer *m_HeroSendBullet;
    //特殊类计时器
    QTimer *m_RotateTimer;//弹幕旋转效果计时器
    QTimer *m_Timer;//默认刷新
    QTimer *m_PaintTimer;//绘图计时器

    //额外类计时器

    QTimer *enemySendTimer;//敌人派出
    QTimer *enemyButSendTimer;//敌人弹幕派出
    QTimer *enemyButNewTimer;//敌人弹幕刷新
    QTimer *enemyNewTimer;//敌人位移和形态改变
    QTimer *bossButSendTimer;//Boss派出弹幕强度计时器
    QTimer *bossButNewTimer;//Boss更新弹幕强度计时器
    QTimer *bossNewTimer;//Boss位移更新计时器



    //----------------特殊调整----------------

    int m_AddEnemyNum=0;//出怪时间积累

    int imageRotate=0;//弹幕旋转角度累加 快

    int imageRotateSmall=0;//弹幕旋转角度累加 慢

    int theTime=1;//1 enemy 2 Boss

    int printId=0;//特殊效果id

public:

    //-------------函数-----------------


    virtual void initNumber()=0;//初始化成员数据

    virtual void sendEnemy(int sendEnemyId,EnemyInformation & enemyInfor,int sendBulletId,BulletInformation & butInfor)=0;//派出敌人

    virtual void sendEnemyTimer()=0;//出怪函数

    void startAllTime();//开始所有计时器

    void stopAllTime();//停止所有计时器

    void gamePlay();//游戏开始（包含默认刷新数据和全局绘图）

    void initWidget();//初始化自身数据

    void sendBoom(int x,int y);//派出爆炸

    void newBoom();//更新爆炸

    void enemyOver();//对敌人伤害判定

    void heroOverE();//对主角伤害判定

    void heroOverB();//对主角伤害判定

    void sendBoss();//派出boss

    void newBoss();//刷新Boss

    void bossOver();//对boss伤害判定

    void propOver();//对道具的回收判定

    void keyHero();//键盘类英雄事件（位移）

    void keyHeroBullet();//键盘类英雄事件（弹幕）

    void gameOver();//game die

    void gameWin();//game win

    void sendEndLabel(int id);//派出结束Label

    //-----------------------Timer结尾函数为计时器直属------------------------------

    void sendEnemyBulletTimer();//派出弹幕函数

    void newEnemyBulletTimer();//更新弹幕函数

    void newEnemyTimer();//更新敌人位移和形态函数

    void sendBossBulletTimer();//Boss派出弹幕函数

    void newBossBulletTimer();//Boss弹幕更新函数

    void newBossTimer();//Boss位移更新函数

    //-----------------------------系统提供的函数----------------------------------

    void keyPressEvent(QKeyEvent *event);//键盘事件按下

    void keyReleaseEvent(QKeyEvent *event);//键盘事件松开

    void paintEvent(QPaintEvent *event);//全局绘图

    //--------------------------------绘图事件------------------------------------
    void paintMap(QPainter*painter);

    void paintHero(QPainter*painter);

    void paintBoom(QPainter*painter);

    void paintEnemy(QPainter*painter);

    void paintBoss(QPainter*painter);

    explicit Widget(QWidget *parent = 0);
    virtual~Widget();



signals:
    void quit();



};

#endif // WIDGET_H
