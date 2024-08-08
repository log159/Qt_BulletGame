#include "bossbullet.h"


void BossBullet::initBossBullet()
{

    m_Step=double(GAME_BULLET_SPEED_3);

    m_Free=true;

    m_Angle=0;//角度

    m_ZoneId=1;//区域编号

    m_X=-100;
    m_Y=-100;
    m_R=0;

    m_Circular.m_R=0;
    m_Circular.m_X=-100;
    m_Circular.m_Y=-100;



    m_Trace=false;
    m_AddNum=0;

    //srand((unsigned)time(NULL));
}
void BossBullet::initButDefault(int bx,int by)
{
    this->m_BX=bx;
    this->m_BY=by;
    this->m_X=bx;
    this->m_Y=by;
    this->m_R=0;
    this->release();

}

void BossBullet::setBossBullet(const QPixmap& img)
{
    m_image=img;
    m_Width=m_image.width();
    m_Height=m_image.height();
    m_Circular.m_R=(img.height()*0.2);

}
void BossBullet::newBossBullet()
{
    if(m_Free)
        return;

    if(m_Angle>=360){m_Angle-=360;}
    if(m_Angle<0){m_Angle+=360;}

    switch(m_NewNum)
    {
    //一个方向直到释放型
    case 0:
        if(setAddMax(3)==false){return;}moveRule();
        break;
    case 1:
    //sin轨迹型
        if(setAddMax(5)==false){return;}moveRule2();
        break;
    //other型
    case 2:
        if(setAddMax(2)==false){return;}moveRule3();
        break;
    //一个方向直到释放型-2
    case 3:
        if(setAddMax(2)==false){return;}moveRule();
        break;
    //一个方向直到释放型-3 启用跟踪
    case 4:
        if(setAddMax(2)==false){return;}if(tracksTime(100,5)){return;}moveRule();
        break;
    //一个方向直到释放型-4
    case 5:
        moveRule();
        break;
    //不移动 启用跟踪
    case 6:
        if(tracksTime(600,3)){return;}
        break;
    //不移动
    case 7:
        break;
    //一个方向直到释放型-2 上，左，右 反弹
    case 8:
        if(setAddMax(3)==false){return;}moveRule4();
        break;
    default:break;
    }

    release();

}



void BossBullet::release()
{
    m_Circular.moveTo(m_X,m_Y);

    //判断释放
    if(m_ReleaseNum==0)//超出地图释放
    {
        if((m_Y>int(GAME_HEIGHT)+3*m_Height)||(m_Y<-3*m_Height)||(m_X<-3*m_Width)||(m_X>int(GAME_WIDTH)+3*m_Width))
            m_Free=true;
    }
    else if(m_ReleaseNum==1)//超出地图以下释放
    {
        if(m_Y>int(GAME_HEIGHT)+3*m_Height)
            m_Free=true;
    }
    else if(m_ReleaseNum==2)//不释放
    {

    }
    else if(m_ReleaseNum==3)
    {
        m_Free=true;//无理由释放
    }

    //释放后
    if(m_Free)
    {
        m_R=0;
        this->m_X=-1000;
        this->m_Y=-1000;
    }
}

bool BossBullet::setAddMax(int i)
{
    ++m_AddNum;
    if(m_AddNum<i){return false;}
    m_AddNum=0;
    return true;
}

bool BossBullet::tracksTime(int i,int n)
{
    if(m_OtherNum>=i)
    {
        this->initButDefault(this->m_X,this->m_Y);
        this->m_NewNum=n;
        this->m_ReleaseNum=0;
        this->m_Angle=MathFunc().getAngle(this->m_X,this->m_Y,this->m_HX,this->m_HY);
        this->m_Only_Angle=this->m_Angle+90;
        this->m_PrintId=1;

        return true;
    }
    ++m_OtherNum;
    return false;
}


void BossBullet::moveRule()
{
    m_R+=m_Step;
    double temp=(double(m_Angle)/double(180))*PI;//ci ta
    m_X=int(m_R/sqrt(1.f+tan(temp)*tan(temp)));
    m_Y=int(m_R/sqrt(1.f+tan(temp)*tan(temp))*tan(temp));
    if(m_X<0){m_X=(-m_X);}
    if(m_Y<0){m_Y=(-m_Y);}
    if(0<=m_Angle&&m_Angle<90){}
    else if(90<=m_Angle&&m_Angle<180){m_X=0-m_X;}
    else if(180<=m_Angle&&m_Angle<270){m_X=0-m_X;m_Y=0-m_Y;}
    else if(270<=m_Angle&&m_Angle<360){m_Y=0-m_Y;}
    m_X+=m_BX;m_Y+=m_BY;
}

void BossBullet::moveRule2()
{
    if(this->m_OtherNum==0){m_Y++;m_X=30*sin(0.02f*double(m_Y))+m_BX;}
    else if(this->m_OtherNum==1){m_Y++;m_X=100*sin(0.02f*double(m_Y))+m_BX;}
    else if(this->m_OtherNum==2){m_Y++;m_X=5*sin(0.02f*double(m_Y))+m_BX;}
    else if(this->m_OtherNum==3){m_Y++;m_X=50*sin(0.02f*double(m_Y))+m_BX;}
}

void BossBullet::moveRule3()
{
    double temp=(double(m_Angle+0.2f)/double(180))*PI;//ci ta
    m_X=int(double(m_R)/sqrt(1.f+tan(temp)*tan(temp)));
    m_Y=int(double(m_R)/sqrt(1.f+tan(temp)*tan(temp))*tan(temp));
    if(m_X<0){m_X=(-m_X);}
    if(m_Y<0){m_Y=(-m_Y);}
    if(0<=m_Angle&&m_Angle<90){}
    else if(90<=m_Angle&&m_Angle<180){m_X=0-m_X;}
    else if(180<=m_Angle&&m_Angle<270){m_X=0-m_X;m_Y=0-m_Y;}
    else if(270<=m_Angle&&m_Angle<360){m_Y=0-m_Y;}
    //m_BY=m_BX;//???????
    m_X+=m_BX;m_Y+=m_BY;
    m_Angle+=0.2;
}

void BossBullet::moveRule4()
{

    if(this->m_Y<0)
    {
        m_Y=0;
        m_Angle=360-m_Angle;
        initButDefault(this->m_X,this->m_Y);
        this->m_NewNum=0;

    }
    else if(this->m_X<0)
    {
        m_X=0;
        if(m_Angle<=180)
            m_Angle=180-m_Angle;
        else
            m_Angle=180*3-m_Angle;
        initButDefault(this->m_X,this->m_Y);
        this->m_NewNum=0;
    }
    else if(this->m_X>int(GAME_WIDTH))
    {
        m_X=int(GAME_WIDTH);
        if(m_Angle<=180)
            m_Angle=180-m_Angle;
        else
            m_Angle=180*3-m_Angle;
        initButDefault(this->m_X,this->m_Y);
        this->m_NewNum=0;
    }
    moveRule();
}
