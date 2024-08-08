#ifndef ENEMYBULLETWAY_H
#define ENEMYBULLETWAY_H

#include <QDebug>

#include "Others/mathfunc.h"
#include "Config/cutimg.h"
#include "Config/config.h"
#include "enemybullet.h"
#include "Others/enemyinformation.h"

class EnemyBulletWay
{
public:

    EnemyBullet*enBut;

    BulletInformation m_Information;//弹幕派出信息

    void setXY(int x,int y,int hx,int hy);

    int otherNum=100;//特殊调节//每次回收从100开始回归
private:
    //Enemy 坐标
    int m_X;
    int m_Y;
    //Hero 坐标
    int m_HX;
    int m_HY;

    int addTime=0;
    bool addSmallSendTime(int i);//延时

public:
    //----------------正常派出------------

    //变速直线
    bool changeSpeed();
    //狙击扇形
    bool snipeRfan();
    //狙击直线
    bool sinpeSpeed();
    //回旋直线
    bool circle();

    //----------------消亡派出-------------

    //四角直线
    void fourQuarter();

    //四角直线Plus
    void fourQuarterPlus();

    EnemyBulletWay()=default;
};

#endif // ENEMYBULLETWAY_H
