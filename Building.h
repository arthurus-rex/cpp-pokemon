#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include "GameObject.h"
#include "Point2D.h"
using namespace std;

class Building: public GameObject {
 private:
  unsigned int trainer_count;

 public:
  Building();
  Building(Point2D in_loc, int in_id, char in_code);

  void AddOneTrainer();
  void RemoveOneTrainer();
  void ShowStatus();
  bool ShouldBeVisible();

};


#endif
