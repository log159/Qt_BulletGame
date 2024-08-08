#include "widgetsendway.h"

WidgetSendWay::WidgetSendWay(Enemy *ptr):
    enemyPtr(ptr)
{

}


void WidgetSendWay::setInformation(EnemyInformation &enemyInfor, int sendBulletId, BulletInformation &butInfor)
{
    this->enInfor=enemyInfor;
    this->sendBut=sendBulletId;
    this->buInfor=butInfor;
}

void WidgetSendWay::setEnemyInformation(Enemy *en)
{
    //获取Enemy的位移信息
    en->setInformation(enInfor);
    //获取Enemy弹幕派出信息
    en->m_SendRule=sendBut;
    //获取Enemy弹幕位移信息
    en->enButSendWay->m_Information=buInfor;
    //释放
    en->m_Free=false;
}

void WidgetSendWay::upRand()
{
    static int addTime=0;++addTime;if(addTime<int(GAME_ENEMY_SEND_TIME)*6){return;}addTime=0;

    for(int i=0;i<int(GAME_ENEMY_NUM);i++)
    {
        if((enemyPtr+i)->m_Free)
        {
//            //设置信息
            setEnemyInformation(enemyPtr+i);

            (enemyPtr+i)->m_BX=rand()%(GAME_WIDTH-(enemyPtr+i)->m_Width)+(enemyPtr+i)->m_Width*0.5;
            (enemyPtr+i)->m_BY=-(enemyPtr+i)->m_Height*0.5;
            (enemyPtr+i)->m_Angle=90.f;
            break;
        }
    }
}

void WidgetSendWay::upRandQuick()
{
    static int addTime=0;++addTime;if(addTime<int(GAME_ENEMY_SEND_TIME)*2){return;}addTime=0;

    for(int i=0;i<int(GAME_ENEMY_NUM);i++)
    {
        if((enemyPtr+i)->m_Free)
        {
            //设置信息
            setEnemyInformation(enemyPtr+i);

            (enemyPtr+i)->m_BX=rand()%(GAME_WIDTH-(enemyPtr+i)->m_Width)+(enemyPtr+i)->m_Width*0.5;
            (enemyPtr+i)->m_BY=-(enemyPtr+i)->m_Height*0.5;
            (enemyPtr+i)->m_Angle=90.f;
            break;
        }
    }
}

void WidgetSendWay::upDislocate()
{
    static int addTime=0;++addTime;if(addTime<int(GAME_ENEMY_SEND_TIME)*10){return;}addTime=0;
    static bool t=false;t=!t;

    int f=0;
    for(int i=0;i<int(GAME_ENEMY_NUM);i++)
    {
        if((enemyPtr+i)->m_Free)
        {
            //设置信息
            setEnemyInformation(enemyPtr+i);

            if(t==true)
                (enemyPtr+i)->m_BX=f*80+100;
            else
                (enemyPtr+i)->m_BX=f*80+60;
            (enemyPtr+i)->m_BY=-(enemyPtr+i)->m_Height*0.5;
            (enemyPtr+i)->m_Angle=90.f;

            ++f;
            if(f>=6)
                break;
        }
    }
}

void WidgetSendWay::halfAngleRand()
{
    static int addTime=0;++addTime;if(addTime<int(GAME_ENEMY_SEND_TIME)*10){return;}addTime=0;

    for(int i=0;i<int(GAME_ENEMY_NUM);i++)
    {
        if((enemyPtr+i)->m_Free)
        {
            //设置信息
            setEnemyInformation(enemyPtr+i);

            (enemyPtr+i)->m_BX=rand()%(GAME_WIDTH-(enemyPtr+i)->m_Width)+(enemyPtr+i)->m_Width*0.5;
            (enemyPtr+i)->m_BY=-(enemyPtr+i)->m_Height*0.5;

            (enemyPtr+i)->m_Angle=rand()%90+45;
            break;
        }
    }
}

void WidgetSendWay::upCorner()
{
    static int addTime=0;++addTime;if(addTime<int(GAME_ENEMY_SEND_TIME)*2){return;}addTime=0;
    static bool t=false;t=!t;
    int f=0;
    for(int i=0;i<int(GAME_ENEMY_NUM);i++)
    {
        if((enemyPtr+i)->m_Free)
        {
            //设置信息
            setEnemyInformation(enemyPtr+i);

            (enemyPtr+i)->m_OtherNum=int(t);

            (enemyPtr+i)->m_X=-(enemyPtr+i)->m_Width*0.5;
            (enemyPtr+i)->m_Y=-(enemyPtr+i)->m_Height*0.5;

            (enemyPtr+i)->m_Angle=rand()%90+45;
            ++f;
            if(f>=2)
                break;
        }
    }
}

void WidgetSendWay::leftSmall()
{
    static int addTime=0;++addTime;if(addTime<int(GAME_ENEMY_SEND_TIME)*15){return;}addTime=0;

    for(int i=0;i<int(GAME_ENEMY_NUM);i++)
    {
        if((enemyPtr+i)->m_Free)
        {
            //设置信息
            setEnemyInformation(enemyPtr+i);

            (enemyPtr+i)->m_BX=-(enemyPtr+i)->m_Width;
            (enemyPtr+i)->m_BY=(enemyPtr+i)->m_Height*2;

            (enemyPtr+i)->m_Angle=0.f;
            break;
        }
    }
}

void WidgetSendWay::rightSmall()
{
    static int addTime=0;++addTime;if(addTime<int(GAME_ENEMY_SEND_TIME)*15){return;}addTime=0;

    for(int i=0;i<int(GAME_ENEMY_NUM);i++)
    {
        if((enemyPtr+i)->m_Free)
        {
            //设置信息
            setEnemyInformation(enemyPtr+i);

            (enemyPtr+i)->m_BX=(enemyPtr+i)->m_Width+GAME_WIDTH;
            (enemyPtr+i)->m_BY=(enemyPtr+i)->m_Height*2;

            (enemyPtr+i)->m_Angle=180.f;
            break;
        }
    }
}

void WidgetSendWay::middleSmall()
{
    static int addTime=int(GAME_ENEMY_SEND_TIME)*50;++addTime;if(addTime<int(GAME_ENEMY_SEND_TIME)*60){return;}addTime=0;

    static int num=0;
    if(num>=3){return;}

    for(int i=0;i<int(GAME_ENEMY_NUM);i++)
    {
        if((enemyPtr+i)->m_Free)
        {
            //设置信息
            setEnemyInformation(enemyPtr+i);

            (enemyPtr+i)->m_BX=GAME_WIDTH*0.5;
            (enemyPtr+i)->m_BY=-(enemyPtr+i)->m_Height;

            (enemyPtr+i)->m_Angle=90.f;
            ++num;
            break;
        }
    }
}

void WidgetSendWay::leftOrRightSmall()
{
    static int addTime=int(GAME_ENEMY_SEND_TIME)*50;++addTime;if(addTime<int(GAME_ENEMY_SEND_TIME)*60){return;}addTime=0;

    int f=0;
    for(int i=0;i<int(GAME_ENEMY_NUM);i++)
    {
        if((enemyPtr+i)->m_Free)
        {
            setEnemyInformation(enemyPtr+i);
            if(f==0)
            {
                (enemyPtr+i)->m_BX=-(enemyPtr+i)->m_Width;
                (enemyPtr+i)->m_BY=100;
                (enemyPtr+i)->m_Angle=0.f;
            }
            else if(f==1)
            {
                (enemyPtr+i)->m_BX=GAME_WIDTH+(enemyPtr+i)->m_Width;
                (enemyPtr+i)->m_BY=200;
                (enemyPtr+i)->m_Angle=180.f;
            }
            ++f;
            if(f==2)
                break;
        }
    }
}
