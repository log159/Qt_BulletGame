#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QPixmap>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    QPixmap image;

    MyLabel(const QString&str,int s=15);

    //设为选中样式
     void setPressStyle();

     //设为释放样式
     void setReleaseStyle();

signals:
    void touchOff();

public slots:
};

#endif // MYLABEL_H
