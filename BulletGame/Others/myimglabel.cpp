#include "myimglabel.h"


MyImgLabel::MyImgLabel(const QPixmap&p1,const QPixmap&p2)
{
    QSize picSize(20,20);
    this->m_img1=p1;
    this->m_img2=p2;
    m_img1=m_img1.scaled(picSize);
    m_img2=m_img2.scaled(picSize);

}

void MyImgLabel::setImg1()
{
    this->setFixedSize(m_img1.width(),m_img1.height());
    this->setPixmap(m_img1);

}

void MyImgLabel::setImg2()
{
//    this->setFixedSize(m_img2.width(),m_img2.height());
//    this->setPixmap(m_img2);
    this->clear();
}
