#include "boom.h"

Boom::Boom()
{

    this->initBoom();
}
void Boom::initBoom()
{
    this->m_TheNum=0;
    this->m_Free=true;
    this->m_Space=0;
    for(int i=1;i<=int(GAME_BOOM_NUM);i++)
    {
        QString str=QString(GAME_BOOM_WAY).arg(i);
        m_Vector.push_back(QPixmap(str));
    }
    this->m_Xoffset=m_Vector[0].width()/2;
    this->m_Yoffset=m_Vector[0].height()/2;
}

void Boom::newBoom()
{
    m_Space++;
    if(this->m_Free)
    {
        return;
    }
    if(m_Space < int(GAME_BOOM_ADDSPEED))
    {
        return;
    }

    //更新下一张图编号
    m_Space=0;
    this->m_TheNum++;

    if(m_TheNum > int(GAME_BOOM_NUM)-1)
    {
        //爆炸结束 数据恢复

        m_Free=true;
        m_TheNum=0;
        return;
    }
}
