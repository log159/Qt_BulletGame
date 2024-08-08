#ifndef GAMEWIDGET_2_H
#define GAMEWIDGET_2_H

#include "widget.h"

#include "Boss/boss_2.h"

class GameWidget_2:public Widget
{
public:

    void initNumber();//初始化成员数据

    void sendEnemy(int sendEnemyId,EnemyInformation & enemyInfor,int sendBulletId,BulletInformation & butInfor);//派出敌人

    void sendEnemyTimer();//出怪函数

    GameWidget_2();
};

#endif // GAMEWIDGET_2_H
