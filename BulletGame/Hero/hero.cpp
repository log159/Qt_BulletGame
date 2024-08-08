#include "hero.h"

Hero::Hero()
{
    this->initHero(QString(GAME_HERO_WAY),QString(GAME_HERO_WAY_),int(GAME_HERO_RECT));
}

void Hero::initHero(const QString& str,const QString&str2,int r)
{
    this->m_image.load(str);
    this->m_image_.load(str2);
    this->m_X=int(GAME_WIDTH)/2;
    this->m_Y=int(GAME_HEIGHT)-m_image.height()/4;

    //刷新数据初始化
    this->m_Speed=0;
    this->m_OffsetNum=0;

    this->m_Width=m_image.width()/4;
    this->m_Height=m_image.height()/4;

    this->m_Step=int(GAME_HERO_SPEED);

    this->m_Xoffset=m_Width*m_OffsetNum;
    this->m_Yoffset=m_Height*3;

    this->m_PrintX=(m_X-this->m_Width/2)-m_Xoffset;
    this->m_PrintY=(m_Y-this->m_Height/2)-m_Yoffset;

    this->m_BulletSpeed=0;


    this->m_Circular.m_R=r;
    this->m_Circular.m_X=m_X;
    this->m_Circular.m_Y=m_Y;

    this->m_KeySpeed=int(GAME_HERO_TIME);
    this->m_AddDoubleStep=0;
    this->m_theAdd=5.f;
    srand((unsigned)time(NULL));


}
void Hero::timeNewHero()//形态更新数据
{
        m_Speed++;
        if(m_Speed<int(GAME_HERO_ADDSPEED))
            return;
        m_Speed=0;
        this->m_OffsetNum++;
        if(m_OffsetNum>=4)
        {
            m_OffsetNum=0;
        }
        //修改偏移量
        this->m_Xoffset=m_Width*m_OffsetNum;

        this->m_PrintX=(m_X-this->m_Width/2)-m_Xoffset;
        this->m_PrintY=(m_Y-this->m_Height/2)-m_Yoffset;
}

void Hero::keyNewHero()//位移更新数据
{
    m_AddDoubleStep+=0.5f;
    if(m_AddDoubleStep<m_theAdd)
        return;
    m_AddDoubleStep=0.f;

    if(m_Up)
        this->m_Y-=m_Step;
    if(m_Left)
        this->m_X-=m_Step;
    if(m_Down)
        this->m_Y+=m_Step;
    if(m_Right)
        this->m_X+=m_Step;

    if(m_X<=this->m_Width/2)
        m_X=this->m_Width/2;
    if(m_Y<=this->m_Height/2)
        m_Y=this->m_Height/2;
    if(m_X>=int(GAME_WIDTH)-this->m_Width/2)
        m_X=int(GAME_WIDTH)-this->m_Width/2;
    if(m_Y>=int(GAME_HEIGHT)-this->m_Height/2)
        m_Y=int(GAME_HEIGHT)-this->m_Height/2;

    m_Circular.moveTo(m_X,m_Y+3);//更新判定框


    this->m_PrintX=(m_X-this->m_Width/2)-m_Xoffset;
    this->m_PrintY=(m_Y-this->m_Height/2)-m_Yoffset;


}

void Hero::sendBullet()
{
    if(m_PrintId==1){return;}


    int m_SendNum=m_RedNum/100;
    //int m_SendNum=4;
    if(m_RedNum>=400){m_RedNum=400;}

    if(m_SendNum==0)
    {
        m_BulletSpeed++;if(m_BulletSpeed<=int(GAME_HERO_ADDBULLETSPEED)){return;}m_BulletSpeed=0;
        for(int i=0;i<int(GAME_BULLET_NUM_HERO);i++)
        {
            if(this->m_HeroBulletArr[i].m_Free)
            {
                this->m_HeroBulletArr[i].m_BX=this->m_X;
                this->m_HeroBulletArr[i].m_BY=this->m_Y-40;
                this->m_HeroBulletArr[i].m_X=this->m_HeroBulletArr[i].m_BX;
                this->m_HeroBulletArr[i].m_Y=this->m_HeroBulletArr[i].m_BY;
                this->m_HeroBulletArr[i].m_Angle=270.f;
                this->m_HeroBulletArr[i].m_Free=false;
                break;

            }
        }
    }
    else if(m_SendNum==1){
        m_BulletSpeed++;if(m_BulletSpeed<=int(GAME_HERO_ADDBULLETSPEED)){return;}m_BulletSpeed=0;
        int f=0;
        for(int i=0;i<int(GAME_BULLET_NUM_HERO);i++)
        {
            if(this->m_HeroBulletArr[i].m_Free)
            {
                if(m_FocusNum==false)
                {
                    if(f==0)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-30;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;

                    }
                    else if(f==1)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+30;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                    }

                }
                else
                {
                    if(f==0)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-20;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;

                    }
                    else if(f==1)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+20;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                    }
                }
                this->m_HeroBulletArr[i].m_Angle=270.f;
                this->m_HeroBulletArr[i].m_X=this->m_HeroBulletArr[i].m_BX;
                this->m_HeroBulletArr[i].m_Y=this->m_HeroBulletArr[i].m_BY;
                this->m_HeroBulletArr[i].m_Free=false;
                ++f;
                if(f==2)
                    break;

            }
        }

    }
    else if(m_SendNum==2){
        m_BulletSpeed++;if(m_BulletSpeed<=int(GAME_HERO_ADDBULLETSPEED)){return;}m_BulletSpeed=0;
        int f=0;
        for(int i=0;i<int(GAME_BULLET_NUM_HERO);i++)
        {
            if(this->m_HeroBulletArr[i].m_Free)
            {
                if(m_FocusNum==false)
                {
                    if(f==0)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-50;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;

                    }
                    else if(f==1)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+50;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                    }
                    else if(f==2){
                        this->m_HeroBulletArr[i].m_BX=this->m_X;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-40;
                    }

                }
                else
                {
                    if(f==0)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-25;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;

                    }
                    else if(f==1)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+25;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                    }
                    else if(f==2){
                        this->m_HeroBulletArr[i].m_BX=this->m_X;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-30;
                    }
                }
                this->m_HeroBulletArr[i].m_Angle=270.f;
                this->m_HeroBulletArr[i].m_X=this->m_HeroBulletArr[i].m_BX;
                this->m_HeroBulletArr[i].m_Y=this->m_HeroBulletArr[i].m_BY;
                this->m_HeroBulletArr[i].m_Free=false;
                ++f;
                if(f==3)
                    break;

            }
        }

    }
    else if(m_SendNum==3)
    {
        m_BulletSpeed++;if(m_BulletSpeed<=int(GAME_HERO_ADDBULLETSPEED)){return;}m_BulletSpeed=0;
        static int add=0;++add;
        int fMax=3;
        int f=0;
        if(add>=3){add=0;fMax=5;}
        for(int i=0;i<int(GAME_BULLET_NUM_HERO);i++)
        {
            if(this->m_HeroBulletArr[i].m_Free)
            {
                if(m_FocusNum==false)
                {
                    if(f==0)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-50;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                        this->m_HeroBulletArr[i].m_Angle=270.f;

                    }
                    else if(f==1)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+50;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                        this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==2){
                        this->m_HeroBulletArr[i].m_BX=this->m_X;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-40;
                        this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==3)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-60;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y;
                        this->m_HeroBulletArr[i].m_Step=10.f;
                        if(m_EX>0&&m_EY>0)
                            this->m_HeroBulletArr[i].m_Angle=MathFunc().getAngle(this->m_HeroBulletArr[i].m_BX,this->m_HeroBulletArr[i].m_BY,m_EX,m_EY);
                        else
                            this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==4)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+60;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y;
                        this->m_HeroBulletArr[i].m_Step=10.f;
                        if(m_EX>0&&m_EY>0)
                            this->m_HeroBulletArr[i].m_Angle=MathFunc().getAngle(this->m_HeroBulletArr[i].m_BX,this->m_HeroBulletArr[i].m_BY,m_EX,m_EY);
                        else
                            this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                }
                else
                {
                    if(f==0)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-25;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                        this->m_HeroBulletArr[i].m_Angle=270.f;

                    }
                    else if(f==1)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+25;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                        this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==2){
                        this->m_HeroBulletArr[i].m_BX=this->m_X;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-30;
                        this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==3)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-40;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y;
                        this->m_HeroBulletArr[i].m_Step=10.f;
                        if(m_EX>0&&m_EY>0)
                            this->m_HeroBulletArr[i].m_Angle=MathFunc().getAngle(this->m_HeroBulletArr[i].m_BX,this->m_HeroBulletArr[i].m_BY,m_EX,m_EY);
                        else
                            this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==4)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+40;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y;
                        this->m_HeroBulletArr[i].m_Step=10.f;
                        if(m_EX>0&&m_EY>0)
                            this->m_HeroBulletArr[i].m_Angle=MathFunc().getAngle(this->m_HeroBulletArr[i].m_BX,this->m_HeroBulletArr[i].m_BY,m_EX,m_EY);
                        else
                            this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                }

                this->m_HeroBulletArr[i].m_X=this->m_HeroBulletArr[i].m_BX;
                this->m_HeroBulletArr[i].m_Y=this->m_HeroBulletArr[i].m_BY;
                this->m_HeroBulletArr[i].m_Free=false;
                ++f;
                if(f==fMax)
                    break;

            }
        }
    }
    else if(m_SendNum==4)
    {
        m_BulletSpeed++;if(m_BulletSpeed<=int(GAME_HERO_ADDBULLETSPEED)){return;}m_BulletSpeed=0;
        int f=0;
        for(int i=0;i<int(GAME_BULLET_NUM_HERO);i++)
        {
            if(this->m_HeroBulletArr[i].m_Free)
            {
                if(m_FocusNum==false)
                {
                    if(f==0)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-50;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                        this->m_HeroBulletArr[i].m_Angle=270.f;

                    }
                    else if(f==1)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+50;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                        this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==2){
                        this->m_HeroBulletArr[i].m_BX=this->m_X-20;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-40;
                        this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==3)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+20;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-40;
                        this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==4)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-60;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y;
                        this->m_HeroBulletArr[i].m_Step=10.f;
                        if(m_EX>0&&m_EY>0)
                            this->m_HeroBulletArr[i].m_Angle=MathFunc().getAngle(this->m_HeroBulletArr[i].m_BX,this->m_HeroBulletArr[i].m_BY,m_EX,m_EY);
                        else
                            this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==5)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+60;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y;
                        this->m_HeroBulletArr[i].m_Step=10.f;
                        if(m_EX>0&&m_EY>0)
                            this->m_HeroBulletArr[i].m_Angle=MathFunc().getAngle(this->m_HeroBulletArr[i].m_BX,this->m_HeroBulletArr[i].m_BY,m_EX,m_EY);
                        else
                            this->m_HeroBulletArr[i].m_Angle=270.f;
                    }

                }
                else
                {
                    if(f==0)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-25;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                        this->m_HeroBulletArr[i].m_Angle=270.f;

                    }
                    else if(f==1)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+25;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-20;
                        this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==2){
                        this->m_HeroBulletArr[i].m_BX=this->m_X-10;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-30;
                        this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==3)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+10;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y-30;
                        this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==4)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X-40;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y;
                        this->m_HeroBulletArr[i].m_Step=10.f;
                        if(m_EX>0&&m_EY>0)
                            this->m_HeroBulletArr[i].m_Angle=MathFunc().getAngle(this->m_HeroBulletArr[i].m_BX,this->m_HeroBulletArr[i].m_BY,m_EX,m_EY);
                        else
                            this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                    else if(f==5)
                    {
                        this->m_HeroBulletArr[i].m_BX=this->m_X+40;
                        this->m_HeroBulletArr[i].m_BY=this->m_Y;
                        this->m_HeroBulletArr[i].m_Step=10.f;
                        if(m_EX>0&&m_EY>0)
                            this->m_HeroBulletArr[i].m_Angle=MathFunc().getAngle(this->m_HeroBulletArr[i].m_BX,this->m_HeroBulletArr[i].m_BY,m_EX,m_EY);
                        else
                            this->m_HeroBulletArr[i].m_Angle=270.f;
                    }
                }
                this->m_HeroBulletArr[i].m_X=this->m_HeroBulletArr[i].m_BX;
                this->m_HeroBulletArr[i].m_Y=this->m_HeroBulletArr[i].m_BY;
                this->m_HeroBulletArr[i].m_Free=false;
                ++f;
                if(f==6)
                    break;

            }
        }
    }

}

void Hero::newBullet()
{
    for(int i=0;i<int(GAME_BULLET_NUM_HERO);i++)
    {
        if(this->m_HeroBulletArr[i].m_Free==false)
        {
            this->m_HeroBulletArr[i].newHeroBullet();

        }
    }


}

void Hero::sendBoom()
{
    int f=0;
    for(int i=0;i<int(GAME_BULLET_NUM_HERO);i++)
    {
        if(this->m_HeroBulletArr[i].m_Free)
        {
            this->m_HeroBulletArr[i].m_BX=this->m_X;
            this->m_HeroBulletArr[i].m_BY=this->m_Y;
            this->m_HeroBulletArr[i].m_X=this->m_HeroBulletArr[i].m_BX;
            this->m_HeroBulletArr[i].m_Y=this->m_HeroBulletArr[i].m_BY;
            this->m_HeroBulletArr[i].m_Free=false;

            this->m_HeroBulletArr[i].m_Angle=rand()%360;
            f+=5;
            if(f>=360)
                break;

        }
    }
    return;
}

void Hero::harmOver()
{
    this->m_Harm=false;
    this->m_PrintId=1;

}

void Hero::comingReturn()
{
    this->m_Harm=true;
    this->m_PrintId=0;
    this->m_CanSendBoom=true;
}
