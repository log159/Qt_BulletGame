#include "sidebarwidget.h"

SidebarWidget::SidebarWidget(QWidget *parent) : QWidget(parent)
{
    m_TimeHave=new QTime;//计时
    m_TimerFps=new QTimer(this);//统计帧率的计时器

    /*-----------------------------------标签--------------------------------------*/

    //侧栏
    this->m_SidebarLabel=new QLabel(this);
    QPixmap m_SidebarImg;
    m_SidebarImg.load(WINDOW_SIDERBAR_WAY);
    this->m_SidebarLabel->setFixedSize(m_SidebarImg.width(),m_SidebarImg.height());
    this->m_SidebarLabel->setPixmap(m_SidebarImg);
    this->m_SidebarLabel->move(0,0);
    this->m_SidebarLabel->show();
    //版本信息
    this->m_Edition=new Edition;
    m_Edition->setParent(this);
    m_Edition->move(0,GAME_HEIGHT-m_Edition->height());
    m_Edition->show();
    //Palette
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(11);
    //阴影效果
    vEffect.reserve(5);
    for(int i=0;i<5;++i)
    {
        QGraphicsDropShadowEffect * effect=new QGraphicsDropShadowEffect;
        effect->setColor(QColor(255,255,255,100));
        effect->setBlurRadius(20);
        effect->setOffset(1);
        effect->setBlurRadius(10);
        vEffect.push_back(effect);
    }
    //-------------残机-----------------


    m_HpLabel=new QLabel(this);
    m_HpLabel->setText("残机");
    m_HpLabel->setGraphicsEffect(vEffect[0]);
    pe.setColor(QPalette::WindowText,QColor(255,0,120));
    m_HpLabel->setPalette(pe);
    m_HpLabel->setFont(font);
    m_HpLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_HpLabel->move(22,100);
    m_HpLabel->setFixedSize(160,60);
    m_HpLabel->show();


    for(int i=0;i<7;++i)
    {
        MyImgLabel*lab= new MyImgLabel(CutImg().getImg(2,8,1,0),CutImg().getImg(2,8,0,0));
        lab->setParent(this);
        lab->move(i*15+70,120);
        lab->setImg1();
        if(i>=3)
            lab->setImg2();
        lab->show();
        v_LabHp.push_back(lab);

    }


    //--------------符卡------------------
    m_BombLabel=new QLabel(this);
    m_BombLabel->setText("符卡");
    m_BombLabel->setGraphicsEffect(vEffect[1]);
    pe.setColor(QPalette::WindowText,QColor(20,200,10));
    m_BombLabel->setPalette(pe);
    m_BombLabel->setFont(font);
    m_BombLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_BombLabel->move(22,150);
    m_BombLabel->setFixedSize(160,60);
    m_BombLabel->show();

    for(int i=0;i<7;++i)
    {
        MyImgLabel*lab= new MyImgLabel(CutImg().getImg(2,8,5,0),CutImg().getImg(2,8,0,0));
        lab->setParent(this);
        lab->move(i*15+70,170);
        lab->setImg1();
        if(i>=3)
            lab->setImg2();
        lab->show();
        v_LabBomb.push_back(lab);

    }

    //-----------------灵力---------------------
    m_Mana=new QLabel(this);
    QString strMana="";
    strMana+="灵力  "+QString::number(m_RedNum/100)+"."+QString::number(m_RedNum/10%10)+QString::number(m_RedNum%10)+"/4.00";
    m_Mana->setText(strMana);
    m_Mana->setGraphicsEffect(vEffect[2]);
    pe.setColor(QPalette::WindowText,QColor(230,10,10));
    m_Mana->setPalette(pe);
    m_Mana->setFont(font);
    m_Mana->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_Mana->move(22,200);
    m_Mana->setFixedSize(160,60);
    m_Mana->show();

    //------------------点数-----------------------

    m_Count=new QLabel(this);
    m_Count->setText("点数  "+QString::number(m_BlueNum));
    m_Count->setGraphicsEffect(vEffect[3]);
    pe.setColor(QPalette::WindowText,QColor(0,10,250));
    m_Count->setPalette(pe);
    m_Count->setFont(font);
    m_Count->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_Count->move(22,250);
    m_Count->setFixedSize(160,60);
    m_Count->show();


    //-----------------得分------------------
    m_ScoreLab=new QLabel(this);
    m_ScoreLab->setText("得分  "+QString("0000000000"));
    m_ScoreLab->setGraphicsEffect(vEffect[4]);
    font.setFamily("黑体");
    font.setPointSize(10);
    pe.setColor(QPalette::WindowText,Qt::white);
    m_ScoreLab->setPalette(pe);
    m_ScoreLab->setFont(font);
    m_ScoreLab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_ScoreLab->move(22,50);
    m_ScoreLab->setFixedSize(160,60);

    //------------时间----------------
    m_TimeWhere=new QLabel(this);
    font.setFamily("黑体");
    font.setPointSize(7);
    pe.setColor(QPalette::WindowText,Qt::white);
    m_TimeWhere->setPalette(pe);
    m_TimeWhere->setFont(font);
    m_TimeWhere->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_TimeWhere->move(22,480);
    m_TimeWhere->setFixedSize(160,60);
    m_TimeWhere->show();

    //-------------帧率--------------------
    m_FpsLab=new QLabel(this);
    m_FpsLab->setText("fps "+QString::number(0));
    font.setFamily("黑体");
    font.setPointSize(8);
    pe.setColor(QPalette::WindowText,Qt::white);
    m_FpsLab->setPalette(pe);
    m_FpsLab->setFont(font);
    m_FpsLab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_FpsLab->move(22,480);
    m_FpsLab->setFixedSize(160,60);

    //计时
    this->m_TimeHave->start();
    this->m_TimerFps->start(10);

}


void SidebarWidget::addScore(int id)
{
    if(id==0)
        m_Score+=10+m_BlueNum;
    else if(id==1)
        m_Score+=1000+m_BlueNum*10;

    for(int i=0;i<10;++i)
    {
        int temp=1;
        for(int j=0;j<i;++j)
            temp*=10;
        m_ScoreArr[i]=m_Score/temp%10;
    }

    QString str;
    for(int i=9;i>=0;--i)
    {
        str+=QString::number(m_ScoreArr[i]);
    }
    m_ScoreLab->setText("得分  "+str);

}

void SidebarWidget::setMana(int num)
{
    m_RedNum=num;
    QString strMana="";
    strMana+="灵力  "+QString::number(m_RedNum/100)+"."+QString::number(m_RedNum/10%10)+QString::number(m_RedNum%10)+"/4.00";
    m_Mana->setText(strMana);

}

void SidebarWidget::setCount(int num)
{
    m_BlueNum=num;
    m_Count->setText("点数  "+QString::number(m_BlueNum));

}

SidebarWidget::~SidebarWidget()
{
    for(QVector<QGraphicsDropShadowEffect*>::iterator it=vEffect.begin();it!=vEffect.end();++it)
        delete (*it);
    delete m_TimeHave;
}

void SidebarWidget::setHpLab(int num)
{
    if(num<0){num=0;}
    for(QVector<MyImgLabel*>::iterator it=v_LabHp.begin();it!=v_LabHp.end();++it)
        (*it)->setImg2();
    for(int i=0;i<num;++i)
        v_LabHp.at(i)->setImg1();
}

void SidebarWidget::setBombLab(int num)
{
    if(num<0){num=0;}
    for(QVector<MyImgLabel*>::iterator it=v_LabBomb.begin();it!=v_LabBomb.end();++it)
        (*it)->setImg2();
    for(int i=0;i<num;++i)
        v_LabBomb.at(i)->setImg1();
}
