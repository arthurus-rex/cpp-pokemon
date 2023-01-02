//GameObject.h

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"
using namespace std;

//forward declaration
class Point2D;

class GameObject {
  
  //initializing variables
 protected:
  Point2D location;
  int id_num, state;
  char display_code;
  

 public:
  //constructors
  GameObject(char in_code);
  GameObject(Point2D in_loc, int in_id, char in_code);

  //virtual destructors
  virtual ~GameObject() = 0;

  //member functions
  Point2D GetLocation();
  int GetId();
  char GetState();

  //virtual member functions
  virtual void ShowStatus() = 0;
  virtual bool ShouldBeVisible() = 0;
  virtual bool Update() = 0;

  void DrawSelf(char* ptr);
  

};

#endif


