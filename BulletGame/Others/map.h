#ifndef MAP_H
#define MAP_H
#include "Config/config.h"
#include <QPixmap>
#include <QString>
class Map
{
public:
    QPixmap m_image1;

    QPixmap m_image2;

    int m_Y1;
    int m_Y2;

    int m_Speed;//速度

    Map(const QString&str);
    void change(const QString&str);//初始化数据

    void newMap();//更新数据
};

#endif // MAP_H
