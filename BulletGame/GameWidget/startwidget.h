#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QVector>
#include <QTimer>
#include <QPainter>
#include <QPixmap>

#include "Config/config.h"
#include "Others/mylabel.h"
#include "Others/map.h"
class StartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StartWidget(QWidget *parent = nullptr);
    ~StartWidget();

    int selectId=0;
    int maxId=2;

    QVector<MyLabel*>v_Lab;

    bool helpTime=false;
    QLabel * helpLab;

    Map * backgroundPtr;
    Map * backgroundPtr2;

    QTimer * timerPtr;
    QTimer * timerPress;

    QPoint initPoint;
    void animationLabel();

    void initMoveLabel();

    void paintEvent(QPaintEvent *e);

    void keyPressEvent(QKeyEvent *e);

signals:
    void goSelect();

    void goHelp();

    void goQuit();

public slots:
};

#endif // STARTWIDGET_H
