#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QDebug>

#include "Config/config.h"
#include "startwidget.h"
#include "selectwidget.h"
#include "widget.h"
#include "gamewidget_1.h"
#include "gamewidget_2.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    StartWidget * startWidgetPtr;

    SelectWidget * selectWidgetPtr;

    Widget * gameWidgetPtr;


signals:


public slots:
};

#endif // MAINWIDGET_H
