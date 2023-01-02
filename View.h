#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <cstdlib>
#include "string.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonGym.h"
#include "PokemonCenter.h"
#include "Trainer.h"
#include "Model.h"
#include "GameCommand.h"

using namespace std;

const int view_maxsize = 20; //max size of grid array

class View
{
	
 private:
  int size;
  double scale;
  Point2D origin;
  char grid[view_maxsize][view_maxsize][2];

  //calculates subscripts of grid array
  bool GetSubscripts(int &out_x, int &out_y, Point2D location);

 public:
  View();

  void Clear();
  void Plot(GameObject* ptr);
  void Draw();
  

};

#endif
