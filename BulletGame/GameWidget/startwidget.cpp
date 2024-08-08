#include "startwidget.h"

StartWidget::StartWidget(QWidget *parent) : QWidget(parent)
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

     this->timerPress=new QTimer(this);
     connect(timerPress,&QTimer::timeout,[=](){
         animationLabel();
     });

     //帮助图
     this->helpLab=new QLabel(this);
     this->helpLab->setPixmap(QPixmap(":/res/Help.png"));
     this->helpLab->move(-10,-30);
     this->helpLab->hide();

     MyLabel * startPtr=new MyLabel("S T A R T",30);
     startPtr->setParent(this);
     startPtr->setFixedSize(400,90);
     startPtr->move((WINDOW_WIDTH-startPtr->width())*0.5,100+30);
     v_Lab.push_back(startPtr);

     MyLabel * helpPtr=new MyLabel("H E L P",30);
     helpPtr->setParent(this);
     helpPtr->setFixedSize(400,90);
     helpPtr->move((WINDOW_WIDTH-helpPtr->width())*0.5,200+30);
     v_Lab.push_back(helpPtr);

     MyLabel * quitPtr=new MyLabel("Q U I T",30);
     quitPtr->setParent(this);
     quitPtr->setFixedSize(400,90);
     quitPtr->move((WINDOW_WIDTH-quitPtr->width())*0.5,300+30);
     v_Lab.push_back(quitPtr);

     v_Lab[0]->setPressStyle();

     connect(this,&StartWidget::goQuit,[=](){
         exit(0);
     });

     connect(this,&StartWidget::goHelp,[=](){
         if(helpTime){
         for(int i=0;i<v_Lab.size();++i)
             v_Lab[i]->hide();
         helpLab->show();
         }
         else
         {
             for(int i=0;i<v_Lab.size();++i)
                 v_Lab[i]->show();
             helpLab->hide();
         }
     });
}
void StartWidget::animationLabel()
{
    static int i=5;
    static int leftOrRight=false;
    static int add=0;

    v_Lab[selectId]->move(initPoint.x()+i,initPoint.y());
    if(i>5)
        leftOrRight=false;
    else if(i<-5)
        leftOrRight=true;
    if(leftOrRight)
        ++i;
    else
        --i;
    ++add;
    if(add>=30){
        add=0;
        timerPress->stop();
        v_Lab[selectId]->move(initPoint.x(),initPoint.y());
    }
}

void StartWidget::initMoveLabel()
{
    v_Lab[0]->move((WINDOW_WIDTH-v_Lab[0]->width())*0.5,100+30);
    v_Lab[1]->move((WINDOW_WIDTH-v_Lab[1]->width())*0.5,200+30);
    v_Lab[2]->move((WINDOW_WIDTH-v_Lab[2]->width())*0.5,300+30);
}


void StartWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.drawPixmap(0,backgroundPtr->m_Y1,backgroundPtr->m_image1);
    painter.drawPixmap(0,backgroundPtr->m_Y2,backgroundPtr->m_image2);
    painter.drawPixmap(backgroundPtr->m_image1.width(),backgroundPtr->m_Y1,backgroundPtr2->m_image1);
    painter.drawPixmap(backgroundPtr->m_image2.width(),backgroundPtr->m_Y2,backgroundPtr2->m_image2);
}

void StartWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Return||e->key()==Qt::Key_Z||e->key()==Qt::Key_J||e->key()==Qt::Key_Space||e->key()==Qt::Key_Up||e->key()==Qt::Key_Down){

        if(e->key()==Qt::Key_Return||e->key()==Qt::Key_Z||e->key()==Qt::Key_J||e->key()==Qt::Key_Space){
            if(selectId==0){
                timerPtr->stop();
                emit goSelect();
            }
            else if(selectId==1){
                helpTime=!helpTime;
                emit goHelp();
            }
            else if(selectId==2){
                emit goQuit();
            }
        }
        if(helpTime){return;}
        if(e->key()==Qt::Key_Up){--selectId;}
        if(e->key()==Qt::Key_Down){++selectId;}
        if(selectId<0){selectId=maxId;}
        if(selectId>maxId){selectId=0;}
        this->initMoveLabel();
        for(int i=0;i<v_Lab.size();++i)
        {
            if(selectId==i){
                initPoint.setX(v_Lab[i]->x());
                initPoint.setY(v_Lab[i]->y());
                v_Lab[i]->setPressStyle();

                timerPress->start(5);

                continue;
            }
            v_Lab[i]->setReleaseStyle();
        }
    }

}

StartWidget::~StartWidget()
{
    delete backgroundPtr;
    delete backgroundPtr2;

}

