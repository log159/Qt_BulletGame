#include "gamewidget_1.h"

GameWidget_1::GameWidget_1()
{
    this->initNumber();
    this->initWidget();
}
void GameWidget_1::initNumber()
{
    //成员创建
    this->m_Map=new Map(GAME_MAP_WAY_1);
    this->m_Hero=new Hero;
    this->m_Boss=new Boss_1;
    this->m_Enemy=new Enemy[GAME_ENEMY_NUM];
    this->enSendWay=new WidgetSendWay(m_Enemy);
}

void GameWidget_1::sendEnemyTimer()
{
    ++m_AddEnemyNum;//时间向前推进
    //出怪函数
    //Enemy Information (const QPixmap&img,int rule,double step,double smallstep,double acceleration,int loc,int hp);
    //Bullet Information (const QPixmap&img,int rule,double step,double smallstep,double acceleration,int printid,double onlyangle);


    EnemyInformation enemyInfor;
    BulletInformation butInfor;


//    enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_C),1,4.f,2.5f,-0.03f,0,999);
//    butInfor.setInformation(CutImg().getImg(2,8,3,0),1,2.f,0.f,0.f,1,0.f);
//    this->sendEnemy(9,enemyInfor,5,butInfor);
    if(m_AddEnemyNum<1000){

        enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_A),1,3.f,1.f,-0.03f,0,5,1);
        butInfor.setInformation(CutImg().getImg(2,8,4,0),0,2.f,0.f,0.f,1,0.f);
        this->sendEnemy(1,enemyInfor,3,butInfor);
    }
    else if(1000<m_AddEnemyNum&&m_AddEnemyNum<1500){
        enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_B),1,3.f,1.f,-0.02f,0,3);
        butInfor.setInformation(CutImg().getImg(2,8,2,0),0,4.f,1.7f,-0.01f,1,0.f);
        this->sendEnemy(1,enemyInfor,2,butInfor);
    }
    else if(1500<m_AddEnemyNum&&m_AddEnemyNum<2200){
        enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_A),1,3.f,1.f,-0.03f,0,5);
        butInfor.setInformation(CutImg().getImg(2,8,4,0),0,2.f,0.f,0.02f,1,0.f);
        this->sendEnemy(2,enemyInfor,3,butInfor);
    }
    else if(2200<m_AddEnemyNum&&m_AddEnemyNum<3300){
        enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_B),1,3.f,1.f,-0.03f,0,3,2);
        butInfor.setInformation(CutImg().getImg(2,8,2,0),0,4.f,1.7f,-0.01f,1,0.f);
        this->sendEnemy(3,enemyInfor,2,butInfor);
    }
    else if(3300<m_AddEnemyNum&&m_AddEnemyNum<4500){
        enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_B),2,3.f,1.f,-0.03f,0,3,2);
        butInfor.setInformation(CutImg().getImg(2,8,2,0),0,4.f,1.7f,-0.01f,1,0.f);
        this->sendEnemy(4,enemyInfor,2,butInfor);
    }
    else if(4500<m_AddEnemyNum&&m_AddEnemyNum<5500){
        enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_B),3,3.f,1.f,-0.03f,0,3);
        butInfor.setInformation(CutImg().getImg(2,8,2,0),0,4.f,1.7f,-0.02f,1,0.f);
        this->sendEnemy(5,enemyInfor,4,butInfor);
    }
    else if(5500<m_AddEnemyNum&&m_AddEnemyNum<6800){
        enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_B),4,3.f,1.f,-0.03f,0,3,2);
        butInfor.setInformation(CutImg().getImg(2,8,2,0),0,4.f,1.7f,-0.02f,1,0.f);
        this->sendEnemy(2,enemyInfor,2,butInfor);
    }
    else if(6800<m_AddEnemyNum&&m_AddEnemyNum<7500)
    {
        enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_A),3,3.f,0.f,-0.03f,0,5,1);
        butInfor.setInformation(CutImg().getImg(2,8,4,0),0,2.f,0.f,0.f,1,0.f);
        this->sendEnemy(6,enemyInfor,1,butInfor);
    }
    else if(7500<m_AddEnemyNum&&m_AddEnemyNum<8800){
        enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_B),3,3.f,1.f,-0.03f,0,3);
        butInfor.setInformation(CutImg().getImg(2,8,2,0),0,4.f,1.7f,-0.02f,1,0.f);
        this->sendEnemy(7,enemyInfor,4,butInfor);
    }
    else if(8800<m_AddEnemyNum&&m_AddEnemyNum<11000)
    {
        enemyInfor.setInformation(CutImg().getImg(GAME_ENEMY_WAY_C),1,5.f,3.5f,-0.03f,0,999);
        butInfor.setInformation(CutImg().getImg(2,8,3,0),1,2.f,0.f,0.f,1,0.f);
        this->sendEnemy(9,enemyInfor,5,butInfor);
    }
    else if(11500<m_AddEnemyNum)
    {
        sendBoss();
    }
    else{}


}
void GameWidget_1::sendEnemy(int sendEnemyId,EnemyInformation & enemyInfor,int sendBulletId,BulletInformation & butInfor)
{

    enSendWay->setInformation(enemyInfor,sendBulletId,butInfor);

    switch(sendEnemyId)
    {
    //无
    case 0:break;
    //上场随机
    case 1:enSendWay->upRand();break;
    //上场有序 交互错位
    case 2:enSendWay->upDislocate();break;
    //半角随机
    case 3:enSendWay->halfAngleRand();break;
    //上场角落
    case 4:enSendWay->upCorner();break;
    //左场慢速
    case 5:enSendWay->leftSmall();break;
    //上场随机
    case 6:enSendWay->upRandQuick();break;
    //右场慢速
    case 7:enSendWay->rightSmall();break;
    //中场慢速
    case 8:enSendWay->middleSmall();break;
    //左场慢速
    case 9:enSendWay->leftOrRightSmall();break;
    }




}
