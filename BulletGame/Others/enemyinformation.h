#ifndef ENEMYINFORMATION_H
#define ENEMYINFORMATION_H
#include <QPixmap>

class EnemyInformation
{
public:
    QPixmap m_Img;
    int m_Rule;
    double m_Step;
    double m_SmallStep;
    double m_Acceleration;
    int m_Location;
    int m_Hp;
    int m_EndSend;


    EnemyInformation()=default;
    EnemyInformation(const QPixmap&img,int rule,double step,double smallstep,double acceleration,int loc,int hp,int endSend=0);

    void setInformation(const QPixmap&img,int rule,double step,double smallstep,double acceleration,int loc,int hp,int endSend=0);
    void operator=(const EnemyInformation&butInfor);
};

#endif // ENEMYINFORMATION_H
