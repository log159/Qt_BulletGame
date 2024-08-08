#include "enemybulletway.h"
bool EnemyBulletWay::addSmallSendTime(int i)
{
    //缓冲
    ++addTime;
    if(addTime<i){return false;}
    addTime=0;
    return true;

}

void EnemyBulletWay::setXY(int x, int y, int hx, int hy)
{
    this->m_X=x;
    this->m_Y=y;
    this->m_HX=hx;
    this->m_HY=hy;
}

bool EnemyBulletWay::changeSpeed()
{
    if(addSmallSendTime(int(GAME_ENEMY_ADDBULLETSPEED)*0.5)==false){return false;}
    int f=0;
    for(int i=0;i<int(GAME_BULLET_NUM_3);i++)
    {
        if((enBut+i)->m_Free)
        {
            m_Information.m_Step*=1.1;
            (enBut+i)->setInformation(m_Information);

            (enBut+i)->m_BX=m_X;
            (enBut+i)->m_BY=m_Y;
            (enBut+i)->m_Angle=90.f;
            (enBut+i)->m_Free=false;
            ++f;
            if(f>=7)
            {
                m_Information.initInformation();
                break;
            }
        }
    }
    return true;
}

bool EnemyBulletWay::snipeRfan()
{
    if(addSmallSendTime(int(GAME_ENEMY_ADDBULLETSPEED)*0.3)==false){return false;}
    int f=0;
    double tempAngle=MathFunc().getAngle(this->m_X,this->m_Y,m_HX,m_HY);
    for(int i=0;i<int(GAME_BULLET_NUM_3);i++)
    {
        if((enBut+i)->m_Free)
        {
            (enBut+i)->setInformation(m_Information);
            (enBut+i)->m_BX=m_X;
            (enBut+i)->m_BY=m_Y;
            (enBut+i)->m_Angle=tempAngle-40.f+double(f*20);
            (enBut+i)->m_Free=false;
            ++f;
            if(f>=5){
                m_Information.initInformation();
                break;
            }
        }
    }
    return true;
}

bool EnemyBulletWay::sinpeSpeed()
{
    if(addSmallSendTime(int(GAME_ENEMY_ADDBULLETSPEED)*0.5)==false){return false;}
    int f=0;
    double tempAngle=MathFunc().getAngle(this->m_X,this->m_Y,m_HX,m_HY);
    for(int i=0;i<int(GAME_BULLET_NUM_3);++i)
    {
        if((enBut+i)->m_Free)
        {
            m_Information.m_Step*=1.1;
            (enBut+i)->setInformation(m_Information);

            (enBut+i)->m_BX=m_X;
            (enBut+i)->m_BY=m_Y;
            (enBut+i)->m_Angle=tempAngle;
            (enBut+i)->m_Free=false;
            ++f;
            if(f>=7){
                m_Information.initInformation();
                break;
            }
        }
    }
    return true;
}

bool EnemyBulletWay::circle()
{
    //全局阻滞
    if(addSmallSendTime(int(GAME_ENEMY_ADDBULLETSPEED)*0.02)==false){return false;}

    static double t_Angle=0.f;
    t_Angle+=11.0f;
    if(t_Angle>=360.f){t_Angle-=360.f;}
    int f=0;

    otherNum-=2;

    int tempX=otherNum*0.7*sin(t_Angle/180*PI);
    int tempY=otherNum*0.7*cos(t_Angle/180*PI);


    for(int i=0;i<int(GAME_BULLET_NUM_3);++i)
    {
        if((enBut+i)->m_Free)
        {
            (enBut+i)->setInformation(m_Information);
            (enBut+i)->m_Free=false;

            if(f==0){
                (enBut+i)->m_X=m_X+tempX;
                (enBut+i)->m_Y=m_Y+tempY;
            }
            else if(f==1){
                (enBut+i)->m_X=m_X+tempY;
                (enBut+i)->m_Y=m_Y-tempX;
            }
            else if(f==2){
                (enBut+i)->m_X=m_X-tempX;
                (enBut+i)->m_Y=m_Y-tempY;
            }
            else if(f==3){
                (enBut+i)->m_X=m_X-tempY;
                (enBut+i)->m_Y=m_Y+tempX;
            }
            (enBut+i)->m_BX=m_X;
            (enBut+i)->m_BY=m_Y;

            (enBut+i)->m_R=MathFunc().getR(m_X,m_Y,(enBut+i)->m_X,(enBut+i)->m_Y);
            (enBut+i)->m_Angle=MathFunc().getAngle(m_X,m_Y,(enBut+i)->m_X,(enBut+i)->m_Y);
            (enBut+i)->m_OtherNum=0;
            ++f;
            if(f==4)
            {
                m_Information.initInformation();
                break;
            }
        }
    }
    return true;
}

void EnemyBulletWay::fourQuarter()
{
    int f=0;
    for(int i=0;i<int(GAME_BULLET_NUM_3);++i)
    {
        if((enBut+i)->m_Free)
        {
            m_Information.m_Step=1;

            (enBut+i)->setInformation(m_Information);

            (enBut+i)->m_BX=m_X;
            (enBut+i)->m_BY=m_Y;
            if(f%4==0)
                (enBut+i)->m_Angle=45;
            else if(f%4==1)
                (enBut+i)->m_Angle=45+90;
            else if(f%4==2)
                (enBut+i)->m_Angle=45+180;
            else if(f%4==3)
                (enBut+i)->m_Angle=45+270;

            (enBut+i)->m_Free=false;
            ++f;
            if(f>=4){
                m_Information.initInformation();
                break;
            }
        }
    }
}

void EnemyBulletWay::fourQuarterPlus()
{
    int f=0;
    for(int i=0;i<int(GAME_BULLET_NUM_3);++i)
    {
        if((enBut+i)->m_Free)
        {
            if(f<4)
                m_Information.m_Step=1;
            else if(f<8)
                m_Information.m_Step=2;
            else if(f<12)
                m_Information.m_Step=3;

            (enBut+i)->setInformation(m_Information);

            (enBut+i)->m_BX=m_X;
            (enBut+i)->m_BY=m_Y;
            if(f%4==0)
                (enBut+i)->m_Angle=45;
            else if(f%4==1)
                (enBut+i)->m_Angle=45+90;
            else if(f%4==2)
                (enBut+i)->m_Angle=45+180;
            else if(f%4==3)
                (enBut+i)->m_Angle=45+270;

            (enBut+i)->m_Free=false;
            ++f;
            if(f>=12){
                m_Information.initInformation();
                break;
            }
        }
    }
}
