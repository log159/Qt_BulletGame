#ifndef MYIMGLABEL_H
#define MYIMGLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QSize>

class MyImgLabel : public QLabel
{
    Q_OBJECT
public:
    QPixmap m_img1;
    QPixmap m_img2;
    explicit MyImgLabel(const QPixmap&p1,const QPixmap&p2);

    void setImg1();
    void setImg2();

signals:

public slots:
};

#endif // MYIMGLABEL_H
