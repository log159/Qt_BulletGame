#ifndef BOOM_H
#define BOOM_H
#include "Config/config.h"
#include <QPixmap>
#include <QVector>
#include <QString>
class Boom
{
public:
    QVector<QPixmap>m_Vector;

    int m_X;
    int m_Y;

    int m_TheNum;

    int m_Free;

    int m_Space;

    //图片偏移量
    int m_Xoffset;
    int m_Yoffset;

    void initBoom();

    void newBoom();

    Boom();
};

#endif // BOOM_H

