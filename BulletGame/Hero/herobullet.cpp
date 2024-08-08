#include "herobullet.h"

HeroBullet::HeroBullet()
{
    this->initHeroBullet(CutImg().getImg(2,8,0,3));
}

void HeroBullet::initHeroBullet(const QPixmap& img)
{
    this->m_image=img;

    this->m_Step=double(GAME_BULLET_SPEED_1);

    this->m_Free=true;

    this->m_Circular.m_R=m_image.width()*0.3;
}

void HeroBullet::newHeroBullet()
{

    if(this->m_Free)
        return;

    m_R+=m_Step;
    double temp=(double(m_Angle)/double(180))*PI;
    m_X=int(double(m_R)/sqrt(1.f+tan(temp)*tan(temp)));
    m_Y=int(double(m_R)/sqrt(1.f+tan(temp)*tan(temp))*tan(temp));
    if(m_X<0){m_X=(-m_X);}
    if(m_Y<0){m_Y=(-m_Y);}
    if(0<=m_Angle&&m_Angle<90){}
    else if(90<=m_Angle&&m_Angle<180){m_X=0-m_X;}
    else if(180<=m_Angle&&m_Angle<270){m_X=0-m_X;m_Y=0-m_Y;}
    else if(270<=m_Angle&&m_Angle<360){m_Y=0-m_Y;}
    m_X+=m_BX;
    m_Y+=m_BY;

    release();

}

void HeroBullet::release()
{
    this->m_Circular.moveTo(m_X,m_Y);

    if(m_Y>int(GAME_HEIGHT)+m_image.height())
        m_Free=true;
    if(m_Y<-m_image.height())
        m_Free=true;
    if(m_X<-m_image.width())
        m_Free=true;
    if(m_X>int(GAME_WIDTH)+m_image.width())
        m_Free=true;
    if(m_Free)
    {
        m_X=-1000;
        m_Y=-1000;
        m_R=0;
        m_Angle=270;
        m_Step=double(GAME_BULLET_SPEED_1);
    }
}
