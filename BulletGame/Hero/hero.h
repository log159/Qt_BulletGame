#ifndef HERO_H
#define HERO_H
#include <QPixmap>
#include <QString>
#include <ctime>
#include "Config/config.h"
#include "Others/mycircular.h"
#include "herobullet.h"
class Hero
{
public:

    QPixmap m_image;
    QPixmap m_image_;
    bool isKorShift=false;
    int m_PrintId=0;//显示形式  0 正常 1 不显示 2 半显示
    int m_Hp=3;
    bool m_FocusNum=false;
    int m_BombNum=3;
    int m_RedNum=0;
    long int m_BlueNum=0;
    bool m_CanSendBoom=true;

    //判定坐标
    int m_X;
    int m_Y;

    //打印坐标
    int m_PrintX;
    int m_PrintY;

    //图片偏移量
    int m_Xoffset;
    int m_Yoffset;

    //区域图大小
    int m_Width;
    int m_Height;

    //攻击靶目标
    int m_EX=-10;
    int m_EY=-10;

    //是否有伤害判定
    bool m_Harm=true;


    MyCircular m_Circular;//判定框

    int m_Step;//步长

    int m_KeySpeed;//ms移速刷新

    double m_AddDoubleStep;//移速缓冲

    double m_theAdd;//缓冲阈值 6.f or 12.f

    bool m_Up=false;
    bool m_Down=false;
    bool m_Left=false;
    bool m_Right=false;

    bool m_isUp=false;
    bool m_isDown=false;
    bool m_isLeft=false;
    bool m_isRight=false;

    int m_BulletSpeed;//子弹派出速度积累

    int m_Speed;//贴图刷新速度积累


    int m_OffsetNum;//偏移大小0~3

    HeroBullet m_HeroBulletArr[GAME_BULLET_NUM_HERO];//弹夹

    Hero();

    void initHero(const QString & str,const QString & str2,int r);//初始化数据

    void timeNewHero();//更新数据

    void keyNewHero();//更新数据

    void sendBullet();//派出子弹

    void newBullet();//更新子弹数据

    void sendBoom();

    void harmOver();//死亡

    void comingReturn();//返场

};

#endif // HERO_H
