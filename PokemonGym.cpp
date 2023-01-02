#include "PokemonGym.h"

PokemonGym::PokemonGym()
  :Building()
{
  display_code = 'G';
  state = NOT_DEFEATED;
  max_number_of_battles = 10;
  num_battles_remaining = max_number_of_battles;
  health_cost_per_battle = 1;
  PokeDollar_cost_per_battle = 1.0;
  experience_per_battle = 2;
}


PokemonGym::PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc)
  :Building(in_loc, in_id, 'G')
{
  id_num = in_id;
  max_number_of_battles = max_battle;
  num_battles_remaining = max_battle;
  health_cost_per_battle = health_loss;
  experience_per_battle = exp_per_battle;
  PokeDollar_cost_per_battle = PokeDollar_cost;
  location = in_loc;
}


//returns PokeDollar cost for total battles
double PokemonGym::GetPokeDollarCost(unsigned int battle_qty)
{
  return battle_qty*PokeDollar_cost_per_battle;
}

//returns health cost for total battles
unsigned int PokemonGym::GetHealthCost(unsigned int battle_qty)
{
  return health_cost_per_battle*battle_qty;
}

//Returns number of battles remaining for specific PokemonGym
unsigned int PokemonGym::GetNumBattlesRemaining()
{
  return num_battles_remaining;
}

//Returns true if Trainer can battle based on budget/PokemonHealth
bool PokemonGym::IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health)
{
  bool afford = budget >= PokemonGym::GetPokeDollarCost(battle_qty);
  bool healthy_enough = health >= PokemonGym::GetHealthCost(battle_qty);
  bool can_fight = afford && healthy_enough;
  
  return can_fight;
}

//Calculating XP for total battles fought
unsigned int PokemonGym::TrainPokemon(unsigned int battle_units)
{
  unsigned int total_battles, exp_gain;

  if (battle_units <= num_battles_remaining)
    {
      total_battles = num_battles_remaining - battle_units;
      exp_gain = total_battles*experience_per_battle;
    }

  else
    {
      exp_gain = num_battles_remaining*experience_per_battle;
    }
  
  return exp_gain;
}

//returns XP
unsigned int PokemonGym::GetExperiencePerBattle()
{
  return experience_per_battle;
}

unsigned int PokemonGym::Battle(unsigned int battle_units)
{
  num_battles_remaining = num_battles_remaining - battle_units;
}


//completed update function
bool PokemonGym::Update()
{

  char initial_state = state;
  
  if (num_battles_remaining == 0)
    {
      state = DEFEATED;
      display_code = 'g';
      cout << "(" << display_code << ")(" << id_num << ") has been beaten" << endl;
    }

  if ((initial_state == NOT_DEFEATED) && (state == DEFEATED))
    {
      return true;
    }
  else
    {
      return false;
    }
}

//return true if no more battles remaining
bool PokemonGym::passed()
{
  if (num_battles_remaining == 0)
    {
      return true;
    }

  else
    {
      return false;
    }
}

int PokemonGym::GetGymID()
{
  return id_num;
}

void PokemonGym::ShowStatus()
{
  cout << "**********************************************************" << endl;
  cout << "PokemonGymStatus: " << endl;
  Building::ShowStatus();
  cout << "Max number of battles: " << max_number_of_battles << endl;
  cout << "Health cost per battle: " << health_cost_per_battle << endl;
  cout << "PokeDollar per battle: " << PokeDollar_cost_per_battle << endl;
  cout << "Experience per battle: " << experience_per_battle << endl;
  cout << num_battles_remaining << " battle(s) are remaining for this PokemonGym" << endl;
  cout << "**********************************************************" << endl;
}

