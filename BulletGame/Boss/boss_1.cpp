#include "boss_1.h"


Boss_1::Boss_1()
{
    this->initBoss(QString(GAME_BOSS_BLUE_WAY2),int(GAME_BOSS_RECT),5);

    this->initHpVector(19,600);
}

void Boss_1::sendBullet()
{

    this->getPoint();

    static int checkSendTime=0;
    checkSendTime++;if(checkSendTime<dangerCheck*0.5){return;}checkSendTime=0;

    switch(this->m_BulletNum)
    {
    case 0:break;//无攻击方式
    case 1:m_BobuWay.scattering(1);break;//rand霰弹
    case 2:m_BobuWay.windmill(1);m_BobuWay.scattering(2);break;//风车*1 rand霰弹
    case 3:m_BobuWay.windmill(2);m_BobuWay.spreadStar(30);break;//风车*2 扩散
    case 4:m_BobuWay.windmill(3);m_BobuWay.spreadStar(30);break;//风车*3 扩散
    case 5:m_BobuWay.windmill(3);m_BobuWay.windmillCounter(3);break;//风车*3 逆风车*3
    case 6:m_BobuWay.windmillMove(3);m_BobuWay.rainStar(12);break;//风车*3-摆动
    case 7:m_BobuWay.windmillMove(5);m_BobuWay.rainStar(10);break;//风车*5-摆动
    case 8:m_BobuWay.rebound(10);break;//反弹
    case 9:m_BobuWay.windmillMove(6);m_BobuWay.spreadStar(40);break;//风车*6-摆动 扩散
    case 10:m_BobuWay.sinStar();stopMove();break;//sin型轨迹 停止移动
    case 11:m_BobuWay.rainStar(6,1);break;//流
    case 12:m_BobuWay.sinStar();m_BobuWay.rainStar(6,1);break;//sin型轨迹 流
    case 13:m_BobuWay.scatterFind();m_BobuWay.spreadStar(20);break;//四角聚散 扩散
    case 14:m_BobuWay.windmill(8);break;//风车*8
    case 15:m_BobuWay.scatterFindStar();break;//聚散
    case 16:m_BobuWay.spreadStar(20,10,1);m_BobuWay.rainStar(7);break;//rand扩散 流
    case 17:m_BobuWay.windmill(3,100,100);m_BobuWay.windmillCounter(3,GAME_WIDTH-100,100);break;//风车*1 逆风车*1
    case 18:m_BobuWay.lorenz(75);m_BobuWay.spreadStar(30);break;//other 扩散
    case 19:m_BobuWay.waveParticle(10);break;//波粒
    default:break;
    }

}
