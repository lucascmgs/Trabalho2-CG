#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point {
    public:
        double x;
        double y;
        bool in;
        float Color[3] = {0.0, 0.0, 1.0};

    Point(){
        this->x = 0;
        this->y = 0;
        this->Color[2] = 1.0;
    }

    Point(double givenX, double givenY){
        this->x = givenX;
        this->y = givenY;
    }

    void SetColor(float red, float green, float blue){
        this->Color[0] = red;
        this->Color[1] = green;
        this->Color[2] = blue;
    }

    double ZProdVec (const Point& operated){
        return(this->x * operated.y - this->y * operated.x);
    }

    Point MiddlePoint(const Point& operated){
        return Point((this->x + operated.x)/2., (this->y + operated.y)/2.);
    }

    double Distance(const Point& operated){
        double resultX = operated.x - this->x;
        double resultY = operated.y - this->y;
        return sqrt(pow(resultX, 2) + pow(resultY, 2));
    }

    Point operator+ (const Point& operated){
        return Point(this->x + operated.x, this->y + operated.y);
    }


    Point operator- (const Point& operated){
        return Point(this->x - operated.x, this->y - operated.y);
    }

    Point operator* (const double k){
        return Point(this->x * k, this->y * k);
    }

    Point& operator+= (const Point& operated){
        this->x += operated.x;
        this->y += operated.y;

        return *this;
    }

    Point& operator*= (const double escalar){
        this->x *= escalar;
        this->y *= escalar;

        return *this;
    }
};

#endif