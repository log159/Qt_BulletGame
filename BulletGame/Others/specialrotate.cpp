#include "specialrotate.h"


SpecialRotate::SpecialRotate()
{

    this->initSpecialRotate(GAME_SPECIAL_WAY_1);
}
void SpecialRotate::initSpecialRotate(QString str)
{
    this->m_image.load(str);
    this->m_Width=m_image.width();
    this->m_Height=m_image.height();
}
