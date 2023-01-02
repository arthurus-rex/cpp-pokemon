#ifndef WILD_POKEMON_H
#define WILD_POKEMON_H

#include <iostream>
#include <string.h>

#include "GameObject.h"
#include "Point2D.h"
#include "Trainer.h"
#include "Vector2D.h"

using namespace std;


enum PokemonStates {
	    IN_ENVIRONMENT = 0,
	    IN_TRAINER = 1,
	    DEAD = 2,
	    IN_COMBAT = 3
};

class Trainer;

class WildPokemon: public GameObject {
  
protected:
  double attack, health, speed;
  bool variant, in_combat;
  string name;
  Trainer* current_trainer;
  unsigned int PokemonStates;
  Point2D current_location, destination;
  Vector2D pokemon_delta;

  
public:
  
  WildPokemon(string, double, double, bool, int, Point2D);

  //~WildPokemon();

  void follow(Trainer* current_trainer);

  
  bool get_variant();
  double get_attack();
  double get_health();
  bool get_in_combat();
  bool UpdatePokemonLocation();
  void SetupPokemonDestination();
  
  bool Update();
  void ShowStatus();
  bool ShouldBeVisible();
  
  
  bool IsAlive();
  int GetPokemonID();
  Point2D GetLocation();
  
  
 
  

};

#endif
