#ifndef POKEMON_GYM_H
#define POKEMON_GYM_H

#include <iostream>
#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"

enum PokemonGymStates {
		       NOT_DEFEATED = 0,
		       DEFEATED = 1
};

class PokemonGym: public Building {
 private:
  unsigned int num_battles_remaining, max_number_of_battles, health_cost_per_battle, experience_per_battle;
  double PokeDollar_cost_per_battle;

 public:
  PokemonGym();
  PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc);

  double GetPokeDollarCost(unsigned int battle_qty);
  unsigned int GetHealthCost(unsigned int battle_qty);
  unsigned int GetNumBattlesRemaining();
  bool IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health);
  unsigned int TrainPokemon(unsigned int battle_units);
  unsigned int GetExperiencePerBattle();
  unsigned int Battle(unsigned int battle_units); //reduces Gym's num_battles_remaining by battle_count
  int GetGymID();
  bool Update();
  bool passed();
  void ShowStatus();
    
};

#endif


