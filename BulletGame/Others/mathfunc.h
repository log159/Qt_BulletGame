#ifndef MATHFUNC_H
#define MATHFUNC_H
#include<cmath>
//数学宏定义
#define PI acos(-1)
class MathFunc
{
public:
    double getAngle(int x1,int y1,int x2,int y2)
    {
        double dob=atan(double(y1>y2?y1-y2:y2-y1)/double(x1>x2?x1-x2:x2-x1))*180/acos(-1);

        if(y2>=y1&&x2>=x1){return dob;}
        else if(y2>=y1&&x2<=x1){return 180.f-dob;}
        else if(y2<=y1&&x2<=x1){return 180.f+dob;}
        else if(y2<=y1&&x2>=x1){return 360.f-dob;}
        else{return 90;}
    }
    double getR(int x1,int y1,int x2,int y2)
    {
        int tempX=x1-x2;
        int tempY=y1-y2;
        if(tempX<0){tempX=-tempX;}
        if(tempY<0){tempY=-tempY;}
        return sqrt(double(tempX*tempX+tempY*tempY));

    }
};
#endif // MATHFUNC_H
