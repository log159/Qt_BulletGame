#ifndef CUTIMG_H
#define CUTIMG_H

#include <QPixmap>
#include <QVector>
#include <QString>
class CutImg
{
public:
    CutImg();

    QPixmap getImg(int id,int f,double x,double y);

    QPixmap getImg(const QString&str);

    QVector<QString>v;

};

#endif // CUTIMG_H
