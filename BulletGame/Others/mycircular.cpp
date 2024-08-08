#include "mycircular.h"


void MyCircular::moveTo(int x, int y)
{
    m_X=x;
    m_Y=y;
}

bool MyCircular::intersects(const MyCircular& cir)
{
    int A=(m_X-cir.m_X)*(m_X-cir.m_X)+(m_Y-cir.m_Y)*(m_Y-cir.m_Y);
    int B=(m_R+cir.m_R)*(m_R+cir.m_R);
//    A>B;//相离
//    A<B;//相交
//    A==B;//相切


    if(A>=B)
    {
        return false;
    }
    else
    {
        return true;

    }



}
