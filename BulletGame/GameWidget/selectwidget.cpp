#include "selectwidget.h"

SelectWidget::SelectWidget(QWidget *parent) : QWidget(parent)
{
    //窗口设置
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);//宽高
    //背景设置
    this->backgroundPtr=new Map(":/res/Map_3.png");
    this->backgroundPtr2=new Map(":/res/Map_3.png");

    //计时器
    this->timerPtr=new QTimer(this);
     connect(this->timerPtr,&QTimer::timeout,[=](){
         backgroundPtr->newMap();
         update();
     });

     for(int i=0;i<=maxId;++i)
     {
         MyLabel * lab=new MyLabel("第 "+QString::number(i+1)+" 关",20);
         lab->setParent(this);
         lab->setFixedSize(180,80);
         lab->move(15,i*lab->height()+5);
         lab->show();
         v_Lab.push_back(lab);
     }
     this->v_Img.push_back(QPixmap(":/res/Map_1.png"));
     this->v_Img.push_back(QPixmap(":/res/Map_2.png"));


     v_Lab.at(0)->setPressStyle();


}


void SelectWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.drawPixmap(0,backgroundPtr->m_Y1,backgroundPtr->m_image1);
    painter.drawPixmap(0,backgroundPtr->m_Y2,backgroundPtr->m_image2);
    painter.drawPixmap(backgroundPtr->m_image1.width(),backgroundPtr->m_Y1,backgroundPtr2->m_image1);
    painter.drawPixmap(backgroundPtr->m_image2.width(),backgroundPtr->m_Y2,backgroundPtr2->m_image2);

    painter.drawPixmap(300,50,WINDOW_WIDTH-300-50,WINDOW_HEIGHT-100,v_Img.at(selectId));
}

void SelectWidget::keyPressEvent(QKeyEvent *e)
{
     if(e->key()==Qt::Key_Return||e->key()==Qt::Key_Z||e->key()==Qt::Key_J||e->key()==Qt::Key_Space)
     {
         timerPtr->stop();
         emit startGame(selectId);
     }
    if(e->key()==Qt::Key_Up){--selectId;}
    if(e->key()==Qt::Key_Down){++selectId;}
    if(selectId<0){selectId=maxId;}
    if(selectId>maxId){selectId=0;}
    for(int i=0;i<v_Lab.size();++i)
    {
        if(selectId==i){
            v_Lab[i]->setPressStyle();
            continue;
        }
        v_Lab[i]->setReleaseStyle();
    }
}
SelectWidget::~SelectWidget()
{
    delete backgroundPtr;
    delete backgroundPtr2;
}
