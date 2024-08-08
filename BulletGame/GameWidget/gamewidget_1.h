#ifndef GAMEWIDGET_1_H
#define GAMEWIDGET_1_H

#include "widget.h"

#include "Boss/boss_1.h"

class GameWidget_1:public Widget
{
public:

    void initNumber();//初始化成员数据

    void sendEnemy(int sendEnemyId,EnemyInformation & enemyInfor,int sendBulletId,BulletInformation & butInfor);//派出敌人

    void sendEnemyTimer();//出怪函数

    GameWidget_1();
};

#endif // GAMEWIDGET_1_H
