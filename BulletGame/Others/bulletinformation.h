#ifndef BULLETINFORMATION_H
#define BULLETINFORMATION_H

#include <QPixmap>

class BulletInformation
{
public:
    QPixmap m_Img;
    int m_Rule;
    double m_Step;
    double m_SmallStep;
    double m_Acceleration;
    int m_PrintId;
    double m_OnlyAngle;

private:
    int m_initRule;
    double m_initStep;
    double m_initSmallStep;
    double m_initAcceleration;
    int m_initPrintId;
    double m_initOnlyAngle;


public:
    void initInformation();

    BulletInformation()=default;
    BulletInformation(const QPixmap&img,int rule,double step,double smallstep,double acceleration,int printid,double onlyangle);

    void setInformation(const QPixmap&img,int rule,double step,double smallstep,double acceleration,int printid,double onlyangle);
    void operator=(const BulletInformation&butInfor);
};

#endif // BULLETINFORMATION_H
