#include "prop.h"

Prop::Prop()
{
    initProp();
}

void Prop::initProp()
{
    this->m_Free=true;

    m_Free=true;
    m_Angle=90.f;//角度
    m_Step=2.f;

    //位移
    m_X=-1000;
    m_Y=-1000;
    m_BX=-1000;
    m_BY=-1000;
    m_R=0;

    //判定
    m_Circular.m_R=30;
    m_Circular.m_X=-1000;
    m_Circular.m_Y=-1000;
    m_image=CutImg().getImg(1,16,3,13);
}

void Prop::newProp()
{
    if(m_Free)
        return;
    m_Y+=2;

    release();

}

void Prop::release()
{
    m_Circular.moveTo(m_X,m_Y);
    //判断释放
    if(m_Y>int(GAME_HEIGHT)+m_image.height())
        m_Free=true;

    if(m_Free)
    {
        m_R=0;
        id=-1;
        this->m_X=-1000;
        this->m_Y=-1000;
    }
}
