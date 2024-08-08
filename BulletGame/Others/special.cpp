#include "special.h"



Special::Special()
{

    this->initSpecial(GAME_SPECIAL_WAY_1,5,1);
}
void Special::initSpecial(QString str,int w,int h)
{

    m_image.load(str);

    //刷新数据初始化
    m_OffsetNum=0;
    m_Speed=0;
    m_X=-100;
    m_Y=-100;

    //分割单位初始化
    this->m_Wunit=w;
    this->m_Hunit=h;

    m_Width=m_image.width()/w;
    m_Height=m_image.height()/h;



    m_Xoffset=m_Width*m_OffsetNum;
    m_Yoffset=m_Height*0;


    m_PrintX=(m_X-m_Width/2)-m_Xoffset;
    m_PrintY=(m_Y-m_Height/2)-m_Yoffset;



}

void Special::newSpecial(int x,int y)
{
    m_X=x;
    m_Y=y;

    m_Speed++;
    if(m_Speed<int(GAME_SPECIAL_ADDSPEED_1))
    {
        return;
    }
    m_Speed=0;
    this->m_OffsetNum++;
    if(m_OffsetNum>=m_Wunit-3)
    {
        m_OffsetNum=0;
    }
    //修改偏移量
    this->m_Xoffset=m_Width*m_OffsetNum;


    this->m_PrintX=(m_X-this->m_Width/2)-m_Xoffset;
    this->m_PrintY=(m_Y-this->m_Height/2)-m_Yoffset;

}
