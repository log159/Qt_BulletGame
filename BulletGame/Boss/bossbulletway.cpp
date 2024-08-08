#include "bossbulletway.h"

BossBulletWay::BossBulletWay()
{
    //时间函数
    srand((unsigned)time(NULL));
}

void BossBulletWay::newNeedFirst(int x, int y)
{
    m_BX_=x;
    m_BY_=y;

}
void BossBulletWay::initButDefault(int i,int bx,int by,double v)
{

    (boBut+i)->m_BX=bx;
    (boBut+i)->m_BY=by;
    (boBut+i)->m_X=bx;
    (boBut+i)->m_Y=by;
    (boBut+i)->m_R=0;
    (boBut+i)->m_Free=false;
    (boBut+i)->m_Step=v;
    (boBut+i)->m_OtherNum=0;
}

bool BossBulletWay::numMaxReturn(int id, int m)
{
    //数量限制
    int t_num=0;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
        if((boBut+i)->m_NewNum==id){++t_num;}
    if(t_num>=m){return false;}
    else{return true;}
}
void BossBulletWay::windmill(int id,int x,int y)
{
    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck){return;}checkSendTime=0;
    static int jio=0;jio+=7;if(jio>=360){jio-=360;}if(jio<0){jio+=360;}
    this->f=0;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            if(x<0||y<0){initButDefault(i,m_BX_,m_BY_,1.5);}
            else{initButDefault(i,x,y);}
            (boBut+i)->m_Angle=jio+(360/id*f);

            (boBut+i)->m_ReleaseNum=0;
            (boBut+i)->m_NewNum=0;

            this->setSendImg(boBut+i,2,8,4,3);//-------------
            (boBut+i)->m_Only_Angle=(boBut+i)->m_Angle+90;//-------
            (boBut+i)->m_PrintId=1;//------
            f++;
            if(f==id)
                break;
        }
    }

}

void BossBulletWay::windmillCounter(int id, int x, int y)
{
    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck){return;}checkSendTime=0;
    static int jio=0;jio-=7;if(jio>=360){jio-=360;}if(jio<0){jio+=360;}
    this->f=0;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            if(x<0||y<0){initButDefault(i,m_BX_,m_BY_,1.5);}
            else{initButDefault(i,x,y);}

            (boBut+i)->m_Angle=jio+(360/id*f);
            (boBut+i)->m_ReleaseNum=0;
            (boBut+i)->m_NewNum=0;

            this->setSendImg(boBut+i,2,8,4,3);//-------------
            (boBut+i)->m_Only_Angle=(boBut+i)->m_Angle+90;//-------
            (boBut+i)->m_PrintId=1;//------

            f++;
            if(f==id)
                break;
        }
    }
}

void BossBulletWay::windmillMove(int id)
{
    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck){return;}checkSendTime=0;
    static int jio=0;if(jio>=360){jio-=360;}if(jio<0){jio+=360;}
    ++add;
    if(add>=78){add=0;}
    if(0<=add&&add<39){jio+=7;}
    else{jio-=7;}
    this->f=0;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            initButDefault(i,m_BX_,m_BY_,1.5);
            (boBut+i)->m_Angle=double(jio+360/id*f);
            (boBut+i)->m_ReleaseNum=0;
            (boBut+i)->m_NewNum=0;
            this->setSendImg(boBut+i,2,8,4,3);//-------------
            (boBut+i)->m_Only_Angle=(boBut+i)->m_Angle+90;//-------
            (boBut+i)->m_PrintId=1;//------
            ++f;
            if(f==id)
                break;
        }
    }
}

void BossBulletWay::scattering(int id)
{
    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck){return;}checkSendTime=0;
    static int jio=0;jio+=7;if(jio>=360){jio-=360;}if(jio<0){jio+=360;}
    this->f=0;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            initButDefault(i,m_BX_,m_BY_);
            ran=rand()%360;
            (boBut+i)->m_Angle=ran;
            (boBut+i)->m_ReleaseNum=0;
            (boBut+i)->m_NewNum=0;
            this->setSendImg(boBut+i,2,8,4,0);//-------------
            //(boBut+i)->m_Only_Angle=(boBut+i)->m_Angle+90;//-------
            (boBut+i)->m_PrintId=2;//------
            ++f;
            if(f==id)
                break;
        }
    }
}

void BossBulletWay::spreadStar(int id,int p,int r)//第一个参数影响数量 第二个参数影响速度 第三个参数影响位置(默认启用跟踪)
{
    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck*p){return;}checkSendTime=0;
    this->f=0;
    int checkNum=0;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
            checkNum++;
    }
    if(checkNum<id+10)
        return;
    ran=rand()%150+15;
    int t_r1=rand()%GAME_WIDTH*0.8+GAME_WIDTH*0.1;
    int t_r2=rand()%GAME_HEIGHT*0.3+GAME_HEIGHT*0.1;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            (boBut+i)->m_Angle=f*(360/id)+ran;
            if(r==0){
                initButDefault(i,m_BX_,m_BY_,1.5);
                (boBut+i)->m_NewNum=0;
                this->setSendImg(boBut+i,2,8,4,0);//-------------
                (boBut+i)->m_PrintId=2;//------
            }
            else
            {
                initButDefault(i,t_r1,t_r2);
                (boBut+i)->m_NewNum=4;

                this->setSendImg(boBut+i,2,8,4,3);//-------------
                (boBut+i)->m_Only_Angle=(boBut+i)->m_Angle+90;//-------
                (boBut+i)->m_PrintId=1;//------
            }
            (boBut+i)->m_ReleaseNum=0;
            f++;
            if(f==id)
                break;
        }

    }
}

void BossBulletWay::sinStar()
{

    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck*4){return;}checkSendTime=0;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        int ranNum=rand()%4;
        int ranX=rand()%int(GAME_WIDTH);
        
        if((boBut+i)->m_Free)
        {
            initButDefault(i,ranX,0);
            (boBut+i)->m_OtherNum=ranNum;
            (boBut+i)->m_ReleaseNum=1;
            (boBut+i)->m_NewNum=1;
            this->setSendImg(boBut+i,2,8,4,0);//-------------
            //(boBut+i)->m_Only_Angle=(boBut+i)->m_Angle+90;//-------
            (boBut+i)->m_PrintId=2;//------
            break;
        }
    }
}

void BossBulletWay::lorenz(int id)//----------------------------------------------------
{
    if(numMaxReturn(2,120)==false){setNumMoveAll(1.5f);}
    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck*0.3){return;}checkSendTime=0;
    add+=id;
    if(add>=360)
        add-=360;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            initButDefault(i,m_BX_,m_BY_);
            (boBut+i)->m_R=120;
            (boBut+i)->m_Angle=-(90-add)+360;
            int heartCita=90+add;
            if(heartCita>=360){heartCita-=360;}
            double temp=(double(heartCita)/double(180))*PI;//ci ta
            int m_MyX=int(double((boBut+i)->m_R)/sqrt(1.f+tan(temp)*tan(temp)));
            int m_MyY=int(double((boBut+i)->m_R)/sqrt(1.f+tan(temp)*tan(temp))*tan(temp));
            if(m_MyX<0){m_MyX=(-m_MyX);}
            if(m_MyY<0){m_MyY=(-m_MyY);}
            if(0<=heartCita&&heartCita<90){}
            else if(90<=heartCita&&heartCita<180){m_MyX=0-m_MyX;}
            else if(180<=heartCita&&heartCita<270){m_MyX=0-m_MyX;m_MyY=0-m_MyY;}
            else if(270<=heartCita&&heartCita<360){m_MyY=0-m_MyY;}
            m_MyX+=m_BX_;m_MyY+=m_BY_;
            (boBut+i)->m_BX=m_MyX;(boBut+i)->m_BY=m_MyY;

            (boBut+i)->m_ReleaseNum=2;
            (boBut+i)->m_NewNum=2;

            this->setSendImg(boBut+i,2,8,4,0);//-------------
            (boBut+i)->m_Only_Angle=(boBut+i)->m_Angle+90;//-------
            (boBut+i)->m_PrintId=2;//------
            break;
        }

    }
}

void BossBulletWay::rainStar(int i,int id)//参数一决定弹幕密度 参数二决定方式
{
    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck*i){return;}checkSendTime=0;
    this->f=0;
    int ranX=rand()%int(GAME_WIDTH);
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            initButDefault(i,ranX,f*(-15),1.5f);

            (boBut+i)->m_ReleaseNum=1;
            (boBut+i)->m_NewNum=3;
            if(id==0){(boBut+i)->m_Angle=90.f;}
            else{(boBut+i)->m_Angle=MathFunc().getAngle((boBut+i)->m_BX,(boBut+i)->m_BY,m_HX_,m_HY_);}
            this->setSendImg(boBut+i,2,8,4,0);//-------------
            (boBut+i)->m_Only_Angle=(boBut+i)->m_Angle+90;//-------
            (boBut+i)->m_PrintId=2;//------
            f++;
            if(f==9)
                break;
        }
    }
}

void BossBulletWay::scatterFind()
{
    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck){return;}checkSendTime=0;
    static double t_Angle=0.f;
    t_Angle+=11.0f;
    if(t_Angle>=360.f){t_Angle-=360.f;}
    this->f=0;
    static int p=80;
    static bool n=0;
    if(p==20){n=0;}
    else if(p==80){n=1;}
    if(n==0){++p;}
    if(n==1){--p;}
    int tempX=p*sin(t_Angle/180*PI);
    int tempY=p*cos(t_Angle/180*PI);
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            if(f==0){initButDefault(i,m_BX_+tempX,m_BY_+tempY);}
            else if(f==1){initButDefault(i,m_BX_+tempY,m_BY_-tempX);}
            else if(f==2){initButDefault(i,m_BX_-tempX,m_BY_-tempY);}
            else if(f==3){initButDefault(i,m_BX_-tempY,m_BY_+tempX);}

            (boBut+i)->m_Angle=MathFunc().getAngle((boBut+i)->m_X,(boBut+i)->m_Y,m_BX_,m_BY_);
            (boBut+i)->m_ReleaseNum=0;
            (boBut+i)->m_NewNum=3;
            this->setSendImg(boBut+i,2,8,4,0);//-------------
            //(boBut+i)->m_Only_Angle=(boBut+i)->m_Angle+90;//-------
            (boBut+i)->m_PrintId=2;//------
            ++f;
            if(f==4)
                break;
        }
    }
}

void BossBulletWay::scatterFindStar()
{
    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck*0.5){return;}checkSendTime=0;
    static double t_Angle=0.f;
    if(numMaxReturn(7,150)==false){t_Angle=rand()%361;setNumMoveAll(1.6f);}
    t_Angle+=11.0f;
    this->f=0;
    static int p_b=100;
    static int p=40;

    int tempX=p*sin(t_Angle*2.2/180*PI);
    int tempY=p*cos(t_Angle*2.2/180*PI);
    int tempX_B=p_b*sin(t_Angle/180*PI)+m_BX_;
    int tempY_B=p_b*cos(t_Angle/180*PI)+m_BY_;

    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            if(f==0){initButDefault(i,tempX_B+tempX,tempY_B+tempY);}
            else if(f==1){initButDefault(i,tempX_B+tempY,tempY_B-tempX);}
            else if(f==2){initButDefault(i,tempX_B-tempX,tempY_B-tempY);}
            else if(f==3){initButDefault(i,tempX_B-tempY,tempY_B+tempX);}

            (boBut+i)->m_ReleaseNum=2;
            (boBut+i)->m_NewNum=7;

            this->setSendImg(boBut+i,2,8,4,0);//-------------
            //(boBut+i)->m_Only_Angle=MathFunc().getAngle((boBut+i)->m_X,(boBut+i)->m_Y,m_BX_,m_BY_)+90;//-------
            (boBut+i)->m_PrintId=2;//------
            ++f;
            if(f==4)
                break;
        }
    }
}

void BossBulletWay::waveParticle(int id)
{

    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck){return;}checkSendTime=0;
    static int a=0;++a;if(a>360){a-=360;}
    static int jio=0;jio+=a;if(jio>=360){jio-=360;}if(jio<0){jio+=360;}
    this->f=0;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            initButDefault(i,m_BX_,m_BY_,1.3f);

            (boBut+i)->m_Angle=jio+(360/id*f);
            (boBut+i)->m_ReleaseNum=0;
            (boBut+i)->m_NewNum=3;

            this->setSendImg(boBut+i,2,8,4,3);//-------------
            (boBut+i)->m_Only_Angle=(boBut+i)->m_Angle+90;//-------
            (boBut+i)->m_PrintId=1;//------
            f++;
            if(f==id)
                break;
        }
    }
}

void BossBulletWay::rebound(int id)
{
    //全局阻滞
    static int checkSendTime=0;checkSendTime++;if(checkSendTime<dangerCheck*5){return;}checkSendTime=0;
    this->f=0;
    int checkNum=0;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
            checkNum++;
    }
    if(checkNum<id+10)
        return;
    ran=rand()%150+15;
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_Free)
        {
            (boBut+i)->m_Angle=f*(360/id)+ran;

            initButDefault(i,m_BX_,m_BY_,1.f);
            this->setSendImg(boBut+i,2,8,4,0);//-------------
            (boBut+i)->m_PrintId=2;//------

            (boBut+i)->m_NewNum=8;
            (boBut+i)->m_ReleaseNum=0;
            f++;
            if(f==id)
                break;
        }

    }
}


//以下为其它
void BossBulletWay::setNumMoveAll(double v)
{
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
    {
        if((boBut+i)->m_ReleaseNum==2){
            initButDefault(i,(boBut+i)->m_X,(boBut+i)->m_Y,v);
            (boBut+i)->m_NewNum=3;
            (boBut+i)->m_ReleaseNum=0;
            (boBut+i)->m_Angle=MathFunc().getAngle((boBut+i)->m_X,(boBut+i)->m_Y,m_BX_,m_BY_);

        }
    }
}

void BossBulletWay::setSendImg(BossBullet*but,int id,int f,double x,double y)
{
    but->setBossBullet(imgConfig.getImg(id,f,x,y));
}


