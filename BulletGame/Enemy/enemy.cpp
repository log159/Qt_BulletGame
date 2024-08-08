#include "enemy.h"

Enemy::Enemy()
{
    initEnemy();
}

void Enemy::initEnemy()
{
    m_EnemyBulletArr=new EnemyBullet[GAME_BULLET_NUM_3];
    m_Prop=new Prop[GAME_PROP_NUM];
    enButSendWay=new EnemyBulletWay;
    //弹夹初始化
    for(int i=0;i<int(GAME_BULLET_NUM_3);++i)
        m_EnemyBulletArr[i].initEnemyBullet();
    enButSendWay->enBut=m_EnemyBulletArr;

    m_Angle=90.f;
    m_Free=true;
    srand((unsigned)time(NULL));

}

void Enemy::setEnemy(int a,const QPixmap& img,int hp)
{
    m_image=img;

    //刷新数据初始化
    m_OffsetNum=0;

    m_Width=m_image.width()/4;
    m_Height=m_image.height()/4;

    m_Circular.m_R=m_Width*0.3;
    m_Circular.m_X=-1000;
    m_Circular.m_Y=-1000;


    m_Xoffset=m_Width*m_OffsetNum;
    m_Yoffset=m_Height*a;


    m_PrintX=(m_X-m_Width*0.5)-m_Xoffset;
    m_PrintY=(m_Y-m_Height*0.5)-m_Yoffset;

    m_Hp=hp;
    m_initHp=m_Hp;
    m_R=0;

}


void Enemy::sendBullet()
{
    if(m_Free)
        return;
    this->enButSendWay->setXY(m_X,m_Y,m_HX,m_HY);
    switch(m_SendRule)
    {
    //无
    case 0:break;
    //变速直线
    case 1:if(enButSendWay->changeSpeed()){m_SendRule=0;}break;
    //狙击扇形
    case 2:if(enButSendWay->snipeRfan()){m_SendRule=0;}break;
    //狙击直线
    case 3:if(enButSendWay->sinpeSpeed()){m_SendRule=0;}break;
    //连续狙击扇形
    case 4:enButSendWay->snipeRfan();break;
    //回旋直线
    case 5:enButSendWay->circle();break;
    }
}

void Enemy::newEnemy()
{
    if(m_Free)
        return;

    if(m_Step>=m_SmallStep)
        m_Step+=m_Acceleration;

    //无
    if(this->m_Rule==0)
    {

    }
    //普通前行
    else if(this->m_Rule==1)
    {
        m_R+=m_Step;
        mathFunc();
    }
    //二次函数
    else if(this->m_Rule==2)
    {
        ++m_Y;
        double a,b,A,B;
        a=double(GAME_HEIGHT)/3;
        b=double(GAME_WIDTH)/3;
        A=-(b/(a*a));
        B=(2*b)/a;
        if(m_OtherNum==false)
        {
            m_X=int(A*m_Y*m_Y+B*m_Y)*2;
        }
        else
        {
            m_X=int(-A*m_Y*m_Y-B*m_Y)*2+int(GAME_WIDTH);
        }

    }
    //普通前行 计时退场
    else if(this->m_Rule==3)
    {
        m_R+=m_Step;
        mathFunc();
        ++m_OtherNum;

        if(m_OtherNum>=300)
        {
            this->m_OtherNum=0;
            this->m_Angle=270.f;
            this->m_Rule=1;
            this->m_Step=1.f;
            this->m_SmallStep=1.f;
            this->m_Acceleration=0.f;
            this->m_BX=this->m_X;
            this->m_BY=this->m_Y;
            this->m_R=0;
        }
    }
    //普通前行 计时退场 快
    else if(this->m_Rule==4)
    {
        m_R+=m_Step;
        mathFunc();
        ++m_OtherNum;

        if(m_OtherNum>=100)
        {
            this->m_OtherNum=0;
            this->m_Angle=270.f;
            this->m_Rule=1;
            this->m_Step=1.f;
            this->m_SmallStep=1.f;
            this->m_Acceleration=0.f;
            this->m_BX=this->m_X;
            this->m_BY=this->m_Y;
            this->m_R=0;
        }
    }




    release();
}

void Enemy::setInformation(const EnemyInformation &ememyInfor)
{
    this->setEnemy(ememyInfor.m_Location,ememyInfor.m_Img,ememyInfor.m_Hp);
    this->m_Rule=ememyInfor.m_Rule;
    this->m_Step=ememyInfor.m_Step;
    this->m_SmallStep=ememyInfor.m_SmallStep;
    this->m_Acceleration=ememyInfor.m_Acceleration;
    this->m_EndSendNum=ememyInfor.m_EndSend;

}
void Enemy::newBullet()
{
    for(int i=0;i<int(GAME_BULLET_NUM_3);++i)
        if(m_EnemyBulletArr[i].m_Free==false)
            m_EnemyBulletArr[i].newEnemyBullet();
    //掉落随newBullet一起更新
    for(int i=0;i<int(GAME_PROP_NUM);++i)
    {
        if((m_Prop+i)->m_Free==false)
        {
            (m_Prop+i)->newProp();
        }
    }
}

void Enemy::sendProp()
{

    for(int i=0;i<int(GAME_PROP_NUM);++i)
    {
        if((m_Prop+i)->m_Free)
        {

            (m_Prop+i)->id=rand()%3;
            if((m_Prop+i)->id==0)
                (m_Prop+i)->m_image=CutImg().getImg(1,16,0,13);
            else if((m_Prop+i)->id==1)
                 (m_Prop+i)->m_image=CutImg().getImg(1,16,3,13);
            else if((m_Prop+i)->id==2)
                (m_Prop+i)->m_image=CutImg().getImg(1,16,1,13);
            (m_Prop+i)->m_X=this->m_X;
            (m_Prop+i)->m_Y=this->m_Y;
            (m_Prop+i)->m_Free=false;

            break;
        }
    }

}

void Enemy::endSendBullet()
{
    sendProp();

    //无
    if(m_EndSendNum==0){

    }
    //四角
    else if(m_EndSendNum==1){
        enButSendWay->fourQuarter();
    }
    //四角Plus
    else if(m_EndSendNum==2){
        enButSendWay->fourQuarterPlus();
    }

}
void Enemy::mathFunc()
{
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


void Enemy::release()
{

    //判断释放
    if(m_Y>int(GAME_HEIGHT)+3*m_Height)
        m_Free=true;
    else if(m_Y<(-3*m_Height))
        m_Free=true;
    else if(m_X<(-3*m_Width))
        m_Free=true;
    else if(m_X>int(GAME_WIDTH)+3*m_Width)
        m_Free=true;

    if(m_Free==true)
    {
        m_X=-1000;
        m_Y=-1000;
        m_Angle=90.f;
        m_R=0;
        m_OtherNum=0;
        enButSendWay->otherNum=100;
    }
    //gif变换
    ++addTimePrint;
    if(addTimePrint>=20){
    addTimePrint=0;
    ++m_OffsetNum;
    }
    if(m_OffsetNum>=4)
        m_OffsetNum=0;
    //判定偏移量
    m_Circular.moveTo(m_X,m_Y);
    //显示偏移量
    m_Xoffset=m_Width*m_OffsetNum;
    m_PrintX=(m_X-m_Width/2)-m_Xoffset;
    m_PrintY=(m_Y-m_Height/2)-m_Yoffset;
}




Enemy::~Enemy()
{
    delete enButSendWay;
    delete[] m_EnemyBulletArr;
    delete[] m_Prop;
}



