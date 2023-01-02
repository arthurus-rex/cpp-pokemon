#ifndef TRAINER_H
#define TRAINER_H

#include <iostream>
#include <cstdlib>
#include "string.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonGym.h"
#include "PokemonCenter.h"
#include "WildPokemon.h"

using namespace std;

class WildPokemon;  //forward declaration cause header file wasn't working

enum state {
		    STOPPED = 0,
		    MOVING = 1,
		    FAINTED = 2,
		    AT_CENTER = 3,
		    IN_GYM = 4,
		    MOVING_TO_CENTER = 5,
		    MOVING_TO_GYM = 6,
		    BATTLING_IN_GYM = 7,
		    RECOVERING_HEALTH = 8
};

class Trainer: public GameObject {
 private:
  double speed, PokeDollars;
  bool is_at_center, is_IN_GYM;
  unsigned int health, experience, battles_to_buy, potions_to_buy;
  string name;
  PokemonCenter* current_center;
  PokemonGym* current_gym;
  WildPokemon* current_pokemon;
  Point2D destination;
  Vector2D delta;

 public:
  Trainer();
  Trainer(char in_code);
  Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
  
  virtual ~Trainer(); //virtual destructor

  void StartMoving(Point2D dest);
  void StartMovingToGym(PokemonGym* gym);
  void StartMovingToCenter(PokemonCenter* center);
  void StartBattling(unsigned int num_battles);
  void StartRecoveringHealth(unsigned int num_potions);
  void Stop();
  bool HasFainted();
  bool ShouldBeVisible();
  void ShowStatus();
  bool Update();
  string GetName();
  void GetState();
  PokemonCenter* GetCurrentCenter();
  PokemonGym* GetCurrentGym();
  int GetTrainerID();
  Point2D GetLocation();
  void ReduceTrainerHealth();
  

 protected:
  bool UpdateLocation();
  void SetupDestination(Point2D dest);
  
};

double GetRandomAmountOfPokeDollars();

#endif
