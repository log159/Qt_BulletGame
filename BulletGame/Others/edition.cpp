#include "edition.h"

Edition::Edition()
{
    this->setFixedSize(WINDOW_WIDTH-GAME_WIDTH,30);
//    myLabel->setStyleSheet("border:2px solid red;");//设置边框
    this->setText("version number 3.0");
    QFont font;
    font.setFamily("楷体");
    font.setPointSize(10);
    this->setFont(font);
    this->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    this->setStyleSheet("color:white;");
}
