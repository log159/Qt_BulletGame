#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{

}
void Widget::initWidget()
{
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    this->m_BoomPtr=new Boom[GAME_BOOM_MAXNUM];
    srand((unsigned)time(NULL));
    this->m_SidebarPtr=new SidebarWidget;
    m_SidebarPtr->setParent(this);
    m_SidebarPtr->move(GAME_WIDTH,0);
    m_SidebarPtr->show();
    /*---------------所有的计时器连接信号槽-----------------------*/
    m_HeroTimerUp=new QTimer(this);
    m_HeroTimerLeft=new QTimer(this);
    m_HeroTimerDown=new QTimer(this);
    m_HeroTimerRight=new QTimer(this);
    m_HeroSendBullet=new QTimer(this);
    m_HeroTimerBoom=new QTimer(this);

    m_RotateTimer=new QTimer(this);
    m_Timer=new QTimer(this);//默认刷新
    m_PaintTimer=new QTimer(this);//绘图计时器
    //额外类计时器
    enemySendTimer=new QTimer(this);//敌人派出
    enemyButSendTimer=new QTimer(this);//敌人弹幕派出
    enemyButNewTimer=new QTimer(this);//敌人弹幕刷新
    enemyNewTimer=new QTimer(this);//敌人位移和形态改变
    bossButSendTimer=new QTimer(this);//Boss派出弹幕强度计时器
    bossButNewTimer=new QTimer(this);//Boss更新弹幕强度计时器
    bossNewTimer=new QTimer(this);//Boss位移更新计时器

    //英雄刷新位置
     connect(this->m_HeroTimerUp,&QTimer::timeout,this,&Widget::keyHero);
     connect(this->m_HeroTimerLeft,&QTimer::timeout,this,&Widget::keyHero);
     connect(this->m_HeroTimerDown,&QTimer::timeout,this,&Widget::keyHero);
     connect(this->m_HeroTimerRight,&QTimer::timeout,this,&Widget::keyHero);
     connect(this->m_HeroTimerBoom,&QTimer::timeout,[=](){
         static int add=0;++add;if(add>=50){add=0;this->m_HeroTimerBoom->stop();this->m_Hero->m_CanSendBoom=true;m_Hero->m_Harm=true;}
         this->m_Hero->sendBoom();
     });
    //英雄派出子弹
    connect(this->m_HeroSendBullet,&QTimer::timeout,this,&Widget::keyHeroBullet);
    //全局绘图计时器
    connect(this->m_PaintTimer,&QTimer::timeout,[=](){this->update();});
    //旋转弹幕绘图角度回归计时器
    connect(m_RotateTimer,&QTimer::timeout,[=](){
        if((this->imageRotate+=20) == 360){this->imageRotate = 0;}
        if((this->imageRotateSmall++)==360){this->imageRotateSmall=0;}
    });
    //游戏默认刷新计时器
    connect(this->m_Timer,&QTimer::timeout,this,&Widget::gamePlay);//默认刷新
    //出怪计时器
    connect(this->enemySendTimer,&QTimer::timeout,this,&Widget::sendEnemyTimer);//敌人派出
    //敌人弹幕派出速度计时器
    connect(this->enemyButSendTimer,&QTimer::timeout,this,&Widget::sendEnemyBulletTimer);//敌人弹幕派出
    //敌人弹幕刷新速度计时器
    connect(this->enemyButNewTimer,&QTimer::timeout,this,&Widget::newEnemyBulletTimer);//敌人弹幕刷新
    //敌人位移和形态刷新速度计时器
    connect(this->enemyNewTimer,&QTimer::timeout,this,&Widget::newEnemyTimer);//敌人位移和形态改变
    //Boss弹幕派出速度计时器
    connect(this->bossButSendTimer,&QTimer::timeout,this,&Widget::sendBossBulletTimer);//Boss派出弹幕
    //Boss弹幕刷新速度计时器
    connect(this->bossButNewTimer,&QTimer::timeout,this,&Widget::newBossBulletTimer);//Boss弹幕位置更新
    //Boss位移更新计时器
    connect(this->bossNewTimer,&QTimer::timeout,this,&Widget::newBossTimer);//Boss位移形态更新

    //帧率统计
    connect(this->m_SidebarPtr->m_TimerFps,&QTimer::timeout,[=](){
        if(this->m_SidebarPtr->m_TimeHave->elapsed()-this->m_SidebarPtr->lastTime>1000)
        {
            this->m_SidebarPtr->lastTime=this->m_SidebarPtr->m_TimeHave->elapsed();
            this->m_SidebarPtr->m_FpsLab->setText("fps "+QString::number((double)this->m_SidebarPtr->m_Fps*0.5));
            this->m_SidebarPtr->m_Fps=0;
        }
    });


    this->startAllTime();
    //全局焦点
    setFocusPolicy(Qt::NoFocus);
}

void Widget::startAllTime()
{
    /*---------------所有需要的计时器开始发出信号-----------------------*/
    this->m_PaintTimer->start(int(GAME_PAINTER_TIME));//全局绘图
    this->m_RotateTimer->start(int(GAME_BULLET_ROTATE_TIME));//旋转类弹幕旋转强度计时器
    this->m_Timer->start(int(GAME_TIME));//全局默认刷新计时器
    this->enemySendTimer->start(int(GAME_ENEMY_SEND_TIME));//派出敌人的计时器
    this->enemyButSendTimer->start(int(GAME_ENEMY_SENDBULLET));//敌人派出弹幕强度函数计时器
    this->enemyButNewTimer->start(int(GAME_BULLET_NEWENEMYBULLET_TIME));//敌人弹幕刷新强度函数计时器
    this->enemyNewTimer->start(int(GAME_ENEMY_TIME));//敌人位移和形态改变
    //this->bossButSendTimer.start(int(GAME_BOSS_SENDBULLET_TIME));//Boss派出弹幕强度计时器
    //this->bossButNewTimer.start(int(GAME_BULLET_NEWBOSSBULLET_TIME));//Boss更新弹幕强度计时器
    //this->bossNewTimer.start(int(GAME_BOSS_MOVE_TIME));//Boss位移形态更新计时器
}

void Widget::stopAllTime()
{

    /*---------------所有需要的计时器停止发出信号-----------------------*/
    //this->m_PaintTimer.stop();//全局绘图
    //this->m_RotateTimer->stop();//旋转类弹幕旋转强度计时器
    //this->m_Timer.stop();//全局默认刷新计时器
    this->enemySendTimer->stop();//派出敌人的计时器
    this->enemyButSendTimer->stop();//敌人派出弹幕强度函数计时器
    this->enemyButNewTimer->stop();//敌人弹幕刷新强度函数计时器
    this->enemyNewTimer->stop();//敌人位移和形态改变
    this->bossButSendTimer->stop();//Boss派出弹幕强度计时器
    this->bossButNewTimer->stop();//Boss更新弹幕强度计时器
    this->bossNewTimer->stop();//Boss位移形态更新计时器
}

void Widget::gamePlay()
{
        this->m_Map->newMap();
        this->m_Hero->newBullet();
        this->m_Hero->timeNewHero();
        this->newBoom();
        if(theTime==1)
        {
            //this->heroOverE();
            this->enemyOver();
            this->propOver();
            int ex=-100,ey=-100;
            double er=1000.f;
            for(int i=0;i<int(GAME_ENEMY_NUM);++i)
            {
                (m_Enemy+i)->m_HX=m_Hero->m_X;
                (m_Enemy+i)->m_HY=m_Hero->m_Y;
                if((m_Enemy+i)->m_Free==false)
                {
                    double newR=MathFunc().getR((m_Enemy+i)->m_X,(m_Enemy+i)->m_Y,m_Hero->m_X,m_Hero->m_Y);
                    if(newR<er)
                    {
                        er=newR;
                        ex=(m_Enemy+i)->m_X;
                        ey=(m_Enemy+i)->m_Y;
                    }
                }
            }
            this->m_Hero->m_EX=ex;
            this->m_Hero->m_EY=ey;
        }
        else if(theTime==2)
        {
            //this->heroOverB();
            this->bossOver();
            this->m_Boss->getHeroLocation(m_Hero->m_X,m_Hero->m_Y);
            this->m_Hero->m_EX=m_Boss->m_X;
            this->m_Hero->m_EY=m_Boss->m_Y;

        }
        this->m_SidebarPtr->m_TimeWhere->setText(QString::number(this->m_SidebarPtr->m_TimeHave->elapsed())+" ms");

}

void Widget::sendEnemyBulletTimer()
{
    //敌人派出弹幕===============================================================================
        for(int i=0;i<int(GAME_ENEMY_NUM);i++)
            if((m_Enemy+i)->m_Free==false)
                (m_Enemy+i)->sendBullet();
}
void Widget::newEnemyBulletTimer()
{
    //更新敌人弹幕=================================================================================
        for(int i=0;i<int(GAME_ENEMY_NUM);i++)
            (m_Enemy+i)->newBullet();
}
void Widget::newEnemyTimer()
{
    //更新敌人位移数据 和 形态数据==============================================================

        for(int i=0;i<int(GAME_ENEMY_NUM);++i)
            if((m_Enemy+i)->m_Free==false)
                (m_Enemy+i)->newEnemy();
}
void Widget::sendBossBulletTimer()
{
    if(m_Boss->m_Harm)
    {
        m_Boss->nextBullet();
        m_Boss->sendBullet();
    }
}
void Widget::newBossBulletTimer()
{
    if(m_Boss->m_Harm)
        m_Boss->newBullet();
}
void Widget::newBossTimer()
{
    m_Boss->goMove();
    m_Boss->newBoss();
}
//———————————————————————————————————————————

void Widget::sendBoom(int x,int y)
{
    for(int k=0;k<int(GAME_BOOM_MAXNUM);k++)
    {
        if((m_BoomPtr+k)->m_Free)
        {
            (m_BoomPtr+k)->m_Free=false;
            (m_BoomPtr+k)->m_X=x;
            (m_BoomPtr+k)->m_Y=y;
            break;
        }
    }
}

void Widget::enemyOver()
{
    HeroBullet*but=m_Hero->m_HeroBulletArr;
    Enemy*en=m_Enemy;
    for(int i=0;i<int(GAME_BULLET_NUM_HERO);i++)
    {
        if((but+i)->m_Free)
            continue;
        for(int j=0;j<int(GAME_ENEMY_NUM);j++)
        {
            if((en+j)->m_Free)
                continue;
            if((but+i)->m_Circular.intersects((en+j)->m_Circular))
            {
                (but+i)->m_Free=true;
                (but+i)->release();
                --(en+j)->m_Hp;
                if((en+j)->m_Hp<=0)
                {
                    this->m_SidebarPtr->addScore(0);

                    sendBoom((en+j)->m_X,(en+j)->m_Y);
                    (en+j)->endSendBullet();
                    (en+j)->m_Free=true;
                    (en+j)->release();
                }
            }
        }
    }
}

//============================================================================================================================================
void Widget::heroOverE()
{
    if(m_Hero->m_Harm==false){return;}
    //怪的判定
    Enemy*en=m_Enemy;
    for(int i=0;i<GAME_ENEMY_NUM;i++)
    {
        if((en+i)->m_Free)
            continue;
        if((en+i)->m_Circular.intersects(m_Hero->m_Circular))
        {
            --m_Hero->m_Hp;
            this->m_SidebarPtr->setHpLab(m_Hero->m_Hp);
            this->m_Hero->harmOver();
            if(m_Hero->m_Hp<0){gameOver();}
            return;
        }
    }
    //怪的弹幕判定
    EnemyBullet*but=nullptr;
    for(int i=0;i<GAME_ENEMY_NUM;i++)
    {
        but=(en+i)->m_EnemyBulletArr;

        for(int j=0;j<GAME_BULLET_NUM_3;j++)
        {
            if((but+j)->m_Free==false)
            {
                if((but+j)->m_Circular.intersects(m_Hero->m_Circular))
                {
                    (but+j)->release();
                    --m_Hero->m_Hp;
                    this->m_SidebarPtr->setHpLab(m_Hero->m_Hp);
                    this->m_Hero->harmOver();
                    if(m_Hero->m_Hp<0){gameOver();}
                    return;
                }
            }
        }

    }

}

void Widget::heroOverB()
{

    if(m_Hero->m_Harm==false){return;}
    for(int i=0;i<int(GAME_BULLET_NUM_4);i++)
    {
        if((m_Boss->m_BossBulletArr+i)->m_Free==false)
        {
            if((m_Boss->m_BossBulletArr+i)->m_Circular.intersects(m_Hero->m_Circular))
            {
                --m_Hero->m_Hp;
                (m_Boss->m_BossBulletArr+i)->release();
                this->m_SidebarPtr->setHpLab(m_Hero->m_Hp);
                this->m_Hero->harmOver();
                if(m_Hero->m_Hp<0){gameOver();}
                return;
            }
        }
    }


}

void Widget::sendBoss()
{
    //==================================================================
    theTime=2;//Boss时间
    //停止对其他敌人的派出和刷新
    this->enemySendTimer->stop();//派出敌人的计时器 停止
    this->enemyButSendTimer->stop();//敌人派出弹幕强度函数计时器
    this->enemyButNewTimer->stop();//敌人弹幕刷新强度函数计时器
    this->enemyNewTimer->stop();//敌人位移和形态改变
    m_Boss->m_Free=false;//派出Boss
    this->bossButSendTimer->start(int(GAME_BOSS_SENDBULLET_TIME));//Boss派出弹幕强度计时器
    this->bossButNewTimer->start(int(GAME_BULLET_NEWBOSSBULLET_TIME));//Boss更新弹幕强度计时器
    this->bossNewTimer->start(int(GAME_BOSS_MOVE_TIME));//Boss位移形态更新计时器
    QTimer::singleShot(7000,this,[=](){m_Boss->m_Harm=true;});//正式开始
}

void Widget::newBoss()
{
    if(m_Boss->m_Free)
        return;
    m_Boss->newBoss();
}

void Widget::bossOver()
{
    if(m_Boss->m_Free)
        return;
    if(m_Boss->m_Harm==false)
        return;
    HeroBullet*but=m_Hero->m_HeroBulletArr;
    for(int i=0;i<int(GAME_BULLET_NUM_HERO);i++)
    {
        if((but+i)->m_Free)
            continue;
        if((but+i)->m_Circular.intersects(m_Boss->m_Circular)){
            --m_Boss->m_Hp;
            (but+i)->m_Free=true;
            (but+i)->release();
        }
    }
    if(m_Boss->m_Hp<=0)
    {
        //boss回收所有弹幕
        for(int i=0;i<int(GAME_BULLET_NUM_4);i++)
        {
            if(m_Boss->m_BossBulletArr[i].m_Free==false)
            {
                m_Boss->m_BossBulletArr[i].m_Free=true;
                sendBoom(m_Boss->m_BossBulletArr[i].m_X,m_Boss->m_BossBulletArr[i].m_Y);
            }
        }
        this->m_SidebarPtr->addScore(1);
        ++m_Boss->m_It;
        if(m_Boss->m_It>=m_Boss->v_Hp.size())
            this->gameWin();
        else
            m_Boss->m_Hp=m_Boss->v_Hp[m_Boss->m_It];
    }
}

void Widget::propOver()
{
    //怪的弹幕判定
    Prop*pr=nullptr;
    for(int i=0;i<GAME_ENEMY_NUM;++i)
    {
        pr=(m_Enemy+i)->m_Prop;

        for(int j=0;j<GAME_PROP_NUM;++j)
        {
            if((pr+j)->m_Free==false)
            {
                if((pr+j)->m_Circular.intersects(m_Hero->m_Circular))
                {
                    if((pr+j)->id==0)//红
                        m_Hero->m_RedNum+=5;
                    else if((pr+j)->id==1)//大红
                        m_Hero->m_RedNum+=10;
                    else if((pr+j)->id==2)//蓝
                        m_Hero->m_BlueNum+=10;
                    if(m_Hero->m_RedNum>400)
                        m_Hero->m_RedNum=400;
                    this->m_SidebarPtr->setMana(m_Hero->m_RedNum);
                    this->m_SidebarPtr->setCount(m_Hero->m_BlueNum);
                    (pr+j)->m_Free=true;
                    (pr+j)->release();


                }
            }
        }

    }
}

void Widget::keyHero()
{
    m_Hero->keyNewHero();
}

void Widget::keyHeroBullet()
{
    m_Hero->sendBullet();
}

void Widget::gameOver()
{
    QTimer::singleShot(3000,this,[=](){
        this->stopAllTime();
        this->m_PaintTimer->stop();//全局绘图
        this->m_Timer->stop();//全局默认刷新计时器
        sendEndLabel(0);
        QTimer::singleShot(3000,this,[=](){
            theTime=0;
            emit quit();

        });

    });
}

void Widget::gameWin()
{
    m_Boss->newBoss();
    m_Boss->m_Harm=false;
    m_Boss->endGoto();
    this->bossButSendTimer->stop();//Boss派出弹幕强度计时器
    //boss回收所有弹幕
    for(int i=0;i<int(GAME_BULLET_NUM_4);i++)
    {
        if(m_Boss->m_BossBulletArr[i].m_Free==false)
        {
            m_Boss->m_BossBulletArr[i].m_Free=true;
            sendBoom(m_Boss->m_BossBulletArr[i].m_X,m_Boss->m_BossBulletArr[i].m_Y);
        }
    }
    sendEndLabel(1);
    QTimer::singleShot(7000,this,[=](){
        this->stopAllTime();
        theTime=0;
        emit quit();

    });
}

void Widget::sendEndLabel(int id)
{
    QLabel * m_Label=new QLabel(this);
    m_Label->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    m_Label->move(0,0);
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(50);
    m_Label->setFont(font);
    m_Label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    m_Label->setAttribute(Qt::WA_TransparentForMouseEvents);//鼠标穿透效果
    QPalette pe;
    if(id==0)
    {
        //红色
        pe.setColor(QPalette::WindowText,Qt::red);
        m_Label->setPalette(pe);
        m_Label->setText("GAME OVER");
    }
    else if(id==1)
    {
        //绿色
        pe.setColor(QPalette::WindowText,Qt::green);
        m_Label->setPalette(pe);
        m_Label->setText("GAME WIN");
    }

    m_Label->show();
}

void Widget::newBoom()
{
    for(int k=0;k<(int(GAME_BOOM_MAXNUM));k++)
        if((m_BoomPtr+k)->m_Free==false)
            (m_BoomPtr+k)->newBoom();
}

void Widget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    ++this->m_SidebarPtr->m_Fps;//统计fps

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    paintMap(&painter);
    paintHero(&painter);
    paintEnemy(&painter);
    paintBoss(&painter);
    paintBoom(&painter);


    //特殊绘图操作——0
    if(printId==0)
    {
    }
    //特殊绘图效果——1
    else if(printId==1)
    {
        static bool the=true;
        static int add=0;

        static double rx=(double)m_Hero->m_X;
        static double ry=(double)m_Hero->m_Y;

        static double r1=0;
        static double r2=0;
        static double r3=0;
        static double r4=0;
        static QColor tmpCol;

        QImage image(QSize(544,544),QImage::Format_ARGB32);
        QPainter painter2(&image);
        painter2.setRenderHint(QPainter::Antialiasing);
        paintMap(&painter2);
        paintHero(&painter2);
        paintEnemy(&painter2);
        paintBoss(&painter2);
        paintBoom(&painter2);

        if(the){
            rx=(double)m_Hero->m_X;
            ry=(double)m_Hero->m_Y;
            r1=r2=r3=r4=0.f;
            the=false;
        }

        for(int i=0;i<544;++i)
        {
            for(int j=0;j<544;++j)
            {
                bool t=true;

                int tempX=j-rx;
                int tempY=i-ry;
                if(tempX<0){tempX=-tempX;}
                if(tempY<0){tempY=-tempY;}
                int R=(int)sqrt(double(tempX*tempX+tempY*tempY));
                if(r1>R){t=!t;}

                if(r2>R){t=!t;}
                if(r3>R){t=!t;}
                if(r4>R){t=!t;}

                if(r2!=0.f&&r3!=0.f){

                    double c=acos(-1)/4;
                    double TR=((j-rx)*cos(c)-(i-ry)*sin(c))*((j-rx)*cos(c)-(i-ry)*sin(c))*r3*r3+((j-rx)*sin(c)+(i-ry)*cos(c))*((j-rx)*sin(c)+(i-ry)*cos(c))*r2*r2;
                    if(TR<=r2*r2*r3*r3)
                        t=!t;
                    c=acos(-1)/4*3;
                    TR=((j-rx)*cos(c)-(i-ry)*sin(c))*((j-rx)*cos(c)-(i-ry)*sin(c))*r3*r3+((j-rx)*sin(c)+(i-ry)*cos(c))*((j-rx)*sin(c)+(i-ry)*cos(c))*r2*r2;
                    if(TR<=r2*r2*r3*r3)
                        t=!t;
                }
                tmpCol=QColor(image.pixel(j,i));
                if(t)
                {
                }
                else
                {
                    tmpCol.setRed(255-tmpCol.red());
                    tmpCol.setGreen(255-tmpCol.green());
                    tmpCol.setBlue(255-tmpCol.blue());
                }

                image.setPixel(j,i,qRgb(tmpCol.red(),tmpCol.green(),tmpCol.blue()));
            }
        }
        QPainter painter3(this);
        painter3.drawPixmap(0,0,QPixmap::fromImage(image));
        ++add;
        if(r1<1000){if(add>=0){r1+=70.f;}}
        if(r2<1000){if(add>=5){r2+=50.f;}}
        if(r3<1000){if(add>=6){r3+=50.f;}}
        if(r4<1000){if(add>=8){r4+=40.f;}}
        if(add>=20){add=0;printId=0;the=true;}
    }
}

void Widget::paintMap(QPainter *painter)
{
    //地图绘图
    painter->drawPixmap(0,m_Map->m_Y1,m_Map->m_image1);
    painter->drawPixmap(0,m_Map->m_Y2,m_Map->m_image2);
}

void Widget::paintHero(QPainter *painter)
{
    //英雄绘图

    painter->setClipRect(m_Hero->m_X-m_Hero->m_Width/2,m_Hero->m_Y-m_Hero->m_Height/2,m_Hero->m_Width,m_Hero->m_Height);

    //qDebug()<<QString::number(m_Hero->m_PrintId);
    if(m_Hero->m_PrintId==0)
    {
        if(m_Hero->isKorShift==false)
            painter->drawPixmap(m_Hero->m_PrintX,m_Hero->m_PrintY,m_Hero->m_image);
        else
            painter->drawPixmap(m_Hero->m_PrintX,m_Hero->m_PrintY,m_Hero->m_image_);
    }
    else if(m_Hero->m_PrintId==1)
    {
        printId=1;
        static int addNext=0;
        ++addNext;
        if(addNext>=20){
            addNext=0;
            m_Hero->m_PrintId=2;
            m_Hero->m_X=int(GAME_WIDTH)/2;
            m_Hero->m_Y=int(GAME_HEIGHT)-m_Hero->m_image.height()/4;
        }
    }
    else if(m_Hero->m_PrintId==2)
    {
        this->m_Hero->m_CanSendBoom=false;
        this->m_Hero->m_BombNum=3;
        this->m_SidebarPtr->setBombLab(m_Hero->m_BombNum);
        static int addNext=0;
        ++addNext;
        if(addNext>=300){
            addNext=0;
            m_Hero->comingReturn();
        }
        static int add=0;
        ++add;
        if(add>=3){
            add=0;
            if(m_Hero->isKorShift==false)
                painter->drawPixmap(m_Hero->m_PrintX,m_Hero->m_PrintY,m_Hero->m_image);
            else
                painter->drawPixmap(m_Hero->m_PrintX,m_Hero->m_PrintY,m_Hero->m_image_);
        }
    }

    painter->setClipRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    //英雄弹幕绘图
    painter->save();
    HeroBullet*but=m_Hero->m_HeroBulletArr;
    for(int i=0;i<int(GAME_BULLET_NUM_HERO);i++)
    {
        if((but+i)->m_Free==false)
        {
            QTransform transform;
            transform.translate((but+i)->m_X,(but+i)->m_Y);
            transform.rotate((but+i)->m_Angle+90.f);
            transform.translate(-((but+i)->m_image.width()*0.5),-((but+i)->m_image.height()*0.5));
            painter->setTransform(transform);
            painter->drawPixmap(0,0,(but+i)->m_image);

        }
    }
    painter->restore();
}

void Widget::paintBoom(QPainter *painter)
{

    //爆炸绘图
    for(int i=0;i<GAME_BOOM_MAXNUM;i++)
        if((m_BoomPtr+i)->m_Free==false)
            painter->drawPixmap((m_BoomPtr+i)->m_X-(m_BoomPtr+i)->m_Xoffset,(m_BoomPtr+i)->m_Y-(m_BoomPtr+i)->m_Yoffset,(m_BoomPtr+i)->m_Vector[(m_BoomPtr+i)->m_TheNum]);
}

void Widget::paintEnemy(QPainter *painter)
{
    //敌人绘图
    if(this->theTime==1)
    {
        for(int i=0;i<int(GAME_ENEMY_NUM);++i)
        {
            if((m_Enemy+i)->m_Free==false)
            {
                painter->setClipRect((m_Enemy+i)->m_X-(m_Enemy+i)->m_Width*0.5,(m_Enemy+i)->m_Y-(m_Enemy+i)->m_Height*0.5,(m_Enemy+i)->m_Width,(m_Enemy+i)->m_Height);
                painter->drawPixmap((m_Enemy+i)->m_PrintX,(m_Enemy+i)->m_PrintY,(m_Enemy+i)->m_image);
            }
        }
        painter->setClipRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

        Prop*pr=nullptr;
        //敌人掉落绘图
        for(int i=0;i<GAME_ENEMY_NUM;++i)
        {
            pr=(m_Enemy+i)->m_Prop;
            for(int j=0;j<GAME_PROP_NUM;++j)
            {
                if((pr+j)->m_Free){continue;}
                painter->drawPixmap((pr+j)->m_X-(pr+j)->m_image.width()*0.5,(pr+j)->m_Y-(pr+j)->m_image.height()*0.5,(pr+j)->m_image);
            }

        }

        painter->save();

        EnemyBullet*but=nullptr;
        //敌人弹幕绘图
        for(int i=0;i<GAME_ENEMY_NUM;++i)
        {
            but=(m_Enemy+i)->m_EnemyBulletArr;
            if(but==nullptr){continue;}
            for(int j=0;j<GAME_BULLET_NUM_3;++j)
            {
                if((but+j)->m_Free){continue;}
                QTransform transform;
                transform.translate((but+j)->m_X,(but+j)->m_Y);
                
                //保持一个角度
                if((but+j)->m_PrintId==0)
                    transform.rotate((but+j)->m_Angle+90);
                //旋转显示效果——慢
                else if((but+j)->m_PrintId==1)
                    transform.rotate(imageRotateSmall);
                //旋转显示效果——快
                else if((but+j)->m_PrintId==2)
                    transform.rotate(imageRotate);
                
                transform.translate(-((but+j)->m_image.width()*0.5),-((but+j)->m_image.height()*0.5));
                painter->setTransform(transform);
                painter->drawPixmap(0,0,(but+j)->m_image);

            }
        }
        painter->restore();


    }
}

void Widget::paintBoss(QPainter *painter)
{
    //Boss绘图
    if(this->theTime==2)
    {
        painter->save();
         //boss特效绘图
         if(m_Boss->m_Harm)
         {
             QTransform transform;
             transform.translate(m_Boss->m_X,m_Boss->m_Y);
             transform.rotate(imageRotate);
             transform.translate(-m_Boss->m_SpecialRotate.m_Width/2,-m_Boss->m_SpecialRotate.m_Height/2);
             painter->setTransform(transform);
             painter->drawPixmap(0,0,m_Boss->m_SpecialRotate.m_image);
         }
         painter->restore();
         //Boss绘图
         if(m_Boss->m_Free==false)
         {
             painter->setClipRect(m_Boss->m_X-m_Boss->m_Width/2,m_Boss->m_Y-m_Boss->m_Height/2,m_Boss->m_Width,m_Boss->m_Height);
             painter->drawPixmap(m_Boss->m_PrintX,m_Boss->m_PrintY,m_Boss->m_image);
             painter->setClipRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
         }
         painter->save();
         //Boss弹幕绘图
         if(m_Boss->m_Harm)
         {
             //弹幕绘图
             for(int i=0;i<int(GAME_BULLET_NUM_4);i++)
             {
                 if(m_Boss->m_BossBulletArr[i].m_Free==false)
                 {
                     int tempX=m_Boss->m_BossBulletArr[i].m_X;
                     int tempY=m_Boss->m_BossBulletArr[i].m_Y;
                     QTransform transform;
                     transform.translate(tempX,tempY);
                     //保持一个角度
                     if(m_Boss->m_BossBulletArr[i].m_PrintId==1)
                         transform.rotate(m_Boss->m_BossBulletArr[i].m_Only_Angle);
                     //需要时刻旋转
                     else if(m_Boss->m_BossBulletArr[i].m_PrintId==2)
                         transform.rotate(imageRotateSmall);

                     transform.translate(-(m_Boss->m_BossBulletArr[i].m_Width/2),-(m_Boss->m_BossBulletArr[i].m_Height/2));
                     painter->setTransform(transform);
                     painter->drawPixmap(0,0,m_Boss->m_BossBulletArr[i].m_image);
                 }
             }

         }
         painter->restore();


         if(m_Boss->m_Harm)
         {
             painter->drawRect(m_Boss->m_Rect.m_X,m_Boss->m_Rect.m_Y,m_Boss->m_Rect.m_W,m_Boss->m_Rect.m_H);
             QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
             QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
             brush.setColor(QColor(0,255,0,120));
             brush.setStyle(Qt::SolidPattern);
             painter->setPen(pen);
             painter->setBrush(brush);
             painter->drawRect(m_Boss->m_RectHp.m_X,m_Boss->m_RectHp.m_Y,m_Boss->m_RectHp.m_W,m_Boss->m_RectHp.m_H);
             painter->drawText(int(GAME_WIDTH)/2-20,m_Boss->m_Rect.m_Y+10,QString("%1%").arg(m_Boss->m_Hphundred));
         }
    }
}
void Widget::keyPressEvent(QKeyEvent *event)//键盘事件
{

    //更新自机位置数据
    switch(event->key())
    {
    case Qt::Key_L:
    case Qt::Key_X:
        if(this->m_Hero->m_CanSendBoom)
        {
            m_Hero->m_BombNum-=1;
            if(m_Hero->m_BombNum<0){m_Hero->m_BombNum=-1;break;}
            else{m_SidebarPtr->setBombLab(m_Hero->m_BombNum);}
            m_Hero->m_Harm=false;
            m_HeroTimerBoom->start(100);
            this->m_Hero->m_CanSendBoom=false;
        }
        break;
    //慢速
    case Qt::Key_Shift:
    case Qt::Key_K:m_Hero->m_theAdd=12.f;m_Hero->isKorShift=true;m_Hero->m_FocusNum=true;break;

    case Qt::Key_Up:
    case Qt::Key_W:
        m_Hero->m_Down=false;
        this->m_Hero->m_Up=true;
        this->m_Hero->m_isUp=true;
        this->m_HeroTimerUp->start(m_Hero->m_KeySpeed);break;
    case Qt::Key_Left:
    case Qt::Key_A:
        m_Hero->m_Right=false;
        this->m_Hero->m_Left=true;
        this->m_Hero->m_isLeft=true;
        this->m_HeroTimerLeft->start(m_Hero->m_KeySpeed);break;
    case Qt::Key_Down:
    case Qt::Key_S:
        m_Hero->m_Up=false;
        this->m_Hero->m_Down=true;
        this->m_Hero->m_isDown=true;
        this->m_HeroTimerDown->start(m_Hero->m_KeySpeed);break;
    case Qt::Key_Right:
    case Qt::Key_D:
        m_Hero->m_Left=false;
        this->m_Hero->m_Right=true;
        this->m_Hero->m_isRight=true;
        this->m_HeroTimerRight->start(m_Hero->m_KeySpeed);break;
    case Qt::Key_Z:
    case Qt::Key_J:
        //英雄派出子弹
        this->m_Hero->sendBullet();
        this->m_HeroSendBullet->start(GAME_HERO_SENDBULLET_TIME);break;
    default:break;
    }
}
void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W||event->key()==Qt::Key_Up)
    {
        m_Hero->m_Up=false;
        m_Hero->m_isUp=false;
        if(m_Hero->m_isDown)
            m_Hero->m_Down=true;
    }
    if(event->key()==Qt::Key_A||event->key()==Qt::Key_Left)
    {
        m_Hero->m_Left=false;
        m_Hero->m_isLeft=false;
        if(m_Hero->m_isRight)
            m_Hero->m_Right=true;
    }
    if(event->key()==Qt::Key_S||event->key()==Qt::Key_Down)
    {
        m_Hero->m_Down=false;
        m_Hero->m_isDown=false;
        if(m_Hero->m_isUp)
            m_Hero->m_Up=true;
    }
    if(event->key()==Qt::Key_D||event->key()==Qt::Key_Right)
    {
        m_Hero->m_Right=false;
        m_Hero->m_isRight=false;
        if(m_Hero->m_isLeft)
            m_Hero->m_Left=true;
    }

    if(event->key()==Qt::Key_J||event->key()==Qt::Key_Z)
        this->m_HeroSendBullet->stop();

    if(event->key()==Qt::Key_K||event->key()==Qt::Key_Shift)
    {
        m_Hero->m_theAdd=5.f;
        m_Hero->isKorShift=false;
        m_Hero->m_FocusNum=false;
    }
}
Widget::~Widget()
{
    delete m_Map;
    delete m_Hero;
    delete m_Boss;
    delete enSendWay;
    delete[] m_Enemy;
    delete[] m_BoomPtr;
    delete m_SidebarPtr;
}
