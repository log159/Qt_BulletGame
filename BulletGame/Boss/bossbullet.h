#ifndef BOSSBULLET_H
#define BOSSBULLET_H
#include "Others/mycircular.h"
#include "Config/config.h"
#include <QPixmap>
#include <QString>
#include <cmath>
#include <math.h>
#include <QDebug>
#include <Others/mathfunc.h>
//#include <ctime>

double sqrt(double n);
class BossBullet
{
public:


    int m_PrintId=1;//1 方向型 2 旋转

    double m_Only_Angle=0.f;//方向型弹幕角度

    QPixmap m_image;

    MyCircular m_Circular;//判定框

    //真实坐标
    int m_X;int m_Y;double m_R;

    //索引坐标
    int m_BX;int m_BY;
    int m_HX;int m_HY;

    int m_Width;
    int m_Height;

    double m_Step;//步长

    bool m_Free;//是否闲置


    double m_Angle;//角度

    int m_ZoneId;//区域编号

    bool m_Trace;//启用跟踪

    int m_ReleaseNum;//释放编号

    int m_NewNum;//刷新编号

    int m_AddNum;//累加参数

    int m_OtherNum;//特殊调节编号

    //---------------------------------

    void initBossBullet();//初始化

    void initButDefault(int bx,int by);//更新规则改变时的必要初始化

    void setBossBullet(const QPixmap &img);

    void newBossBullet();//弹幕更新

    void release();//判断释放

    bool setAddMax(int i);

    bool tracksTime(int i,int n=0);

    void moveRule();

    void moveRule2();

    void moveRule3();

    void moveRule4();

    BossBullet()=default;
};

#endif // BOSSBULLET_H
