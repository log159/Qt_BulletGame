#include "map.h"

Map::Map(const QString&str)
{
    this->m_image1.load(str);
    this->m_image2.load(str);
    this->m_Y1=-m_image1.height();
    this->m_Y2=0;
    this->m_Speed=int(GAME_MAP_SPEED);
}

void Map::change(const QString&str)
{
    this->m_image1.load(str);
    this->m_image2.load(str);
    this->m_Y1=-m_image1.height();
    this->m_Y2=0;
    this->m_Speed=int(GAME_MAP_SPEED);

}

void Map::newMap()
{
    this->m_Y1+=this->m_Speed;
    this->m_Y2+=this->m_Speed;


    if(m_Y1>=0)
    {
        this->m_Y1=-m_image1.height();
        this->m_Y2=0;

    }

}
