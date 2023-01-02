#include "Building.h"

Building::Building()
  :GameObject('B')
{
  trainer_count = 0;
  cout << "Building default constructed" << endl;
}


Building::Building(Point2D in_loc, int in_id, char in_code)
  :GameObject(in_loc, in_id, 'B') 
{
  trainer_count = 0;
  id_num = in_id;
  location = in_loc;
  display_code = in_code;
  state = '0';
}

void Building::AddOneTrainer()
{
  trainer_count++;
}

void Building::RemoveOneTrainer()
{
  trainer_count--;
}

void Building::ShowStatus()
{
  cout << "(" << display_code << ")(" << id_num << ") located at " << location << endl;
  
  if (trainer_count == 1)
    {
      cout << "(" << trainer_count << ") trainer is in this building." << endl;
    }
  else
    {
      cout << "(" << trainer_count << ") trainers are in this building." << endl;
    }
}

bool Building::ShouldBeVisible()
{
  return true;
}


