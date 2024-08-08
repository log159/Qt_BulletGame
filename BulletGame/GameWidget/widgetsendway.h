#ifndef WIDGETSENDWAY_H
#define WIDGETSENDWAY_H
#include <QDebug>

#include "Enemy/enemy.h"
#include "Others/bulletinformation.h"
#include "Others/enemyinformation.h"

class WidgetSendWay
{
private:
    Enemy * enemyPtr;
    EnemyInformation enInfor;
    int sendBut;
    BulletInformation buInfor;

public:
    void setInformation(EnemyInformation & enemyInfor,int sendBulletId,BulletInformation & butInfor);//获取信息
    void setEnemyInformation(Enemy*en);

public:

    //上场随机
    void upRand();
    //上场随机 快
    void upRandQuick();
    //上场错位
    void upDislocate();
    //半角随机
    void halfAngleRand();
    //上场角落
    void upCorner();
    //左场慢速
    void leftSmall();
    //右场慢速
    void rightSmall();
    //中场慢速
    void middleSmall();
    //左右慢速
    void leftOrRightSmall();




    WidgetSendWay(Enemy*ptr);
};

#endif // WIDGETSENDWAY_H
