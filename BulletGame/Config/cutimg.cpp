#include "cutimg.h"

CutImg::CutImg()
{
    v.push_back(":/res/etama.png");
    v.push_back(":/res/etama2.png");
    v.push_back(":/res/etama4.png");
    //v.push_back(":/res/etama3.png");//不是
}

QPixmap CutImg::getImg(int id, int f, double x, double y)
{
    QPixmap img;
    img.load(v[id]);
    int i=img.width()/f;
    return img.copy(int(x*i),int(y*i),i,i);

}

QPixmap CutImg::getImg(const QString &str)
{
    return QPixmap(str);
}
