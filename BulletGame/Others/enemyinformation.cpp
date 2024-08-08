#include "enemyinformation.h"


EnemyInformation::EnemyInformation(const QPixmap &img, int rule, double step, double smallstep, double acceleration,int loc,int hp,int endSend):
    m_Img(img),
    m_Rule(rule),
    m_Step(step),
    m_SmallStep(smallstep),
    m_Acceleration(acceleration),
    m_Location(loc),
    m_Hp(hp),
    m_EndSend(endSend)
{

}

void EnemyInformation::setInformation(const QPixmap &img, int rule, double step, double smallstep, double acceleration,int loc,int hp,int endSend)
{
    m_Img=img;
    m_Rule=rule;
    m_Step=step;
    m_SmallStep=smallstep;
    m_Acceleration=acceleration;
    m_Location=loc;
    m_Hp=hp;
    m_EndSend=endSend;
}

void EnemyInformation::operator=(const EnemyInformation &enemyInfor)
{
    setInformation(enemyInfor.m_Img,enemyInfor.m_Rule,enemyInfor.m_Step,enemyInfor.m_SmallStep,enemyInfor.m_Acceleration,enemyInfor.m_Location,enemyInfor.m_Hp,enemyInfor.m_EndSend);
}
