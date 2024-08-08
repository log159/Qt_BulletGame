#include "boss.h"




void Boss::initBoss(const QString& str,int r,int x)
{
    this->m_image.load(str);
    //初始位置
    this->m_X=int(GAME_WIDTH)/2;
    this->m_Y=-50;

    //刷新数据初始化
    this->m_Speed=0;
    this->m_OffsetNum=0;

    this->m_Width=m_image.width()/4;
    this->m_Height=m_image.height()/x;

    this->m_Free=true;//初始闲置
    this->m_Over=false;//非死亡
    this->m_Harm=false;//是否有伤害判定
    this->m_Move=true;//到达靶目标后是否移动

    //位移目标
    this->m_CoMoveLocation.getCoordinate(int(GAME_WIDTH)/2,int(GAME_HEIGHT)/3);

    //初始攻击方式无
    this->m_BulletNum=0;

    this->m_Step=1;//步长(速度)
    this->m_Acceleration=2.0f;//加速度

    this->m_Xoffset=m_Width*m_OffsetNum;
    this->m_Yoffset=m_Height*0;

    this->m_PrintX=(m_X-this->m_Width*0.5)-m_Xoffset;
    this->m_PrintY=(m_Y-this->m_Height*0.5)-m_Yoffset;


    this->m_Hphundred=100.f;

    //判定范围
    this->m_Circular.m_R=r;
    this->m_Circular.m_X=m_X;
    this->m_Circular.m_Y=m_Y;

    //自定义矩形
    this->m_Rect.m_X=10;
    this->m_Rect.m_Y=10;
    this->m_Rect.m_W=int(GAME_WIDTH)-m_Rect.m_X*2;
    this->m_Rect.m_H=10;
    this->m_RectHp=m_Rect;

    //时间函数
    srand((unsigned)time(NULL));

    this->m_BossBulletArr=new BossBullet[GAME_BULLET_NUM_4];
    for(int i=0;i<int(GAME_BULLET_NUM_4);++i)
        (m_BossBulletArr+i)->initBossBullet();

    this->m_BobuWay.boBut=this->m_BossBulletArr;

}

void Boss::initHpVector(int n,int hp)
{
    for(int i=0;i<n;++i)
        v_Hp.push_back(hp);
    m_Hp=v_Hp[0];
    m_It=0;
}
void Boss::getPoint()
{
    //弹幕派出法则获取Boss坐标
    m_BobuWay.newNeedFirst(this->m_X,this->m_Y);
    //弹幕派出法则获取Hero坐标
    m_BobuWay.m_HX_=m_CoAttackLocation.putX();
    m_BobuWay.m_HY_=m_CoAttackLocation.putY();
    //弹幕获取Hero坐标
    for(int j=0;j<int(GAME_BULLET_NUM_4);++j){
        (m_BossBulletArr+j)->m_HX=m_CoAttackLocation.putX();
        (m_BossBulletArr+j)->m_HY=m_CoAttackLocation.putY();
    }
}


void Boss::nextBullet()
{
    m_BulletNum=m_It+1;
}

void Boss::stopMove()
{
    m_Move=false;
//    m_CoMoveLocation.getCoordinate(this->m_X,this->m_Y);//立刻停下
    m_CoMoveLocation.getCoordinate(int(GAME_WIDTH)/2,int(GAME_HEIGHT)/3);//到默认位置停下
}

void Boss::continueMove()
{
    m_Move=true;
}

void Boss::endGoto()
{
    m_Move=false;
    m_CoMoveLocation.getCoordinate(-50,-50);
}
void Boss::newBullet()
{

    static int checkNewTime=0;
    checkNewTime++;if(checkNewTime<dangerCheck){return;}checkNewTime=0;
    for(int j=0;j<int(GAME_BULLET_NUM_4);++j)
        if((m_BossBulletArr+j)->m_Free==false)
            (m_BossBulletArr+j)->newBossBullet();

}

void Boss::goMove()
{
    if(this->m_Move==false)
        return;
    if(m_CoMoveLocation.putX()==m_X&&m_CoMoveLocation.putY()==m_Y)
    {
        int tempX=rand()%(int(GAME_WIDTH)-200)+100;
        int tempY=rand()%(int(GAME_HEIGHT)/2-200)+100;
        m_CoMoveLocation.getCoordinate(tempX,tempY);
    }
}

void Boss::getHeroLocation(int x, int y)
{
    m_CoAttackLocation.getCoordinate(x,y);
}
void Boss::newBoss()
{
    if(m_Free)
        return;

    if(m_It<v_Hp.size())
    {
        double proportion=double(m_Hp)/double(v_Hp[m_It]);
        if(proportion<0.f)
            proportion=0.f;
        m_Hphundred=proportion*100.f;
        //刷新Hp的显示
        if(m_Hp>=0){m_RectHp.m_W=int((double(m_Hp)/double(v_Hp[m_It]))*double(int(GAME_WIDTH)-m_Rect.m_X*2));}
    }
    //刷新Hp

    else{m_Hp=0;m_RectHp.m_W=0;}
    //位移随时间偏移
    m_Acceleration-=0.3f;
    if(m_Acceleration<=0)
        m_Acceleration=0;
    if(m_X>m_CoMoveLocation.putX())
        m_X-=m_Step+int(m_Acceleration);
    else if(m_X<m_CoMoveLocation.putX())
        m_X+=m_Step+int(m_Acceleration);
    if(m_Y>m_CoMoveLocation.putY())
        m_Y-=m_Step+int(m_Acceleration);
    else if(m_Y<m_CoMoveLocation.putY())
        m_Y+=m_Step+int(m_Acceleration);
    if(m_X==m_CoMoveLocation.putX()&&m_Y==m_CoMoveLocation.putY())
        m_Acceleration=2.0f;
    m_Circular.moveTo(m_X,m_Y);//判定位移
    this->m_PrintX=(m_X-this->m_Width/2)-m_Xoffset;
    this->m_PrintY=(m_Y-this->m_Height/2)-m_Yoffset;
    //形态随时间偏移
    m_Speed++;
    if(m_Speed<int(GAME_BOSS_ADDSPEED))
        return;
    m_Speed=0;
    this->m_OffsetNum++;
    if(m_OffsetNum>=4)
        m_OffsetNum=0;
    //修改偏移量
    this->m_Xoffset=m_Width*m_OffsetNum;
    this->m_PrintX=(m_X-this->m_Width/2)-m_Xoffset;
    this->m_PrintY=(m_Y-this->m_Height/2)-m_Yoffset;
}



Boss::~Boss()
{
    delete[] m_BossBulletArr;
}
