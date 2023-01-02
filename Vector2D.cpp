#include <iostream>
#include "Vector2D.h"
#include "Point2D.h"
using namespace std;

//VECTOR2D.CPP

//default constructor
Vector2D::Vector2D()
{
  x = 0.0;
  y = 0.0;
}

//user-set constructor
Vector2D::Vector2D(double in_x, double in_y)
{
  x = in_x;
  y = in_y;
}

//non-member overloaded operator for <<
ostream& operator << (ostream& os, const Vector2D& v)
{
  os << "<" << v.x << ", " << v.y << ">" << endl;
  return os;
}

//non-member overloaded operator for *
Vector2D operator * (Vector2D v, double z)
{
  Vector2D temp;
  temp.x = (v.x * z);
  temp.y = (v.y * z);
  return temp;
}

//non-member overloaded operator for /
Vector2D operator / (Vector2D v, double z)
{
  if (z == 0)
    {
      return v;
    }
  
  Vector2D temp;
  temp.x = (v.x / z);
  temp.y = (v.y / z);
  return temp;
}
  

  

