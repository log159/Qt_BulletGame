#include "gamewidget_2.h"

GameWidget_2::GameWidget_2()
{
    this->initNumber();
    this->initWidget();
}
void GameWidget_2::initNumber()
{
    //成员创建
    this->m_Map=new Map(GAME_MAP_WAY_2);
    this->m_Hero=new Hero;
    this->m_Boss=new Boss_2;
    this->m_Enemy=new Enemy[GAME_ENEMY_NUM];
    this->enSendWay=new WidgetSendWay(m_Enemy);
}

void GameWidget_2::sendEnemyTimer()
{
//    m_AddEnemyNum++;//时间向前推进
//    //出怪函数
//    if(m_AddEnemyNum<2000){
//    sendBoss();
}
void GameWidget_2::sendEnemy(int sendEnemyId,EnemyInformation & enemyInfor,int sendBulletId,BulletInformation & butInfor)
{
    Q_UNUSED(sendEnemyId)
    Q_UNUSED(butInfor)
    Q_UNUSED(enemyInfor)
    Q_UNUSED(sendBulletId)
}
