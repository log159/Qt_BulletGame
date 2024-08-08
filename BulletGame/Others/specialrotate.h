#ifndef SPECIALROTATE_H
#define SPECIALROTATE_H
#include "Config/config.h"
#include <QPixmap>
#include <QString>

class SpecialRotate
{
public:
    QPixmap m_image;

    int m_Width;
    int m_Height;

    void initSpecialRotate(QString str);

    SpecialRotate();
};

#endif // SPECIALROTATE_H
