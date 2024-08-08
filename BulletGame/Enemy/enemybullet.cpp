#include "enemybullet.h"
EnemyBullet::EnemyBullet()
{
    initEnemyBullet();
}
void EnemyBullet::initEnemyBullet()
{

    m_Step=int(GAME_BULLET_SPEED_2);
    m_SmallStep=m_Step;
    m_Acceleration=0.f;

    m_Rule=0;

    m_Free=true;
    m_Angle=90;//角度
    m_OtherNum=0;

    //位移
    m_X=-1000;
    m_Y=-1000;
    m_R=0;

    //判定
    m_Circular.m_R=0;
    m_Circular.m_X=-1000;
    m_Circular.m_Y=-1000;

    srand((unsigned)time(NULL));

}
void EnemyBullet::newEnemyBullet()
{
    if(m_Free)
        return;

//正常前行
    if(m_Rule==0){

        if(m_Step>=m_SmallStep){m_Step+=m_Acceleration;}
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

    }
//无位移
    else if(m_Rule==1)
    {
        ++m_OtherNum;
        if(m_OtherNum>=200)
        {
            m_OtherNum=0;
            m_Rule=0;
        }

    }
    else{}


    release();
}


void EnemyBullet::release()
{

    m_Circular.moveTo(m_X,m_Y);
    //判断释放
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
        m_R=0;
        this->m_X=-1000;
        this->m_Y=-1000;
    }
}

void EnemyBullet::setInformation(const BulletInformation &butInfor)
{
    this->m_image=butInfor.m_Img;
    this->m_Circular.m_R=butInfor.m_Img.width()*0.2;
    this->m_Rule=butInfor.m_Rule;
    this->m_Step=butInfor.m_Step;
    this->m_SmallStep=butInfor.m_SmallStep;
    this->m_Acceleration=butInfor.m_Acceleration;
    this->m_PrintId=butInfor.m_PrintId;
    this->m_Only_Angle=butInfor.m_OnlyAngle;
}
