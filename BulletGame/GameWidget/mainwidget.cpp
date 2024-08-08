#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    //窗口设置
    this->setWindowIcon(QIcon(GAME_ICON));
    this->setWindowTitle(GAME_TEXT);
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);//宽高

    startWidgetPtr=new StartWidget(this);
    startWidgetPtr->show();
    startWidgetPtr->setFocus();
    startWidgetPtr->timerPtr->start(10);

    selectWidgetPtr=new SelectWidget(this);
    selectWidgetPtr->hide();

    connect(startWidgetPtr,&StartWidget::goSelect,[=](){
        startWidgetPtr->hide();
        startWidgetPtr->timerPtr->stop();

        selectWidgetPtr->show();
        selectWidgetPtr->setFocus();
        selectWidgetPtr->timerPtr->start(10);

    });

    connect(selectWidgetPtr,&SelectWidget::startGame,[=](int id){
        if(id==0){gameWidgetPtr=new GameWidget_1;}
        else if(id==1){gameWidgetPtr=new GameWidget_2;}
        if(gameWidgetPtr==nullptr){qDebug()<<"null ptr in mainwidget connect";}
        gameWidgetPtr->setParent(this);
        selectWidgetPtr->hide();
        selectWidgetPtr->timerPtr->stop();
        gameWidgetPtr->show();
        gameWidgetPtr->setFocus();
        connect(gameWidgetPtr,&Widget::quit,[=](){
            gameWidgetPtr->hide();
            delete gameWidgetPtr;
            gameWidgetPtr=nullptr;
            startWidgetPtr->show();
            startWidgetPtr->setFocus();
            startWidgetPtr->timerPtr->start(10);
        });
    });

}

MainWidget::~MainWidget()
{

}


