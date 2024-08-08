#ifndef BOSS_H
#define BOSS_H
#include <QPixmap>
#include <QString>
#include <ctime>
#include <QLabel>
#include <QTimer>
#include <QVector>

#include "Config/config.h"
#include "Others/specialrotate.h"
#include "Others/mycircular.h"
#include "Others/mycoordinate.h"
#include "Others/myrect.h"
#include "bossbullet.h"
#include "bossbulletway.h"

class Boss
{
public:
    QPixmap m_image;//boss图

    MyCircular m_Circular;//判定框

    MyRect m_Rect;//Hp框
    MyRect m_RectHp;//Hp显示
    double m_Hphundred;//Hp百分比


    //阶段性Hp容器
    QVector<int>v_Hp;
    int m_It;//当前位置
    int m_Hp;//当前Hp

    //背景效果
    SpecialRotate m_SpecialRotate;


    //判定坐标
    int m_X;int m_Y;

    //打印坐标
    int m_PrintX;int m_PrintY;

    //图片偏移量
    int m_Xoffset;int m_Yoffset;

    //区域图大小
    int m_Width;int m_Height;

    int m_Step;//步长（速度）

    double m_Acceleration;//加速度

    bool m_Free;//是否闲置

    bool m_Over;//是否死亡

    bool m_Harm;//是否接受伤害判定

    bool m_Move;//到达靶目标后是否移动

    int m_BulletNum;//当前攻击形式 0 1 2 3 4 5.....

    int m_Speed;//贴图刷新速度积累

    int m_OffsetNum;//偏移大小0~3

    int dangerCheck=2;//危险系数（越低越危险）

    //位移靶目标
    MyCoordinate m_CoMoveLocation;

    //攻击靶目标
    MyCoordinate m_CoAttackLocation;

    //弹夹指针
    BossBullet *m_BossBulletArr;

    //弹幕更新法则
    BossBulletWay m_BobuWay;//

    virtual void sendBullet()=0;//派出弹幕

    void nextBullet();//根据Hp确定攻击模式

    void initBoss(const QString& str,int r,int x=4);//初始化

    void initHpVector(int n,int hp);//初始化分段Hp

    void newBoss();//更新boss数据


    void getPoint();//获取并记录各种坐标数据

    void newBullet();//更新弹幕

    void goMove();//到达目的地后去一个新位置

    void getHeroLocation(int x,int y);//更新攻击靶目标

    void stopMove();//停止移动

    void continueMove();//继续移动

    void endGoto();//收尾位移

    Boss()=default;

    virtual~Boss();
};

#endif // BOSS_H
