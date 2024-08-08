#include "bulletinformation.h"

void BulletInformation::initInformation()
{
    m_Rule=m_initRule;
    m_Step=m_initStep;
    m_SmallStep=m_initSmallStep;
    m_Acceleration=m_initAcceleration;
    m_PrintId=m_initPrintId;
    m_OnlyAngle=m_initOnlyAngle;
}

BulletInformation::BulletInformation(const QPixmap&img,int rule,double step,double smallstep,double acceleration,int printid,double onlyangle):
    m_Img(img),
    m_Rule(rule),
    m_Step(step),
    m_SmallStep(smallstep),
    m_Acceleration(acceleration),
    m_PrintId(printid),
    m_OnlyAngle(onlyangle)
{
    m_initRule=m_Rule;
    m_initStep=m_Step;
    m_initSmallStep=m_SmallStep;
    m_initAcceleration=m_Acceleration;
    m_initPrintId=m_PrintId;
    m_initOnlyAngle=m_OnlyAngle;

}

void BulletInformation::operator=(const BulletInformation &butInfor)
{
    setInformation(butInfor.m_Img,butInfor.m_Rule,butInfor.m_Step,butInfor.m_SmallStep,butInfor.m_Acceleration,butInfor.m_PrintId,butInfor.m_OnlyAngle);

}

void BulletInformation::setInformation(const QPixmap&img,int rule,double step,double smallstep,double acceleration,int printid,double onlyangle)
{
    m_Img=img;
    m_Rule=rule;
    m_Step=step;
    m_SmallStep=smallstep;
    m_Acceleration=acceleration;
    m_PrintId=printid;
    m_OnlyAngle=onlyangle;

    m_initRule=m_Rule;
    m_initStep=m_Step;
    m_initSmallStep=m_SmallStep;
    m_initAcceleration=m_Acceleration;
    m_initPrintId=m_PrintId;
    m_initOnlyAngle=m_OnlyAngle;
}

