#ifndef HEROBULLET_H
#define HEROBULLET_H
#include <QPixmap>

#include "Config/cutimg.h"
#include "Config/config.h"
#include "Others/mycircular.h"
#include "Others/mathfunc.h"
class HeroBullet
{
public:
    QPixmap m_image;

    //判定坐标
    int m_X;
    int m_Y;

    int m_BX;
    int m_BY;
    double m_R=0;
    double m_Angle=270.f;

    MyCircular m_Circular;//判定框

    double m_Step;//步长

    bool m_Free;

    HeroBullet();

    void initHeroBullet(const QPixmap& img);//初始化数据

    void newHeroBullet();//更新数据

    void release();
};

#endif // HEROBULLET_H
