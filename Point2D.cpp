#include <iostream>
#include <cmath>
#include <string.h>
#include "Point2D.h"
#include "Vector2D.h"
using namespace std;

//POINT2D.CPP
//represents a point on a Cartesian coordinate system

//default constructor
Point2D::Point2D() 
{
  x = 0.0;
  y = 0.0;
}

//user-set constructor
Point2D::Point2D(double in_x, double in_y) 
{
  x = in_x;
  y = in_y;
}

//non-member function returns Cartesian distance between p1 and p2
double GetDistanceBetween(Point2D p1, Point2D p2) 
{
  return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}



//non-member overloaded operator for <<
ostream& operator << (ostream& os, const Point2D& pt)
{
  os << "(" << pt.x << ", " << pt.y << ")" << endl;
  return os;
}

//non-member overloaded operator for +
Point2D operator + (Point2D pt1, Vector2D v1)
{
  Point2D temp;
  temp.x = (pt1.x + v1.x);
  temp.y = (pt1.y + v1.y);
  return temp;
}


//non-member overloaded operator for -
Vector2D operator - (Point2D pt1, Point2D pt2)
{
  Vector2D temp;
  temp.x = (pt1.x - pt2.x);
  temp.y = (pt1.y - pt2.y);
  return temp;
}

