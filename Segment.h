#ifndef SEGMENT_H
#define SEGMENT_H

#include "Point.h"

using namespace std;

class Segment {
    public:
    Point From;
    Point To;

    Segment(const Point givenFrom, const Point givenTo){
        this->From = givenFrom;
        this->To = givenTo;
    }

    Point Vectorialize(){
        return this->To - this->From;
    }

    bool Intercepts (Segment& operated){
        Point AB = this->Vectorialize();
        Point AD = operated.To - this->From;
        Point AC = operated.From - this->From;

        Point CD = operated.Vectorialize();
        Point CA = this->From - operated.From;
        Point CB = this->To - operated.From;

        double ABres = (AB.ZProdVec(AD) * AB.ZProdVec(AC));
        double CDres = (CD.ZProdVec(CA) * CD.ZProdVec(CB));

        cout << ABres << " " << CDres << endl;

        return (ABres < 0 && CDres < 0);
    }
};

#endif