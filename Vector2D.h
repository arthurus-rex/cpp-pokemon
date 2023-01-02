#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include "math.h"
#include "Point2D.h"
using namespace std;

class Vector2D {
 public:
  double x, y;

  //constructors
  Vector2D(); //default constructor
  Vector2D(double in_x, double in_y); //parameter constructor

};

//non-member overloaded ostream operator
ostream& operator << (ostream&, const Vector2D&);

//other non-member overloaded operators
Vector2D operator * (Vector2D, double);
Vector2D operator / (Vector2D, double);

#endif
