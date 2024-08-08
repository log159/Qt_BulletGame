#include "mylabel.h"

MyLabel::MyLabel(const QString&str,int s)
{
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(s);
    this->setFont(font);
    this->setText(str);
    this->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //this->setAttribute(Qt::WA_TransparentForMouseEvents);//鼠标穿透效果
    this->setStyleSheet("color:rgb(255,255,255);border-radius:5px;");//设置及字体

}

void MyLabel::setPressStyle()
{
    this->setStyleSheet("color:rgb(255,0,0);border-radius:5px;");//设置及字体
}

void MyLabel::setReleaseStyle()
{
    this->setStyleSheet("color:rgb(255,255,255);border-radius:5px;");//设置及字体
}

//    QFont font;
//    font.setFamily("黑体");
//    font.setPointSize(font.pixelSize()+1);
//    this->setFont(font);

