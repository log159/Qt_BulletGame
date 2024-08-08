#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QGraphicsDropShadowEffect>

#include "Others/edition.h"
#include "Config/cutimg.h"
#include "Others/myimglabel.h"

class SidebarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SidebarWidget(QWidget *parent = nullptr);
    ~SidebarWidget();

    void setHpLab(int num);

    void setBombLab(int num);

    void addScore(int id);

    void setMana(int num);

    void setCount(int num);

private:
    QVector<QGraphicsDropShadowEffect*>vEffect;

    short m_ScoreArr[10]={0};
    QVector<MyImgLabel*>v_LabHp;
    QVector<MyImgLabel*>v_LabBomb;


    int m_RedNum=0;
    int m_RedNumMax=400;
    int m_BlueNum=0;



public:
    //非关卡显示类
    Edition * m_Edition;//版本信息
    QLabel * m_SidebarLabel;//边栏框
    QLabel * m_HpLabel;//显示残机
    QLabel * m_BombLabel;//显示炸弹
    QLabel * m_Mana;//显示灵力
    QLabel * m_Count;//显示点数
    QLabel * m_TimeWhere;//时间记录
    QLabel * m_ScoreLab;//得分显示
    QLabel * m_FpsLab;//帧率显示
    QTimer * m_TimerFps;//帧率统计
    QTime *m_TimeHave;//计时
    long int m_Score=0;//得分记录
    int m_Fps=0;//帧率
    int lastTime=0;



signals:

public slots:
};

#endif // SIDEBARWIDGET_H
