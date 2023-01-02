#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>


#include "math.h"
#include "Vector2D.h"
using namespace std;

class Vector2D;
class Point2D {
 public:
  double x, y;

  //constructors
  Point2D();   //default constructor
  Point2D(double in_x, double in_y); //parameter constructor


};

//non-member function prototyptes
double GetDistanceBetween(Point2D p1, Point2D p2);  

//overloaded operator for <<
ostream& operator << (ostream&, const Point2D&);

//overloaded operator for + and -
Point2D operator+(Point2D p1, Vector2D v1);
Vector2D operator-(Point2D p1, Point2D p2);

#endif
