#ifndef MYCOORDINATE_H
#define MYCOORDINATE_H


class MyCoordinate
{
public:

    //获取坐标存入
    void getCoordinate(int x,int y);

    //坐标返回
    int putX();
    int putY();

    MyCoordinate()=default;

private:
    int m_X;
    int m_Y;
};

#endif // MYCOORDINATE_H
