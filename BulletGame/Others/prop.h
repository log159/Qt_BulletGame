#ifndef PROP_H
#define PROP_H
#include <QPixmap>

#include "Config/cutimg.h"
#include "Config/config.h"
#include "Others/mycircular.h"
#include "Others/mathfunc.h"

class Prop
{
public:
    QPixmap m_image;

    int id=-1;//-1没有 0 红 1大红 2蓝

    //判定坐标
    int m_X;
    int m_Y;

    int m_BX;
    int m_BY;

    double m_R;
    double m_Angle;


    MyCircular m_Circular;//判定框

    double m_Step;//步长

    bool m_Free;//是否闲置

    Prop();

    void initProp();//初始化数据

    void newProp();//更新数据

    void release();
};

#endif // PROP_H
