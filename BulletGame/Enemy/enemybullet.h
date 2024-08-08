#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QPixmap>
#include <ctime>
#include "Config/config.h"
#include "Others/mycircular.h"
#include "Others/mathfunc.h"
#include "Others/bulletinformation.h"

class EnemyBullet
{
public:
    QPixmap m_image;

    int m_PrintId=0;//默认静态  0 静态 1动态-慢 2动态-快
    double m_Only_Angle=0.f;//方向型弹幕角度

    //弹幕运动规则
    int m_Rule=0;//默认零

    //真实坐标
    int m_X;
    int m_Y;
    double m_R;

    //索引坐标
    int m_BX;
    int m_BY;

    int m_OtherNum;


    MyCircular m_Circular;//判定框

    double m_Step;//步长
    double m_SmallStep;//最小步长
    double m_Acceleration;//加速度

    bool m_Free;//是否闲置

    double m_Angle;//角度

    void release();//判断释放

    void setInformation(const BulletInformation&butInfor);//设置信息

    void initEnemyBullet();//初始化数据

    void newEnemyBullet();//更新数据


    EnemyBullet();
};

#endif // ENEMYBULLET_H
