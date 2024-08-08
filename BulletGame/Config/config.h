#ifndef CONFIG_H
#define CONFIG_H

#endif // CONFIG_H

//WINDOW属性
#define WINDOW_WIDTH 744
#define WINDOW_HEIGHT 544
#define WINDOW_SIDERBAR_WAY ":/res/Sidebar.png"

//GAME属性
#define GAME_WIDTH 544
#define GAME_HEIGHT 544
#define GAME_TIME 8//ms
#define GAME_ICON ":/res/hierogram.ico"
#define GAME_TEXT "BulletGame"

//地图类
#define GAME_MAP_WAY_1 ":/res/Map_1.png"
#define GAME_MAP_WAY_2 ":/res/Map_2.png"
#define GAME_MAP_SPEED 1//地图刷新步长


//主角类
#define GAME_HERO_WAY ":/res/Demon.png"
#define GAME_HERO_WAY_ ":/res/Demon_.png"
#define GAME_HERO_ADDSPEED 40//贴图刷新速度
#define GAME_HERO_SPEED 1//步长
#define GAME_HERO_ADDBULLETSPEED 4//子弹派出速度
#define GAME_HERO_TIME 1//ms
#define GAME_HERO_TIMESMALL 20//ms
#define GAME_HERO_RECT 4//判定框半径
#define GAME_HERO_SENDBULLET_TIME 8//弹幕派出速度


//敌人类
#define GAME_ENEMY_WAY ":/res/Enemy_1.png"
#define GAME_ENEMY_WAY_A ":/res/Enemy_A.png"
#define GAME_ENEMY_WAY_B ":/res/Enemy_B.png"
#define GAME_ENEMY_WAY_C ":/res/Enemy_C.png"
#define GAME_ENEMY_WAY_D ":/res/Enemy_D.png"
#define GAME_ENEMY_WAY_DRAGON ":/res/Enemy_2.png"
#define GAME_ENEMY_SEND_TIME 10 //ms派出敌人刷新速度
#define GAME_ENEMY_SPEED 1//步长
#define GAME_ENEMY_NUM 50//敌人数量
#define GAME_ENEMY_ADDBULLETSPEED 300//指定类子弹派出速度默认缓冲
#define GAME_ENEMY_TIME 10//全局敌人位移和形态改变速度
#define GAME_ENEMY_SENDBULLET 10//全局敌人派出弹幕速度
#define GAME_ENEMY_RECT 12//一般类敌人的判定框半径


//弹幕类
//#define GAME_BULLET_0 ":/res/Bullet_0.png"//黑白弹幕
//#define GAME_BULLET_1 ":/res/Bullet_1.png"//蓝色弹幕
//#define GAME_BULLET_2 ":/res/Bullet_2.png"//不知名弹幕
//#define GAME_BULLET_3 ":/res/Bullet_3.png"//红色弹幕
//#define GAME_BULLET_4 ":/res/Bullet_4.png"//黄色弹幕
//#define GAME_BULLET_5 ":/res/Bullet_5.png"//彩色弹幕
//#define GAME_BULLET_6 ":/res/Bullet_6.png"//星星弹幕
#define GAME_BULLET_ROTATE_TIME 5//弹幕旋转强度
#define GAME_BULLET_NEWENEMYBULLET_TIME 10//敌人弹幕刷新速度
#define GAME_BULLET_NEWBOSSBULLET_TIME 1//Boss弹幕刷新速度
#define GAME_BULLET_SPEED_1 8//hero弹幕默认步长
#define GAME_BULLET_SPEED_2 1//enemy弹幕默认步长
#define GAME_BULLET_SPEED_3 1//boss弹幕默认步长
#define GAME_BULLET_NUM_HERO 400//hero弹幕数量

#define GAME_BULLET_NUM_3 300//敌人弹幕数量
#define GAME_BULLET_NUM_4 500//boss弹幕数量


//Boss类
#define GAME_BOSS_BLUE_WAY ":/res/BluePerson.png"//boos_1
#define GAME_BOSS_BLUE_WAY2 ":/res/BluePerson2.png"//boss_1_2
#define GAME_BOSS_BLACK_WAY ":/res/Madwitch.png"//boss_2
#define GAME_BOSS_RECT 30//判定半径
#define GAME_BOSS_ADDSPEED 10//贴图刷新速度
#define GAME_BOSS_SENDBULLET_TIME 10//派出弹幕强度
#define GAME_BOSS_MOVE_TIME 20//ms

//爆炸类
#define GAME_BOOM_WAY ":/res/bomb-%1.png"
#define GAME_BOOM_NUM 3//一次爆炸PNG数量
#define GAME_BOOM_ADDSPEED 10//贴图刷新速度
#define GAME_BOOM_MAXNUM 300//最大爆炸数量

//特效类
#define GAME_SPECIAL_WAY_1 ":/res/specially_1.png"
#define GAME_SPECIAL_ADDSPEED_1 10//特效刷新速度

//掉落类
#define GAME_PROP_NUM 20//最大掉落数量

//绘图类
#define GAME_PAINTER_TIME 16//ms绘图频率










