#include "mycoordinate.h"




void MyCoordinate::getCoordinate(int x, int y)
{
    m_X=x;
    m_Y=y;
}

int MyCoordinate::putX()
{
    return m_X;
}

int MyCoordinate::putY()
{
    return m_Y;
}
