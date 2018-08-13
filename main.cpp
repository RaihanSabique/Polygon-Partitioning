#include <iostream>
#include <stack>
#include <fstream>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

using namespace std;

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;



struct Point
{
	int x, y;
};

Point p0;

Point nextToTop(stack<Point> &S)
{
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

int swap(Point &p1, Point &p2)
{
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

int twoPointDist(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y);
}

int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // colinear
	return (val > 0)? 1: 2; // clock or counterclock wise
}

int compare(const void *vp1, const void *vp2)
{
Point *p1 = (Point *)vp1;
Point *p2 = (Point *)vp2;

int o = orientation(p0, *p1, *p2);
if (o == 0)
	return (twoPointDist(p0, *p2) >= twoPointDist(p0, *p1))? -1 : 1;

return (o == 2)? -1: 1;
}

 Point *convexHull(Point points[], int n)
{
int ymin = points[0].y, min = 0;
for (int i = 1; i < n; i++)
{
	int y = points[i].y;

	if ((y < ymin) || (ymin == y &&
		points[i].x < points[min].x))
		ymin = points[i].y, min = i;
}

swap(points[0], points[min]);

p0 = points[0];
qsort(&points[1], n-1, sizeof(Point), compare);

int m = 1;
for (int i=1; i<n; i++)
{
	while (i < n-1 && orientation(p0, points[i],
									points[i+1]) == 0)
		i++;


	points[m] = points[i];
	m++;
	}

if (m < 3) return NULL;

int distance=0;
stack<Point> S;
S.push(points[0]);
S.push(points[1]);
S.push(points[2]);
distance+=pow(twoPointDist(points[0],points[1]),0.5);
//cout<<distance<<endl;
distance+=pow(twoPointDist(points[1],points[2]),0.5);
//cout<<distance<<endl;

int i;
for (i = 3; i < m; i++)
{
	while (orientation(nextToTop(S), S.top(), points[i]) != 2)
		S.pop();
	S.push(points[i]);
	distance+=pow(twoPointDist(points[i-1],points[i]),0.5);
}
distance+=pow(twoPointDist(points[0],points[i]),0.5);
cout<<distance<<"\n";
Point solutionPoints[S.size()];
int x=0;
while (!S.empty())
{
	Point p = S.top();
	solutionPoints[x]=p;
	x++;
	cout << p.x << ", " << p.y << endl;
	S.pop();
}
return solutionPoints;
}


void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 400,0,0);
			glVertex3f(-400,0,0);

			glVertex3f(0,-400,0);
			glVertex3f(0, 400,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void drawPoint()
{
    glColor3f(0.5, .5, .40);
    glBegin(GL_POINTS);
    ifstream infile("input.txt");
	int a, b;
     int n;

	if(infile>>a)
    {
        //cout<<a<<"\n";
        n=a;
    }

    while (infile >> a >> b)
    {
        glVertex2f(a, b);
        //cout<<a<<","<<b<<"\n";
    }

    glEnd( );
}

void drawLine()
{
    glColor3f(1, 0.5, 0.5);
    glBegin(GL_LINES);

    ifstream infile("output1.txt");
	double a, b,c,d;
	int f=0;
	double x0,y0,x1,y1;
	while (infile >> a >> b>>c>>d)
    {
        glVertex2f(a,b); // origin of the line
        glVertex2f(c,d); // ending point of the line
    }

    glEnd( );
}

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(0,0,20,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();
	drawPoint();
	drawLine();

    //glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){




	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();






	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)


	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
