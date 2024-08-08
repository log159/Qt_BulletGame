#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QVector>
#include <QTimer>
#include <QPainter>
#include <QPixmap>

#include "Config/config.h"
#include "Others/mylabel.h"
#include "Others/map.h"
class SelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectWidget(QWidget *parent = nullptr);
    ~SelectWidget();

    int selectId=0;
    int maxId=1;

    QVector<MyLabel*>v_Lab;
    QVector<QPixmap>v_Img;

    Map * backgroundPtr;
    Map * backgroundPtr2;

    QTimer * timerPtr;

    void paintEvent(QPaintEvent *e);

    void keyPressEvent(QKeyEvent *e);

signals:
    void startGame(int id);

public slots:
};

#endif // SELECTWIDGET_H
