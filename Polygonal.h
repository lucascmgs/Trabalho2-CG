#ifndef POLYGONAL_H
#define POLYGONAL_H
#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "Point.h"
#include "Segment.h"
#include <list> 

using namespace std;

class Polygonal {
    public:
    bool closed = false;
    list<Point> Points;

    void Reset(){
        closed = false;
        Points.clear();
    }

    void Add(Point p){
        if(!this->closed){
            this->Points.push_back(p);
        }
    }

    bool IsClosed(){
        return this->closed;
    }

    bool CheckInside(Point p){
        if(this->closed){
            int interceptCount = 0;
            Point outerPoint = Point(1.1, 1.1);
            Segment testSegment = Segment(p, outerPoint);
            for (list<Point>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){      
                list<Point>::iterator second;
                second = it;
                second++;
                if(second == this->Points.end()){
                    break;
                }
                
                Segment currentSegment = Segment(*it, *second);

                if(testSegment.Intercepts(currentSegment)){
                    interceptCount++;
                }
            }
            if(interceptCount % 2 == 0) {
                return false;
            } else {
                return true;
            }
        }
        return false;
    }

    list<Point> GetPoints(){
        return this->Points;
    }

    void Close (){
        this->closed = true;
    }

    void PlotLines(){
        glBegin(GL_LINE_STRIP);
        for (list<Point>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){   
            Point p = *it;   
            glColor3f(p.Color[0], p.Color[1], p.Color[2]);
            double px = it->x;
            double py = it->y;
            //cout << "X: " << px << " Y: " << py << endl; 
            glVertex2f(px,py);
        }
        glEnd();
    }

    void PlotPoints(){
        glBegin(GL_POINTS);
        for (list<Point>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){      
            Point p = *it;
            glColor3f(p.Color[0], p.Color[1], p.Color[2]);
            double px = it->x;
            double py = it->y;
            //cout << "X: " << px << " Y: " << py << endl; 
            glVertex2f(px,py);
        }
        glEnd();
    }
};

#endif