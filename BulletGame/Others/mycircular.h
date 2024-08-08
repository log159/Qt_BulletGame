#ifndef MYCIRCULAR_H
#define MYCIRCULAR_H


class MyCircular
{
public:
    int m_X=-1000;//X坐标
    int m_Y=-1000;//Y坐标
    int m_R=0;//半径

    MyCircular()=default;

    void moveTo(int x,int y);//移动

    bool intersects(const MyCircular& cir);//判断相交
};

#endif // MYCIRCULAR_H
