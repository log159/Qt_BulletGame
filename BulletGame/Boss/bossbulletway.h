#ifndef BOSSBULLETWAY_H
#define BOSSBULLETWAY_H

#include <QDebug>
#include "Boss/bossbullet.h"
#include "Others/mathfunc.h"
#include "Config/cutimg.h"
#include "Config/config.h"
class BossBulletWay
{
public:
    /*---------------------------------------*/
    CutImg imgConfig;//弹幕img资源

    /*------------特殊调节类-----------------*/
private:
    int ran=0;//随机值

    int f=0;//等分参数

    int dangerCheck=6;//危险系数（越低越危险）

    int checkNewTime=0;//阻滞参数（刷新阻滞）

    int add=-1;//累加系数

    /*--------------------------------------------------*/
public:
    //Boss数据
    BossBullet*boBut;
    int m_BX_;int m_BY_;

    //Hero数据
    int m_HX_;int m_HY_;

    //全局默认参数变化 每次刷新开始时
    void newNeedFirst(int x,int y);

    //默认初始化弹幕方法
    void initButDefault(int i,int bx,int by,double v=double(GAME_BULLET_SPEED_3));

    //数量限制（根据newNum 限制）
    bool numMaxReturn(int id,int m);

    /*-----------------------弹幕方法----------------------*/


    //风车方法
    void windmill(int id,int x=-1,int y=-1);
    //逆风车方法
    void windmillCounter(int id,int x=-1,int y=-1);
    //摆动风车方法
    void windmillMove(int id);
    //散射方法
    void scattering(int id);
    //扩散方法
    void spreadStar(int id,int p=24,int r=0);
    //sin方法
    void sinStar();
    //other方法
    void lorenz(int id);
    //流星雨方法
    void rainStar(int i,int id=0);
    //聚散方法
    void scatterFind();
    //聚散星星方法
    void scatterFindStar();
    //波粒方法
    void waveParticle(int id);
    //反弹方法
    void rebound(int id);


    /*-------------------------------------------------*/

    //无释放方式弹幕全部扩散回收
    void setNumMoveAll(double v);

    //指定弹幕派出
    void setSendImg(BossBullet*but,int id,int f,double x,double y);

    BossBulletWay();
};

#endif // BOSSBULLETWAY_H
