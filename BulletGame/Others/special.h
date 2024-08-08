#ifndef SPECIAL_H
#define SPECIAL_H
#include "Config/config.h"
#include <QPixmap>
#include <QString>
class Special
{
public:

    QPixmap m_image;

    int m_X;
    int m_Y;

    //打印坐标
    int m_PrintX;
    int m_PrintY;

    //图片偏移量
    int m_Xoffset;
    int m_Yoffset;

    //分割单位
    int m_Wunit;
    int m_Hunit;


    //区域图大小
    int m_Width;
    int m_Height;
    int m_OffsetNum;

    int m_Speed;//贴图刷新速度积累


    void initSpecial(QString str,int w,int h);

    void newSpecial(int x,int y);

    Special();
};

#endif // SPECIAL_H
