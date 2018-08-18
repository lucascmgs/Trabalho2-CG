#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <list>
#include <cmath> 

using namespace std;

const int WINDOWSIZE = 500;


class Point {
    public:
        double x;
        double y;

    Point(){
        this->x = 0;
        this->y = 0;
    }

    Point(double givenX, double givenY){
        this->x = givenX;
        this->y = givenY;
    }

    int ZProdVec (const Point& operated){
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

        cout << ABres << " " << CDres <<endl;

        return ((AB.ZProdVec(AD) * AB.ZProdVec(AC)) < 0 && (CD.ZProdVec(CA) * CD.ZProdVec(CB)) < 0);
    }
};

class Poligon {
    list<Point> points;
};

list<Point> points;
Point testPoint;
bool closed = false;

bool TestInOut(){
    int interceptTimes = 0;
    Segment auxSeg = Segment(testPoint, Point(1000, 1000));
    for (list<Point>::iterator it = points.begin();
         it != points.end(); ++it)
    {
        cout << "Intercept times: " << interceptTimes << endl;

        list<Point>::iterator testEnd = it;
        list<Point>::iterator second = testEnd;
        cout << "oii" <<endl;
        ++testEnd;
        cout << "oiii" <<endl;
        if(testEnd == points.end()){
           break;
        }
        ++second;
        Segment currentSeg = Segment(*it, *second);
        if(auxSeg.Intercepts(currentSeg)){
           interceptTimes++;
        }
    }
    if(interceptTimes % 2 == 0){
        return false;
    } else {
        return true;
    }
}

void resetPoints(){
    //Limpa a lista
    closed = false;
    testPoint = Point(1000, 1000);
    points.clear();
}

void mouse (int button, int state, int givenX, int givenY)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Point result = Point((2.*givenX)/WINDOWSIZE - 1., -(2.*givenY)/WINDOWSIZE + 1.);
        if(!closed){
            list<Point>::iterator firstPoint = points.begin();

            cout << result.Distance(*firstPoint) <<endl; 
            if(result.Distance(*firstPoint) < 0.1){
                points.push_back(*firstPoint);
                closed = true;
                return;
            }
            cout << "oi" << endl;
            points.push_back(result);
        } else{
            testPoint = result;
        }
        glutPostRedisplay();
    }
}

void keyboard_cb(unsigned char key, int X, int Y)
{
    switch (key)
    {
        case 27:             
            exit (0);
            break;

        //Tecla para chamar a suaviação das retas
        case 's':
            glutPostRedisplay();
            break;
        //Tecla para limpar os points
        case 'r':
            resetPoints();
            glutPostRedisplay();
            break;
    }
}


void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glPointSize(8.0);
    
    glLineWidth(2);
    

    glBegin(GL_LINE_STRIP);


    for (list<Point>::iterator it = points.begin();
         it != points.end(); ++it)
    {      
        glColor3f(0.0, 0.0, 1.0);
        double px = it->x;
        double py = it->y;
        //cout << "X: " << px << " Y: " << py << endl; 
        glVertex2f(px,py);
    }
    glEnd();    


    glBegin(GL_POINTS)
    if(closed){
        if(TestInOut()) {
            glColor3f(0.0, 1.0, 0.0);
        } else {
          glColor3f(1.0, 0.0, 0.0);
        }
        glVertex2f(testPoint.x, testPoint.y);
    }

    glFlush();
    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize (WINDOWSIZE, WINDOWSIZE);
    glutCreateWindow("points");
    glutKeyboardFunc(keyboard_cb);
    glutMouseFunc(mouse);
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return EXIT_SUCCESS ;

}
