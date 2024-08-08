#ifndef ENEMY_H
#define ENEMY_H
#include <QPixmap>
#include <QString>
#include <QDebug>
#include <ctime>

#include "enemybullet.h"
#include "Config/config.h"
#include "Others/mycircular.h"
#include "Config/cutimg.h"
#include "Others/mathfunc.h"
#include "Others/bulletinformation.h"
#include "Others/enemyinformation.h"
#include "enemybulletway.h"
#include "Others/prop.h"

class Enemy
{
public:
    QPixmap m_image;

    CutImg imgConfig;//弹幕img素材

    EnemyBulletWay * enButSendWay;//弹幕派出法则

    int m_Hp;
    int m_initHp;
    //判定坐标
    int m_X;
    int m_Y;
    //索引坐标
    double m_R;
    double m_Angle;
    int m_BX;
    int m_BY;
    int m_HX;
    int m_HY;

    //打印坐标
    int m_PrintX;
    int m_PrintY;
    //图片偏移量
    int m_Xoffset;
    int m_Yoffset;

    //区域图大小
    int m_Width;
    int m_Height;
    int m_OffsetNum;//偏移大小0~3

    MyCircular m_Circular;//判定框
    bool m_Free;//是否闲置
    int m_Rule;//位移更新规则
    double m_Step;//步长
    double m_SmallStep;//最短步长
    double m_Acceleration;//加速度

    int m_SendRule;//派出弹幕规则
    int m_EndSendNum=0;//消亡派出
    int m_OtherNum=0;//特殊规则

    int addTimePrint=0;//打印延时
    int addTime=0;//派出弹幕延时

    EnemyBullet *m_EnemyBulletArr;//弹夹指针
    Prop* m_Prop;//掉落物品指针

    void setInformation(const EnemyInformation&ememyInfor);//设置信息

    void initEnemy();//初始化
    void setEnemy(int a,const QPixmap &img,int hp);//设置信息
    void newEnemy();//数据更新
    void sendBullet();//派出弹幕
    void newBullet();//更新弹幕
    void sendProp();//派出掉落
    void endSendBullet();//亡语效果
    void mathFunc();//数学函数
    void release();//释放Free
    Enemy();
    ~Enemy();
};

#endif // ENEMY_H
